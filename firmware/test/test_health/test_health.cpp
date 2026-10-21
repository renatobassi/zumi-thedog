#include <unity.h>

#include "domain/care.hpp"
#include "domain/health.hpp"
#include "persistence/boot.hpp"
#include "persistence/record.hpp"
#include "ui/frame.hpp"

static const uint32_t kHourMs = 60u * 60u * 1000u;
static const uint32_t kMinuteMs = 60u * 1000u;

void setUp(void) {}
void tearDown(void) {}

struct MemStore {
  uint8_t data[64];
  size_t len;
  bool present;
};

static bool mem_load(void* ctx, PetSnapshot* out) {
  MemStore* mem = static_cast<MemStore*>(ctx);
  if (!mem->present) {
    return false;
  }
  return pet_record_decode(mem->data, mem->len, out);
}

static bool mem_save(void* ctx, const PetSnapshot* snap) {
  MemStore* mem = static_cast<MemStore*>(ctx);
  size_t written = 0;
  if (!pet_record_encode(*snap, mem->data, sizeof mem->data, &written)) {
    return false;
  }
  mem->len = written;
  mem->present = true;
  return true;
}

static PetStore mem_store(MemStore* mem) {
  PetStore store;
  store.ctx = mem;
  store.load = mem_load;
  store.save = mem_save;
  return store;
}

static PetSnapshot critical_pet(uint32_t low_ms) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  pet.bars.hunger = 10;
  pet.bars.energy = 10;
  pet.low_ms = low_ms;
  return pet;
}

void test_case_not_sick_at_59_minutes(void) {
  PetSnapshot pet = critical_pet(59u * kMinuteMs);
  health_advance(pet, 0);
  TEST_ASSERT_FALSE(pet.sick);
  health_advance(pet, 0);
  care_advance(pet, 0);
  PetSnapshot timed = critical_pet(0);
  timed.bars.hunger = 10;
  timed.bars.energy = 10;
  // Só o contador de doença; barras já críticas.
  health_advance(timed, 59u * kMinuteMs);
  TEST_ASSERT_FALSE(timed.sick);
  TEST_ASSERT_EQUAL_UINT32(59u * kMinuteMs, timed.low_ms);
}

void test_case_gets_sick_at_60_minutes(void) {
  PetSnapshot pet = critical_pet(0);
  health_advance(pet, 60u * kMinuteMs);
  TEST_ASSERT_TRUE(pet.sick);
  TEST_ASSERT_FALSE(pet.on_street);
  pet.bars.energy = 20;
  TEST_ASSERT_FALSE(care_apply(pet, CARE_PLAY));
}

void test_case_recovers_when_bars_rise(void) {
  PetSnapshot pet = critical_pet(0);
  pet.sick = true;
  pet.sick_ms = 3u * kHourMs;
  pet.bars.hunger = 25;
  pet.bars.energy = 25;
  health_advance(pet, kMinuteMs);
  TEST_ASSERT_FALSE(pet.sick);
  TEST_ASSERT_EQUAL_UINT32(0, pet.sick_ms);
  pet.bars.energy = 20;
  TEST_ASSERT_TRUE(care_apply(pet, CARE_PLAY));
}

void test_case_street_after_24h_sick(void) {
  PetSnapshot pet = critical_pet(0);
  pet.sick = true;
  pet.bars.hunger = 5;
  pet.bars.energy = 5;
  health_advance(pet, 24u * kHourMs);
  TEST_ASSERT_TRUE(pet.on_street);
  const uint8_t hunger = pet.bars.hunger;
  care_advance(pet, kHourMs);
  TEST_ASSERT_EQUAL_UINT8(hunger, pet.bars.hunger);
  TEST_ASSERT_FALSE(care_apply(pet, CARE_FEED));
}

void test_case_adopt_resets_cycle(void) {
  PetSnapshot pet = pet_snapshot_newborn(100);
  pet.on_street = true;
  pet.sick = true;
  pet.age_ms = 90u * kHourMs;
  pet.bars.hunger = 0;
  TEST_ASSERT_TRUE(care_apply(pet, CARE_ADOPT));
  TEST_ASSERT_FALSE(pet.on_street);
  TEST_ASSERT_FALSE(pet.sick);
  TEST_ASSERT_EQUAL_UINT32(0, pet.age_ms);
  TEST_ASSERT_EQUAL(PHASE_BLANKET, pet.phase);
  TEST_ASSERT_EQUAL_UINT8(100, pet.bars.hunger);
  TEST_ASSERT_FALSE(pet.asleep);
}

void test_case_drawer_keeps_sick_hours(void) {
  MemStore mem = {};
  PetStore store = mem_store(&mem);
  PetSnapshot pet = critical_pet(0);
  pet.sick = true;
  pet.sick_ms = 10u * kHourMs;
  pet.bars.hunger = 5;
  pet.bars.energy = 5;
  pet.last_tick_ms = 1;
  TEST_ASSERT_TRUE(pet_commit(store, pet));

  const PetSnapshot restored = pet_restore(store, 99);
  TEST_ASSERT_TRUE(restored.sick);
  TEST_ASSERT_EQUAL_UINT32(10u * kHourMs, restored.sick_ms);
  TEST_ASSERT_FALSE(restored.on_street);
}

void test_street_frame_offers_adopt(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  pet.on_street = true;
  const ZumiFrame frame = zumi_frame(pet);
  TEST_ASSERT_EQUAL_STRING("Voltou pra rua", frame.status);
  TEST_ASSERT_EQUAL_INT(1, frame.target_count);
  TEST_ASSERT_EQUAL_INT(TOUCH_ADOPT, frame.targets[0].action);
  TEST_ASSERT_EQUAL_STRING("Adotar", frame.targets[0].label);
}

void test_sick_frame_says_sick(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  pet.sick = true;
  TEST_ASSERT_EQUAL_STRING("Doente", zumi_frame(pet).status);
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  UNITY_BEGIN();
  RUN_TEST(test_case_not_sick_at_59_minutes);
  RUN_TEST(test_case_gets_sick_at_60_minutes);
  RUN_TEST(test_case_recovers_when_bars_rise);
  RUN_TEST(test_case_street_after_24h_sick);
  RUN_TEST(test_case_adopt_resets_cycle);
  RUN_TEST(test_case_drawer_keeps_sick_hours);
  RUN_TEST(test_street_frame_offers_adopt);
  RUN_TEST(test_sick_frame_says_sick);
  return UNITY_END();
}

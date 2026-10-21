#include <unity.h>

#include "domain/care.hpp"
#include "domain/growth.hpp"
#include "persistence/boot.hpp"
#include "persistence/record.hpp"

static const uint32_t kHourMs = 60u * 60u * 1000u;

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

void test_case_blanket_under_24h(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  care_advance(pet, 23u * kHourMs);
  TEST_ASSERT_EQUAL_UINT32(23u * kHourMs, pet.age_ms);
  TEST_ASSERT_EQUAL(PHASE_BLANKET, pet.phase);
}

void test_case_puppy_at_24h(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  care_advance(pet, 24u * kHourMs);
  TEST_ASSERT_EQUAL(PHASE_PUPPY, pet.phase);
  care_advance(pet, 47u * kHourMs);
  TEST_ASSERT_EQUAL_UINT32(71u * kHourMs, pet.age_ms);
  TEST_ASSERT_EQUAL(PHASE_PUPPY, pet.phase);
}

void test_case_adult_sitting_at_72h(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  care_advance(pet, 72u * kHourMs);
  TEST_ASSERT_EQUAL(PHASE_ADULT_SITTING, pet.phase);
  care_advance(pet, 95u * kHourMs);
  TEST_ASSERT_EQUAL(PHASE_ADULT_SITTING, pet.phase);
}

void test_case_adult_at_168h(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  care_advance(pet, 168u * kHourMs);
  TEST_ASSERT_EQUAL(PHASE_ADULT, pet.phase);
  care_advance(pet, 50u * kHourMs);
  TEST_ASSERT_EQUAL(PHASE_ADULT, pet.phase);
}

void test_case_drawer_keeps_age_and_phase(void) {
  MemStore mem = {};
  PetStore store = mem_store(&mem);
  PetSnapshot pet = pet_snapshot_newborn(0);
  care_advance(pet, 10u * kHourMs);
  pet.last_tick_ms = 10u * kHourMs;
  TEST_ASSERT_TRUE(pet_commit(store, pet));

  const uint8_t hunger_before = pet.bars.hunger;
  const PetSnapshot restored = pet_restore(store, 10u * kHourMs + 24u * kHourMs);
  TEST_ASSERT_EQUAL_UINT32(10u * kHourMs, restored.age_ms);
  TEST_ASSERT_EQUAL(PHASE_BLANKET, restored.phase);
  TEST_ASSERT_EQUAL_UINT8(hunger_before, restored.bars.hunger);
}

void test_old_v1_record_starts_age_zero(void) {
  uint8_t bytes[kPetRecordV1Size] = {
      'Z', 'U', 'M', 'I', 1, 10, static_cast<uint8_t>(PHASE_PUPPY), 40, 70, 55, 80, 0, 1, 0, 0, 0, 0, 0};
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < 16; ++i) {
    crc ^= static_cast<uint16_t>(bytes[i]) << 8;
    for (int bit = 0; bit < 8; ++bit) {
      if ((crc & 0x8000) != 0) {
        crc = static_cast<uint16_t>((crc << 1) ^ 0x1021);
      } else {
        crc = static_cast<uint16_t>(crc << 1);
      }
    }
  }
  bytes[16] = static_cast<uint8_t>(crc);
  bytes[17] = static_cast<uint8_t>(crc >> 8);

  PetSnapshot out;
  TEST_ASSERT_TRUE(pet_record_decode(bytes, sizeof bytes, &out));
  TEST_ASSERT_EQUAL_UINT32(0, out.age_ms);
  TEST_ASSERT_EQUAL(PHASE_BLANKET, out.phase);
  TEST_ASSERT_EQUAL_UINT8(40, out.bars.hunger);
}

void test_phase_for_age_thresholds(void) {
  TEST_ASSERT_EQUAL(PHASE_BLANKET, phase_for_age(0));
  TEST_ASSERT_EQUAL(PHASE_BLANKET, phase_for_age(kGrowthPuppyMs - 1));
  TEST_ASSERT_EQUAL(PHASE_PUPPY, phase_for_age(kGrowthPuppyMs));
  TEST_ASSERT_EQUAL(PHASE_ADULT_SITTING, phase_for_age(kGrowthAdultSittingMs));
  TEST_ASSERT_EQUAL(PHASE_ADULT, phase_for_age(kGrowthAdultMs));
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  UNITY_BEGIN();
  RUN_TEST(test_case_blanket_under_24h);
  RUN_TEST(test_case_puppy_at_24h);
  RUN_TEST(test_case_adult_sitting_at_72h);
  RUN_TEST(test_case_adult_at_168h);
  RUN_TEST(test_case_drawer_keeps_age_and_phase);
  RUN_TEST(test_old_v1_record_starts_age_zero);
  RUN_TEST(test_phase_for_age_thresholds);
  return UNITY_END();
}

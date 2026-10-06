#include <unity.h>

#include "persistence/boot.hpp"
#include "persistence/record.hpp"

static const uint32_t kHourMs = 60u * 60u * 1000u;

struct MemStore {
  uint8_t data[64];
  size_t len;
  bool present;
};

void setUp(void) {}
void tearDown(void) {}

static PetSnapshot pet_with(uint8_t hunger, uint8_t energy, uint8_t fun, uint8_t hygiene, bool asleep) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  pet.bars.hunger = hunger;
  pet.bars.energy = energy;
  pet.bars.fun = fun;
  pet.bars.hygiene = hygiene;
  pet.asleep = asleep;
  return pet;
}

static void expect_bars(const PetSnapshot& pet, uint8_t hunger, uint8_t energy, uint8_t fun, uint8_t hygiene) {
  TEST_ASSERT_EQUAL_UINT8(hunger, pet.bars.hunger);
  TEST_ASSERT_EQUAL_UINT8(energy, pet.bars.energy);
  TEST_ASSERT_EQUAL_UINT8(fun, pet.bars.fun);
  TEST_ASSERT_EQUAL_UINT8(hygiene, pet.bars.hygiene);
}

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

static uint16_t crc16(const uint8_t* data, size_t len) {
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; ++i) {
    crc ^= static_cast<uint16_t>(data[i]) << 8;
    for (int bit = 0; bit < 8; ++bit) {
      if ((crc & 0x8000) != 0) {
        crc = static_cast<uint16_t>((crc << 1) ^ 0x1021);
      } else {
        crc = static_cast<uint16_t>(crc << 1);
      }
    }
  }
  return crc;
}

void test_case_power_cut_keeps_awake_bars(void) {
  MemStore mem = {};
  PetStore store = mem_store(&mem);
  PetSnapshot pet = pet_with(40, 70, 55, 80, false);
  pet.phase = PHASE_PUPPY;
  pet.last_tick_ms = 123456;
  TEST_ASSERT_TRUE(pet_commit(store, pet));

  const PetSnapshot restored = pet_restore(store, 50);
  expect_bars(restored, 40, 70, 55, 80);
  TEST_ASSERT_FALSE(restored.asleep);
  TEST_ASSERT_EQUAL(PHASE_PUPPY, restored.phase);
  TEST_ASSERT_EQUAL_UINT32(50, restored.last_tick_ms);
}

void test_case_power_cut_keeps_sleep(void) {
  MemStore mem = {};
  PetStore store = mem_store(&mem);
  PetSnapshot pet = pet_with(60, 30, 55, 80, true);
  pet.last_tick_ms = 999;
  TEST_ASSERT_TRUE(pet_commit(store, pet));

  const PetSnapshot restored = pet_restore(store, 10);
  expect_bars(restored, 60, 30, 55, 80);
  TEST_ASSERT_TRUE(restored.asleep);
  TEST_ASSERT_EQUAL_UINT32(10, restored.last_tick_ms);
}

void test_case_drawer_hours_do_not_decay(void) {
  MemStore mem = {};
  PetStore store = mem_store(&mem);
  PetSnapshot pet = pet_with(40, 70, 55, 80, false);
  pet.last_tick_ms = 0;
  TEST_ASSERT_TRUE(pet_commit(store, pet));

  const PetSnapshot restored = pet_restore(store, 5u * kHourMs);
  expect_bars(restored, 40, 70, 55, 80);
  TEST_ASSERT_FALSE(restored.asleep);
  TEST_ASSERT_EQUAL_UINT32(5u * kHourMs, restored.last_tick_ms);
}

void test_case_first_boot_is_newborn(void) {
  MemStore mem = {};
  PetStore store = mem_store(&mem);

  const PetSnapshot restored = pet_restore(store, 80);
  expect_bars(restored, 100, 100, 100, 100);
  TEST_ASSERT_FALSE(restored.asleep);
  TEST_ASSERT_EQUAL(PHASE_BLANKET, restored.phase);
  TEST_ASSERT_EQUAL_UINT32(80, restored.last_tick_ms);
}

void test_case_invalid_record_is_newborn(void) {
  MemStore mem = {};
  mem.present = true;
  mem.len = 4;
  mem.data[0] = 1;
  mem.data[1] = 2;
  mem.data[2] = 3;
  mem.data[3] = 4;
  PetStore store = mem_store(&mem);

  const PetSnapshot restored = pet_restore(store, 15);
  expect_bars(restored, 100, 100, 100, 100);
  TEST_ASSERT_FALSE(restored.asleep);
  TEST_ASSERT_EQUAL_UINT32(15, restored.last_tick_ms);
}

void test_flipped_byte_does_not_decode(void) {
  PetSnapshot pet = pet_with(40, 70, 55, 80, false);
  uint8_t buf[kPetRecordV1Size];
  size_t written = 0;
  TEST_ASSERT_TRUE(pet_record_encode(pet, buf, sizeof buf, &written));
  buf[7] ^= 0x01;

  PetSnapshot out;
  TEST_ASSERT_FALSE(pet_record_decode(buf, written, &out));
}

void test_short_record_is_rejected(void) {
  PetSnapshot pet = pet_with(40, 70, 55, 80, true);
  uint8_t buf[kPetRecordV1Size];
  size_t written = 0;
  TEST_ASSERT_TRUE(pet_record_encode(pet, buf, sizeof buf, &written));

  PetSnapshot out;
  TEST_ASSERT_FALSE(pet_record_decode(buf, written - 1, &out));
}

void test_unknown_version_is_rejected(void) {
  PetSnapshot pet = pet_with(40, 70, 55, 80, false);
  uint8_t buf[kPetRecordV1Size];
  size_t written = 0;
  TEST_ASSERT_TRUE(pet_record_encode(pet, buf, sizeof buf, &written));
  buf[4] = 99;
  const uint16_t crc = crc16(buf, written - 2);
  buf[written - 2] = static_cast<uint8_t>(crc);
  buf[written - 1] = static_cast<uint8_t>(crc >> 8);

  PetSnapshot out;
  TEST_ASSERT_FALSE(pet_record_decode(buf, written, &out));
}

void test_v1_extra_tail_keeps_known_fields(void) {
  uint8_t buf[20] = {};
  buf[0] = 'Z';
  buf[1] = 'U';
  buf[2] = 'M';
  buf[3] = 'I';
  buf[4] = 1;
  buf[5] = 12;
  buf[6] = static_cast<uint8_t>(PHASE_ADULT);
  buf[7] = 40;
  buf[8] = 70;
  buf[9] = 55;
  buf[10] = 80;
  buf[11] = 0;
  buf[16] = 0xAB;
  buf[17] = 0xCD;
  const uint16_t crc = crc16(buf, 18);
  buf[18] = static_cast<uint8_t>(crc);
  buf[19] = static_cast<uint8_t>(crc >> 8);

  PetSnapshot out;
  TEST_ASSERT_TRUE(pet_record_decode(buf, sizeof buf, &out));
  expect_bars(out, 40, 70, 55, 80);
  TEST_ASSERT_EQUAL(PHASE_ADULT, out.phase);
  TEST_ASSERT_FALSE(out.asleep);
}

void test_bar_above_100_is_rejected(void) {
  PetSnapshot pet = pet_with(101, 70, 55, 80, false);
  uint8_t buf[kPetRecordV1Size];
  size_t written = 0;
  TEST_ASSERT_FALSE(pet_record_encode(pet, buf, sizeof buf, &written));
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  UNITY_BEGIN();
  RUN_TEST(test_case_power_cut_keeps_awake_bars);
  RUN_TEST(test_case_power_cut_keeps_sleep);
  RUN_TEST(test_case_drawer_hours_do_not_decay);
  RUN_TEST(test_case_first_boot_is_newborn);
  RUN_TEST(test_case_invalid_record_is_newborn);
  RUN_TEST(test_flipped_byte_does_not_decode);
  RUN_TEST(test_short_record_is_rejected);
  RUN_TEST(test_unknown_version_is_rejected);
  RUN_TEST(test_v1_extra_tail_keeps_known_fields);
  RUN_TEST(test_bar_above_100_is_rejected);
  return UNITY_END();
}

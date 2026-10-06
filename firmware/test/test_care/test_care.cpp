#include <unity.h>

#include "domain/care.hpp"

static const uint32_t kHourMs = 60u * 60u * 1000u;

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

void test_case_forget_awake_one_hour(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  care_advance(pet, kHourMs);
  expect_bars(pet, 92, 94, 90, 96);
  TEST_ASSERT_FALSE(pet.asleep);
}

void test_case_feed_fills_and_clamps(void) {
  PetSnapshot hungry = pet_with(50, 100, 100, 100, false);
  TEST_ASSERT_TRUE(care_apply(hungry, CARE_FEED));
  TEST_ASSERT_EQUAL_UINT8(90, hungry.bars.hunger);

  PetSnapshot almost = pet_with(80, 100, 100, 100, false);
  TEST_ASSERT_TRUE(care_apply(almost, CARE_FEED));
  TEST_ASSERT_EQUAL_UINT8(100, almost.bars.hunger);
}

void test_case_play_refuses_below_15_and_spends_at_15(void) {
  PetSnapshot tired = pet_with(100, 14, 50, 100, false);
  TEST_ASSERT_FALSE(care_apply(tired, CARE_PLAY));
  expect_bars(tired, 100, 14, 50, 100);
  TEST_ASSERT_FALSE(tired.asleep);

  PetSnapshot ready = pet_with(100, 15, 50, 100, false);
  TEST_ASSERT_TRUE(care_apply(ready, CARE_PLAY));
  expect_bars(ready, 100, 0, 90, 100);
}

void test_case_bath(void) {
  PetSnapshot pet = pet_with(100, 100, 30, 40, false);
  TEST_ASSERT_TRUE(care_apply(pet, CARE_BATHE));
  expect_bars(pet, 100, 100, 20, 90);
}

void test_case_sleep_five_hours_wakes_at_full_energy(void) {
  PetSnapshot pet = pet_with(100, 0, 100, 100, false);
  TEST_ASSERT_TRUE(care_apply(pet, CARE_SLEEP));
  care_advance(pet, 5u * kHourMs);
  expect_bars(pet, 80, 100, 90, 100);
  TEST_ASSERT_FALSE(pet.asleep);
}

void test_case_wake_keeps_bars(void) {
  PetSnapshot pet = pet_with(70, 40, 55, 60, true);
  TEST_ASSERT_TRUE(care_apply(pet, CARE_WAKE));
  expect_bars(pet, 70, 40, 55, 60);
  TEST_ASSERT_FALSE(pet.asleep);
}

void test_case_care_while_asleep_is_refused(void) {
  PetSnapshot feeding = pet_with(40, 20, 30, 50, true);
  TEST_ASSERT_FALSE(care_apply(feeding, CARE_FEED));
  expect_bars(feeding, 40, 20, 30, 50);
  TEST_ASSERT_TRUE(feeding.asleep);

  PetSnapshot playing = pet_with(40, 20, 30, 50, true);
  TEST_ASSERT_FALSE(care_apply(playing, CARE_PLAY));
  expect_bars(playing, 40, 20, 30, 50);
  TEST_ASSERT_TRUE(playing.asleep);

  PetSnapshot bathing = pet_with(40, 20, 30, 50, true);
  TEST_ASSERT_FALSE(care_apply(bathing, CARE_BATHE));
  expect_bars(bathing, 40, 20, 30, 50);
  TEST_ASSERT_TRUE(bathing.asleep);
}

void test_case_half_hour_is_half_the_hourly_step(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  care_advance(pet, kHourMs / 2u);
  expect_bars(pet, 96, 97, 95, 98);
}

void test_sleep_and_wake_refuse_when_already_in_that_state(void) {
  PetSnapshot awake = pet_snapshot_newborn(0);
  TEST_ASSERT_FALSE(care_apply(awake, CARE_WAKE));
  TEST_ASSERT_FALSE(awake.asleep);

  PetSnapshot asleep = pet_with(100, 10, 100, 100, true);
  TEST_ASSERT_FALSE(care_apply(asleep, CARE_SLEEP));
  TEST_ASSERT_TRUE(asleep.asleep);
  expect_bars(asleep, 100, 10, 100, 100);
}

void test_same_hour_twice_matches(void) {
  PetSnapshot first = pet_snapshot_newborn(0);
  PetSnapshot second = pet_snapshot_newborn(5000);
  care_advance(first, kHourMs);
  care_advance(second, kHourMs);
  expect_bars(second, first.bars.hunger, first.bars.energy, first.bars.fun, first.bars.hygiene);
  TEST_ASSERT_EQUAL(first.asleep, second.asleep);
}

void test_time_after_waking_uses_awake_rates(void) {
  PetSnapshot pet = pet_with(100, 0, 100, 100, true);
  care_advance(pet, 6u * kHourMs);
  expect_bars(pet, 72, 94, 80, 96);
  TEST_ASSERT_FALSE(pet.asleep);
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  UNITY_BEGIN();
  RUN_TEST(test_case_forget_awake_one_hour);
  RUN_TEST(test_case_feed_fills_and_clamps);
  RUN_TEST(test_case_play_refuses_below_15_and_spends_at_15);
  RUN_TEST(test_case_bath);
  RUN_TEST(test_case_sleep_five_hours_wakes_at_full_energy);
  RUN_TEST(test_case_wake_keeps_bars);
  RUN_TEST(test_case_care_while_asleep_is_refused);
  RUN_TEST(test_case_half_hour_is_half_the_hourly_step);
  RUN_TEST(test_sleep_and_wake_refuse_when_already_in_that_state);
  RUN_TEST(test_same_hour_twice_matches);
  RUN_TEST(test_time_after_waking_uses_awake_rates);
  return UNITY_END();
}

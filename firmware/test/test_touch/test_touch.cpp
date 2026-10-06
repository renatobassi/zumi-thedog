#include <string.h>

#include <unity.h>

#include "domain/care.hpp"
#include "ui/screen.hpp"

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

static CareTarget target_named(const PetSnapshot& pet, const char* label) {
  const ZumiFrame frame = zumi_frame(pet);
  for (int i = 0; i < 4; ++i) {
    if (strcmp(frame.targets[i].label, label) == 0) {
      return frame.targets[i];
    }
  }
  TEST_FAIL_MESSAGE("alvo ausente");
  return frame.targets[0];
}

static TouchOutcome tap(PetSnapshot& pet, const char* label) {
  const CareTarget target = target_named(pet, label);
  return touch_at(pet, target.x + target.w / 2, target.y + target.h / 2);
}

void test_feed_raises_hunger_and_says_so(void) {
  PetSnapshot pet = pet_with(50, 100, 100, 100, false);
  const TouchOutcome outcome = tap(pet, "Comer");
  TEST_ASSERT_TRUE(outcome.attempted);
  TEST_ASSERT_TRUE(outcome.accepted);
  TEST_ASSERT_EQUAL_STRING("Comeu", outcome.notice);
  TEST_ASSERT_EQUAL_UINT8(90, pet.bars.hunger);
}

void test_play_without_energy_is_refused(void) {
  PetSnapshot pet = pet_with(50, 14, 40, 80, false);
  const TouchOutcome outcome = tap(pet, "Brincar");
  TEST_ASSERT_TRUE(outcome.attempted);
  TEST_ASSERT_FALSE(outcome.accepted);
  TEST_ASSERT_EQUAL_STRING("Nao brincou", outcome.notice);
  expect_bars(pet, 50, 14, 40, 80);
  TEST_ASSERT_FALSE(pet.asleep);
}

void test_sleep_target_becomes_wake(void) {
  PetSnapshot pet = pet_with(80, 40, 70, 60, false);
  const TouchOutcome slept = tap(pet, "Dormir");
  TEST_ASSERT_TRUE(slept.accepted);
  TEST_ASSERT_EQUAL_STRING("Dormiu", slept.notice);
  TEST_ASSERT_TRUE(pet.asleep);
  expect_bars(pet, 80, 40, 70, 60);
  TEST_ASSERT_EQUAL_STRING("Acordar", zumi_frame(pet).targets[2].label);

  const TouchOutcome woke = tap(pet, "Acordar");
  TEST_ASSERT_TRUE(woke.accepted);
  TEST_ASSERT_EQUAL_STRING("Acordou", woke.notice);
  TEST_ASSERT_FALSE(pet.asleep);
  expect_bars(pet, 80, 40, 70, 60);
  TEST_ASSERT_EQUAL_STRING("Dormir", zumi_frame(pet).targets[2].label);
}

void test_care_while_asleep_shows_refusal(void) {
  const char* labels[3] = {"Comer", "Brincar", "Banho"};
  for (int i = 0; i < 3; ++i) {
    PetSnapshot pet = pet_with(40, 20, 30, 50, true);
    const TouchOutcome outcome = tap(pet, labels[i]);
    TEST_ASSERT_TRUE(outcome.attempted);
    TEST_ASSERT_FALSE(outcome.accepted);
    TEST_ASSERT_EQUAL_STRING("Esta dormindo", outcome.notice);
    expect_bars(pet, 40, 20, 30, 50);
    TEST_ASSERT_TRUE(pet.asleep);
  }
}

void test_miss_does_nothing(void) {
  PetSnapshot pet = pet_with(50, 50, 50, 50, false);
  const TouchOutcome outcome = touch_at(pet, 0, 0);
  TEST_ASSERT_FALSE(outcome.attempted);
  TEST_ASSERT_NULL(outcome.notice);
  expect_bars(pet, 50, 50, 50, 50);
  TEST_ASSERT_FALSE(pet.asleep);
}

void test_gap_between_targets_is_a_miss(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  const ZumiFrame frame = zumi_frame(pet);
  const int y = frame.targets[0].y + frame.targets[0].h + 1;
  TEST_ASSERT_TRUE(y < frame.targets[1].y);
  const TouchOutcome outcome = touch_at(pet, frame.targets[0].x + 4, y);
  TEST_ASSERT_FALSE(outcome.attempted);
  expect_bars(pet, 100, 100, 100, 100);
}

void test_hold_does_not_repeat_until_release_and_gap(void) {
  TouchLatch latch = {false, 0};
  TEST_ASSERT_TRUE(touch_accept(latch, true, 1000));
  TEST_ASSERT_FALSE(touch_accept(latch, true, 1100));
  TEST_ASSERT_FALSE(touch_accept(latch, false, 1200));
  TEST_ASSERT_FALSE(touch_accept(latch, true, 1000 + kTouchGapMs - 1));
  TEST_ASSERT_FALSE(touch_accept(latch, false, 1000 + kTouchGapMs - 1));
  TEST_ASSERT_TRUE(touch_accept(latch, true, 1000 + kTouchGapMs));
}

void test_notice_hides_itself(void) {
  CareNotice notice = {0, 0};
  TEST_ASSERT_NULL(care_notice_text(notice, 0));
  care_notice_show(notice, "Comeu", 5000);
  TEST_ASSERT_EQUAL_STRING("Comeu", care_notice_text(notice, 5000));
  TEST_ASSERT_EQUAL_STRING("Comeu", care_notice_text(notice, 5000 + kCareNoticeMs - 1));
  TEST_ASSERT_NULL(care_notice_text(notice, 5000 + kCareNoticeMs));
}

void test_bath_and_play_when_allowed(void) {
  PetSnapshot playing = pet_with(100, 15, 50, 100, false);
  const TouchOutcome played = tap(playing, "Brincar");
  TEST_ASSERT_TRUE(played.accepted);
  TEST_ASSERT_EQUAL_STRING("Brincou", played.notice);
  expect_bars(playing, 100, 0, 90, 100);

  PetSnapshot bathing = pet_with(100, 100, 30, 40, false);
  const TouchOutcome bathed = tap(bathing, "Banho");
  TEST_ASSERT_TRUE(bathed.accepted);
  TEST_ASSERT_EQUAL_STRING("Banhou", bathed.notice);
  expect_bars(bathing, 100, 100, 20, 90);
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  UNITY_BEGIN();
  RUN_TEST(test_feed_raises_hunger_and_says_so);
  RUN_TEST(test_play_without_energy_is_refused);
  RUN_TEST(test_sleep_target_becomes_wake);
  RUN_TEST(test_care_while_asleep_shows_refusal);
  RUN_TEST(test_miss_does_nothing);
  RUN_TEST(test_gap_between_targets_is_a_miss);
  RUN_TEST(test_hold_does_not_repeat_until_release_and_gap);
  RUN_TEST(test_notice_hides_itself);
  RUN_TEST(test_bath_and_play_when_allowed);
  return UNITY_END();
}

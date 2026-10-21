#include <unity.h>

#include "domain/mood.hpp"
#include "ui/frame.hpp"

void setUp(void) {}
void tearDown(void) {}

static PetSnapshot well() {
  return pet_snapshot_newborn(0);
}

void test_case_wag_when_well(void) {
  TEST_ASSERT_EQUAL(MOOD_WAG, mood_choose(well(), CARE_FEED, false));
}

void test_case_hungry_beats_wag(void) {
  PetSnapshot pet = well();
  pet.bars.hunger = 25;
  TEST_ASSERT_EQUAL(MOOD_HUNGRY, mood_choose(pet, CARE_FEED, false));
}

void test_case_sleep_beats_hungry(void) {
  PetSnapshot pet = well();
  pet.bars.hunger = 10;
  pet.asleep = true;
  TEST_ASSERT_EQUAL(MOOD_SLEEP, mood_choose(pet, CARE_FEED, false));
}

void test_case_sick_beats_hungry(void) {
  PetSnapshot pet = well();
  pet.bars.hunger = 10;
  pet.sick = true;
  TEST_ASSERT_EQUAL(MOOD_SICK, mood_choose(pet, CARE_FEED, false));
}

void test_case_action_window(void) {
  PetSnapshot pet = well();
  TEST_ASSERT_EQUAL(MOOD_ACTION_PLAY, mood_choose(pet, CARE_PLAY, true));
  TEST_ASSERT_EQUAL(MOOD_WAG, mood_choose(pet, CARE_PLAY, false));
}

void test_case_refused_action_does_not_animate(void) {
  PetSnapshot pet = well();
  pet.sick = true;
  TEST_ASSERT_EQUAL(MOOD_SICK, mood_choose(pet, CARE_PLAY, false));
}

void test_case_street_has_no_care_pose(void) {
  PetSnapshot pet = well();
  pet.on_street = true;
  TEST_ASSERT_EQUAL(MOOD_STREET, mood_choose(pet, CARE_FEED, true));
  TEST_ASSERT_EQUAL_INT(POSE_NONE, zumi_frame(pet).pose);
}

void test_wag_alternates_frames(void) {
  PetSnapshot pet = well();
  MoodView mood;
  mood.action = CARE_FEED;
  mood.action_until_ms = 0;
  mood.now_ms = 0;
  TEST_ASSERT_EQUAL_INT(POSE_MANTA, zumi_frame(pet, mood).pose);
  mood.now_ms = mood_frame_period_ms(MOOD_WAG);
  TEST_ASSERT_EQUAL_INT(POSE_WAG_B, zumi_frame(pet, mood).pose);
  TEST_ASSERT_TRUE(pose_versioned(POSE_SLEEP));
  TEST_ASSERT_TRUE(pose_versioned(POSE_HUNGRY));
  TEST_ASSERT_TRUE(pose_versioned(POSE_SICK));
  TEST_ASSERT_TRUE(sprite_view(POSE_SLEEP).width > 0);
}

void test_action_reuses_wag_frames(void) {
  PetSnapshot pet = well();
  MoodView mood;
  mood.action = CARE_FEED;
  mood.action_until_ms = kMoodActionMs;
  mood.now_ms = 0;
  TEST_ASSERT_EQUAL(MOOD_ACTION_FEED, zumi_frame(pet, mood).mood);
  TEST_ASSERT_EQUAL_INT(POSE_MANTA, zumi_frame(pet, mood).pose);
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  UNITY_BEGIN();
  RUN_TEST(test_case_wag_when_well);
  RUN_TEST(test_case_hungry_beats_wag);
  RUN_TEST(test_case_sleep_beats_hungry);
  RUN_TEST(test_case_sick_beats_hungry);
  RUN_TEST(test_case_action_window);
  RUN_TEST(test_case_refused_action_does_not_animate);
  RUN_TEST(test_case_street_has_no_care_pose);
  RUN_TEST(test_wag_alternates_frames);
  RUN_TEST(test_action_reuses_wag_frames);
  return UNITY_END();
}

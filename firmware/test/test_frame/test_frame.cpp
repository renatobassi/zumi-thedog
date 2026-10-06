#include <unity.h>

#include "ui/frame.hpp"

void setUp(void) {}
void tearDown(void) {}

static bool inside_screen(int x, int y, int w, int h) {
  return x >= 0 && y >= 0 && w > 0 && h > 0 && x + w <= kZumiScreenW && y + h <= kZumiScreenH;
}

void test_newborn_shows_blanket_and_full_bars(void) {
  const PetSnapshot pet = pet_snapshot_newborn(0);
  const ZumiFrame frame = zumi_frame(pet);

  TEST_ASSERT_EQUAL_INT(POSE_MANTA, frame.pose);
  TEST_ASSERT_TRUE(inside_screen(frame.dog_x, frame.dog_y, frame.dog_w, frame.dog_h));
  TEST_ASSERT_EQUAL_STRING("Fome", frame.bars[0].name);
  TEST_ASSERT_EQUAL_STRING("Energia", frame.bars[1].name);
  TEST_ASSERT_EQUAL_STRING("Diversao", frame.bars[2].name);
  TEST_ASSERT_EQUAL_STRING("Higiene", frame.bars[3].name);

  for (int i = 0; i < 4; ++i) {
    const int y = frame.track_y + i * frame.track_pitch;
    TEST_ASSERT_EQUAL_UINT8(100, frame.bars[i].value);
    TEST_ASSERT_EQUAL_INT(kZumiBarTrackPx, frame.bars[i].fill_px);
    TEST_ASSERT_TRUE(inside_screen(frame.track_x, y, frame.track_w, frame.track_h));
    TEST_ASSERT_TRUE(frame.dog_y + frame.dog_h <= y);
  }
}

void test_low_hunger_is_shorter(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  pet.bars.hunger = 20;
  const ZumiFrame frame = zumi_frame(pet);

  TEST_ASSERT_EQUAL_INT(bar_fill_px(20), frame.bars[0].fill_px);
  TEST_ASSERT_TRUE(frame.bars[0].fill_px < frame.bars[1].fill_px);
  TEST_ASSERT_EQUAL_INT(frame.bars[1].fill_px, frame.bars[2].fill_px);
  TEST_ASSERT_EQUAL_INT(frame.bars[2].fill_px, frame.bars[3].fill_px);
  TEST_ASSERT_EQUAL_INT(0, bar_fill_px(0));
}

void test_later_phase_falls_back_to_blanket(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  pet.phase = PHASE_PUPPY;
  TEST_ASSERT_EQUAL_INT(POSE_MANTA, zumi_frame(pet).pose);
  pet.phase = PHASE_ADULT_SITTING;
  TEST_ASSERT_EQUAL_INT(POSE_MANTA, zumi_frame(pet).pose);
  pet.phase = PHASE_ADULT;
  TEST_ASSERT_EQUAL_INT(POSE_MANTA, zumi_frame(pet).pose);
}

static bool overlaps(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) {
  return ax < bx + bw && bx < ax + aw && ay < by + bh && by < ay + ah;
}

void test_four_targets_fit_beside_the_bars(void) {
  const PetSnapshot awake = pet_snapshot_newborn(0);
  const ZumiFrame frame = zumi_frame(awake);

  TEST_ASSERT_EQUAL_STRING("Comer", frame.targets[0].label);
  TEST_ASSERT_EQUAL_STRING("Brincar", frame.targets[1].label);
  TEST_ASSERT_EQUAL_STRING("Dormir", frame.targets[2].label);
  TEST_ASSERT_EQUAL_STRING("Banho", frame.targets[3].label);
  TEST_ASSERT_EQUAL_INT(TOUCH_FEED, frame.targets[0].action);
  TEST_ASSERT_EQUAL_INT(TOUCH_PLAY, frame.targets[1].action);
  TEST_ASSERT_EQUAL_INT(TOUCH_SLEEP, frame.targets[2].action);
  TEST_ASSERT_EQUAL_INT(TOUCH_BATH, frame.targets[3].action);

  for (int i = 0; i < 4; ++i) {
    const CareTarget& target = frame.targets[i];
    TEST_ASSERT_TRUE(inside_screen(target.x, target.y, target.w, target.h));
    TEST_ASSERT_TRUE(target.w >= 64);
    TEST_ASSERT_TRUE(target.h >= 48);
    TEST_ASSERT_TRUE(target.x >= frame.dog_x + frame.dog_w);
    for (int b = 0; b < 4; ++b) {
      const int y = frame.track_y + b * frame.track_pitch;
      TEST_ASSERT_FALSE(overlaps(target.x, target.y, target.w, target.h, frame.track_x, y, frame.track_w, frame.track_h));
      TEST_ASSERT_FALSE(overlaps(target.x, target.y, target.w, target.h, 4, y, 70, frame.track_h));
    }
    TEST_ASSERT_TRUE(frame.notice_y + 16 <= kZumiScreenH);
    TEST_ASSERT_FALSE(overlaps(target.x, target.y, target.w, target.h, frame.notice_x, frame.notice_y, 150, 16));
  }
}

void test_sleep_target_says_wake(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  pet.asleep = true;
  const ZumiFrame frame = zumi_frame(pet);
  TEST_ASSERT_EQUAL_STRING("Acordar", frame.targets[2].label);
  TEST_ASSERT_EQUAL_STRING("Comer", frame.targets[0].label);
  TEST_ASSERT_EQUAL_INT(TOUCH_SLEEP, frame.targets[2].action);
}

void test_sleep_without_sprite_keeps_phase_pose(void) {
  PetSnapshot pet = pet_snapshot_newborn(0);
  pet.asleep = true;
  TEST_ASSERT_FALSE(pose_versioned(POSE_SLEEP));
  TEST_ASSERT_EQUAL_INT(POSE_MANTA, zumi_frame(pet).pose);

  const SpriteView sprite = sprite_view(POSE_MANTA);
  TEST_ASSERT_NOT_NULL(sprite.pixels);
  TEST_ASSERT_TRUE(sprite.width > 0);
  TEST_ASSERT_TRUE(sprite.height > 0);
  TEST_ASSERT_EQUAL_INT(0, sprite_view(POSE_SLEEP).width);
  TEST_ASSERT_EQUAL_INT(0, sprite_view(POSE_NONE).width);
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  UNITY_BEGIN();
  RUN_TEST(test_newborn_shows_blanket_and_full_bars);
  RUN_TEST(test_low_hunger_is_shorter);
  RUN_TEST(test_later_phase_falls_back_to_blanket);
  RUN_TEST(test_four_targets_fit_beside_the_bars);
  RUN_TEST(test_sleep_target_says_wake);
  RUN_TEST(test_sleep_without_sprite_keeps_phase_pose);
  return UNITY_END();
}

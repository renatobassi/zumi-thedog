#include "frame.hpp"

#include "manta_pixels.hpp"

namespace {

const char* kBarNames[4] = {"Fome", "Energia", "Diversao", "Higiene"};

PoseId pose_for_phase(Phase phase) {
  switch (phase) {
  case PHASE_BLANKET:
    return POSE_MANTA;
  case PHASE_PUPPY:
  case PHASE_ADULT_SITTING:
  case PHASE_ADULT:
    return POSE_NONE;
  }
  return POSE_NONE;
}

}  // namespace

bool pose_versioned(PoseId pose) {
  return pose == POSE_MANTA;
}

PoseId zumi_pose(Phase phase, bool asleep) {
  if (asleep && pose_versioned(POSE_SLEEP)) {
    return POSE_SLEEP;
  }

  Phase current = phase;
  for (;;) {
    const PoseId pose = pose_for_phase(current);
    if (pose_versioned(pose)) {
      return pose;
    }
    if (current == PHASE_BLANKET) {
      return POSE_NONE;
    }
    current = static_cast<Phase>(static_cast<int>(current) - 1);
  }
}

int bar_fill_px(uint8_t value) {
  return static_cast<int>(value) * kZumiBarTrackPx / 100;
}

SpriteView sprite_view(PoseId pose) {
  SpriteView view;
  view.pixels = 0;
  view.width = 0;
  view.height = 0;
  if (pose == POSE_MANTA) {
    view.pixels = kMantaPixels;
    view.width = kMantaWidth;
    view.height = kMantaHeight;
  }
  return view;
}

const int kCareColumnX = 198;
const int kCareTargetW = 118;
const int kCareTargetH = 54;
const int kCareTargetGap = 6;

const TouchAction kCareActions[4] = {TOUCH_FEED, TOUCH_PLAY, TOUCH_SLEEP, TOUCH_BATH};
const char* kCareAwake[4] = {"Comer", "Brincar", "Dormir", "Banho"};

ZumiFrame zumi_frame(const PetSnapshot& pet) {
  ZumiFrame frame;
  frame.pose = zumi_pose(pet.phase, pet.asleep);

  const int column_w = kCareColumnX - 8;
  const SpriteView sprite = sprite_view(frame.pose);
  frame.dog_w = sprite.width * kZumiSpriteScale;
  frame.dog_h = sprite.height * kZumiSpriteScale;
  frame.dog_x = sprite.width > 0 ? 4 + (column_w - frame.dog_w) / 2 : 0;
  frame.dog_y = 2;

  frame.track_x = 82;
  frame.track_y = frame.dog_y + frame.dog_h + 8;
  frame.track_w = kZumiBarTrackPx;
  frame.track_h = 16;
  frame.track_pitch = 22;

  const uint8_t values[4] = {pet.bars.hunger, pet.bars.energy, pet.bars.fun, pet.bars.hygiene};
  for (int i = 0; i < 4; ++i) {
    frame.bars[i].name = kBarNames[i];
    frame.bars[i].value = values[i];
    frame.bars[i].fill_px = bar_fill_px(values[i]);
  }

  frame.notice_x = 4;
  frame.notice_y = frame.track_y + 3 * frame.track_pitch + frame.track_h + 6;

  for (int i = 0; i < 4; ++i) {
    frame.targets[i].action = kCareActions[i];
    frame.targets[i].label = (pet.asleep && kCareActions[i] == TOUCH_SLEEP) ? "Acordar" : kCareAwake[i];
    frame.targets[i].x = kCareColumnX;
    frame.targets[i].y = 4 + i * (kCareTargetH + kCareTargetGap);
    frame.targets[i].w = kCareTargetW;
    frame.targets[i].h = kCareTargetH;
  }

  return frame;
}

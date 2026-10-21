#include "frame.hpp"

#include "manta_pixels.hpp"

namespace {

const char* kBarNames[4] = {"Fome", "Energia", "Diversao", "Higiene"};

PoseId pose_for_phase(Phase phase) {
  switch (phase) {
  case PHASE_BLANKET:
    // Até o filhote na manta existir no repo, a tela reutiliza o adulto versionado.
    return POSE_MANTA;
  case PHASE_PUPPY:
    return POSE_NONE;
  case PHASE_ADULT_SITTING:
    return POSE_MANTA;
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

const TouchAction kCareActions[4] = {TOUCH_FEED, TOUCH_PLAY, TOUCH_SLEEP, TOUCH_BATH};
const char* kCareAwake[4] = {"Comer", "Brincar", "Dormir", "Banho"};

ZumiFrame zumi_frame(const PetSnapshot& pet) {
  ZumiFrame frame;
  frame.pose = pet.on_street ? POSE_NONE : zumi_pose(pet.phase, pet.asleep);
  frame.status = 0;
  if (pet.on_street) {
    frame.status = "Voltou pra rua";
  } else if (pet.sick) {
    frame.status = "Doente";
  }

  const SpriteView sprite = sprite_view(frame.pose);
  frame.dog_w = sprite.width * kZumiSpriteScale;
  frame.dog_h = sprite.height * kZumiSpriteScale;
  frame.dog_x = sprite.width > 0 ? (kZumiScreenW - frame.dog_w) / 2 : 0;
  frame.dog_y = kZumiDockY - frame.dog_h;

  frame.track_w = kZumiBarTrackPx;
  frame.track_h = 8;

  frame.notice_x = 8;
  frame.notice_y = kZumiDockY - 18;

  const uint8_t values[4] = {pet.bars.hunger, pet.bars.energy, pet.bars.fun, pet.bars.hygiene};
  for (int i = 0; i < 4; ++i) {
    frame.bars[i].name = kBarNames[i];
    frame.bars[i].value = values[i];
    frame.bars[i].fill_px = bar_fill_px(values[i]);
    frame.bars[i].x = 0;
    frame.bars[i].y = 0;
    frame.targets[i].action = TOUCH_NONE;
    frame.targets[i].label = "";
    frame.targets[i].x = 0;
    frame.targets[i].y = 0;
    frame.targets[i].w = 0;
    frame.targets[i].h = 0;
  }

  if (pet.on_street) {
    frame.target_count = 1;
    frame.targets[0].action = TOUCH_ADOPT;
    frame.targets[0].label = "Adotar";
    frame.targets[0].x = 40;
    frame.targets[0].y = kZumiDockY;
    frame.targets[0].w = 240;
    frame.targets[0].h = kZumiDockH;
    return frame;
  }

  frame.target_count = 4;
  for (int i = 0; i < 4; ++i) {
    frame.targets[i].action = kCareActions[i];
    frame.targets[i].label = (pet.asleep && kCareActions[i] == TOUCH_SLEEP) ? "Acordar" : kCareAwake[i];
    frame.targets[i].x = kZumiDockX + i * (kZumiDockW + kZumiDockGap);
    frame.targets[i].y = kZumiDockY;
    frame.targets[i].w = kZumiDockW;
    frame.targets[i].h = kZumiDockH;

    frame.bars[i].x = frame.targets[i].x + (kZumiDockW - kZumiBarTrackPx) / 2;
    frame.bars[i].y = frame.targets[i].y + 36;
  }

  return frame;
}

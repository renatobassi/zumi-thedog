#include "screen.hpp"

#include "../domain/care.hpp"

namespace {

bool inside(const CareTarget& target, int x, int y) {
  return x >= target.x && y >= target.y && x < target.x + target.w && y < target.y + target.h;
}

TouchAction hit_action(const ZumiFrame& frame, int x, int y) {
  for (int i = 0; i < 4; ++i) {
    if (inside(frame.targets[i], x, y)) {
      return frame.targets[i].action;
    }
  }
  return TOUCH_NONE;
}

CareAction care_for(TouchAction touch, bool asleep) {
  switch (touch) {
  case TOUCH_FEED:
    return CARE_FEED;
  case TOUCH_PLAY:
    return CARE_PLAY;
  case TOUCH_BATH:
    return CARE_BATHE;
  case TOUCH_SLEEP:
    return asleep ? CARE_WAKE : CARE_SLEEP;
  case TOUCH_NONE:
    break;
  }
  return CARE_FEED;
}

const char* notice_for(TouchAction touch, bool was_asleep, bool accepted) {
  if (!accepted) {
    if (was_asleep) {
      return "Esta dormindo";
    }
    return "Nao brincou";
  }
  switch (touch) {
  case TOUCH_FEED:
    return "Comeu";
  case TOUCH_PLAY:
    return "Brincou";
  case TOUCH_BATH:
    return "Banhou";
  case TOUCH_SLEEP:
    return was_asleep ? "Acordou" : "Dormiu";
  case TOUCH_NONE:
    break;
  }
  return 0;
}

}  // namespace

TouchOutcome touch_at(PetSnapshot& pet, int x, int y) {
  TouchOutcome outcome;
  outcome.attempted = false;
  outcome.accepted = false;
  outcome.notice = 0;

  const TouchAction touch = hit_action(zumi_frame(pet), x, y);
  if (touch == TOUCH_NONE) {
    return outcome;
  }

  const bool was_asleep = pet.asleep;
  outcome.attempted = true;
  outcome.accepted = care_apply(pet, care_for(touch, was_asleep));
  outcome.notice = notice_for(touch, was_asleep, outcome.accepted);
  return outcome;
}

bool touch_accept(TouchLatch& latch, bool pressed, uint32_t now_ms) {
  if (!pressed) {
    latch.held = false;
    return false;
  }
  if (latch.held || now_ms < latch.ready_at_ms) {
    latch.held = true;
    return false;
  }
  latch.held = true;
  latch.ready_at_ms = now_ms + kTouchGapMs;
  return true;
}

void care_notice_show(CareNotice& notice, const char* text, uint32_t now_ms) {
  notice.text = text;
  notice.hide_at_ms = now_ms + kCareNoticeMs;
}

const char* care_notice_text(const CareNotice& notice, uint32_t now_ms) {
  if (notice.text == 0 || now_ms >= notice.hide_at_ms) {
    return 0;
  }
  return notice.text;
}

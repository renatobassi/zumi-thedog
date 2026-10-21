#include "mood.hpp"

namespace {

int bar_avg(const Bars& bars) {
  return (static_cast<int>(bars.hunger) + static_cast<int>(bars.energy) + static_cast<int>(bars.fun) +
          static_cast<int>(bars.hygiene)) /
         4;
}

bool is_action(CareAction action) {
  return action == CARE_FEED || action == CARE_PLAY || action == CARE_BATHE;
}

}  // namespace

MoodId mood_choose(const PetSnapshot& pet, CareAction action, bool action_live) {
  if (pet.on_street) {
    return MOOD_STREET;
  }
  if (action_live && is_action(action)) {
    if (action == CARE_FEED) {
      return MOOD_ACTION_FEED;
    }
    if (action == CARE_PLAY) {
      return MOOD_ACTION_PLAY;
    }
    return MOOD_ACTION_BATH;
  }
  if (pet.asleep) {
    return MOOD_SLEEP;
  }
  if (pet.sick) {
    return MOOD_SICK;
  }
  if (pet.bars.hunger <= 25) {
    return MOOD_HUNGRY;
  }
  if (bar_avg(pet.bars) > 60) {
    return MOOD_WAG;
  }
  return MOOD_PHASE;
}

uint32_t mood_frame_period_ms(MoodId mood) {
  switch (mood) {
  case MOOD_WAG:
    return 1000u / 6u;
  case MOOD_ACTION_PLAY:
    return 1000u / 4u;
  case MOOD_ACTION_FEED:
  case MOOD_ACTION_BATH:
    return 1000u / 3u;
  case MOOD_SLEEP:
    return 1000u / 2u;
  case MOOD_STREET:
  case MOOD_SICK:
  case MOOD_HUNGRY:
  case MOOD_PHASE:
    break;
  }
  return 0;
}

int mood_frame_index(MoodId mood, uint32_t now_ms) {
  const uint32_t period = mood_frame_period_ms(mood);
  if (period == 0) {
    return 0;
  }
  return static_cast<int>((now_ms / period) % 2u);
}

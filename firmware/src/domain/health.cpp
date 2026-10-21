#include "health.hpp"

void health_advance(PetSnapshot& pet, uint32_t elapsed_ms) {
  if (pet.on_street || elapsed_ms == 0) {
    return;
  }

  if (pet.sick) {
    if (pet.bars.hunger >= kRecoverBar && pet.bars.energy >= kRecoverBar) {
      pet.sick = false;
      pet.sick_ms = 0;
      pet.low_ms = 0;
      return;
    }
    pet.sick_ms += elapsed_ms;
    if (pet.sick_ms >= kStreetAfterMs) {
      pet.sick_ms = kStreetAfterMs;
      pet.on_street = true;
    }
    return;
  }

  const bool critical = pet.bars.hunger <= kCriticalBar || pet.bars.energy <= kCriticalBar;
  if (!critical) {
    pet.low_ms = 0;
    return;
  }

  pet.low_ms += elapsed_ms;
  if (pet.low_ms < kSickAfterMs) {
    return;
  }

  pet.sick = true;
  pet.sick_ms = pet.low_ms - kSickAfterMs;
  pet.low_ms = kSickAfterMs;
  if (pet.sick_ms >= kStreetAfterMs) {
    pet.sick_ms = kStreetAfterMs;
    pet.on_street = true;
  }
}

bool health_adopt(PetSnapshot& pet, uint32_t now_ms) {
  if (!pet.on_street) {
    return false;
  }
  pet = pet_snapshot_newborn(now_ms);
  return true;
}

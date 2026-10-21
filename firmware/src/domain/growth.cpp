#include "growth.hpp"

Phase phase_for_age(uint32_t age_ms) {
  if (age_ms >= kGrowthAdultMs) {
    return PHASE_ADULT;
  }
  if (age_ms >= kGrowthAdultSittingMs) {
    return PHASE_ADULT_SITTING;
  }
  if (age_ms >= kGrowthPuppyMs) {
    return PHASE_PUPPY;
  }
  return PHASE_BLANKET;
}

void growth_advance(PetSnapshot& pet, uint32_t elapsed_ms) {
  pet.age_ms += elapsed_ms;
  pet.phase = phase_for_age(pet.age_ms);
}

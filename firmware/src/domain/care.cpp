#include "care.hpp"

namespace {

constexpr int kHourMs = 60 * 60 * 1000;

constexpr int kAwakeHunger = -8;
constexpr int kAwakeEnergy = -6;
constexpr int kAwakeFun = -10;
constexpr int kAwakeHygiene = -4;

constexpr int kAsleepHunger = -4;
constexpr int kAsleepEnergy = 20;
constexpr int kAsleepFun = -2;
constexpr int kAsleepHygiene = 0;

constexpr int kFeedHunger = 40;
constexpr int kPlayFun = 40;
constexpr int kPlayEnergy = -15;
constexpr int kPlayMinEnergy = 15;
constexpr int kBathHygiene = 50;
constexpr int kBathFun = -10;

int clamp_bar(int value) {
  if (value < 0) {
    return 0;
  }
  if (value > 100) {
    return 100;
  }
  return value;
}

int round_nearest(int64_t numer, int64_t denom) {
  if (numer >= 0) {
    return static_cast<int>((numer + denom / 2) / denom);
  }
  return -static_cast<int>(((-numer) + denom / 2) / denom);
}

int scaled(int per_hour, uint32_t elapsed_ms) {
  return round_nearest(static_cast<int64_t>(per_hour) * static_cast<int64_t>(elapsed_ms), kHourMs);
}

void apply_awake(Bars& bars, uint32_t elapsed_ms) {
  bars.hunger = static_cast<uint8_t>(clamp_bar(bars.hunger + scaled(kAwakeHunger, elapsed_ms)));
  bars.energy = static_cast<uint8_t>(clamp_bar(bars.energy + scaled(kAwakeEnergy, elapsed_ms)));
  bars.fun = static_cast<uint8_t>(clamp_bar(bars.fun + scaled(kAwakeFun, elapsed_ms)));
  bars.hygiene = static_cast<uint8_t>(clamp_bar(bars.hygiene + scaled(kAwakeHygiene, elapsed_ms)));
}

void apply_asleep(Bars& bars, uint32_t elapsed_ms) {
  bars.hunger = static_cast<uint8_t>(clamp_bar(bars.hunger + scaled(kAsleepHunger, elapsed_ms)));
  bars.energy = static_cast<uint8_t>(clamp_bar(bars.energy + scaled(kAsleepEnergy, elapsed_ms)));
  bars.fun = static_cast<uint8_t>(clamp_bar(bars.fun + scaled(kAsleepFun, elapsed_ms)));
  bars.hygiene = static_cast<uint8_t>(clamp_bar(bars.hygiene + scaled(kAsleepHygiene, elapsed_ms)));
}

uint32_t ms_until_energy_full(uint8_t energy) {
  const uint32_t missing = static_cast<uint32_t>(100 - energy);
  return missing * static_cast<uint32_t>(kHourMs) / static_cast<uint32_t>(kAsleepEnergy);
}

}  // namespace

bool care_apply(PetSnapshot& pet, CareAction action) {
  switch (action) {
  case CARE_FEED:
    if (pet.asleep) {
      return false;
    }
    pet.bars.hunger = static_cast<uint8_t>(clamp_bar(pet.bars.hunger + kFeedHunger));
    return true;
  case CARE_PLAY:
    if (pet.asleep || pet.bars.energy < kPlayMinEnergy) {
      return false;
    }
    pet.bars.fun = static_cast<uint8_t>(clamp_bar(pet.bars.fun + kPlayFun));
    pet.bars.energy = static_cast<uint8_t>(clamp_bar(pet.bars.energy + kPlayEnergy));
    return true;
  case CARE_BATHE:
    if (pet.asleep) {
      return false;
    }
    pet.bars.hygiene = static_cast<uint8_t>(clamp_bar(pet.bars.hygiene + kBathHygiene));
    pet.bars.fun = static_cast<uint8_t>(clamp_bar(pet.bars.fun + kBathFun));
    return true;
  case CARE_SLEEP:
    if (pet.asleep) {
      return false;
    }
    pet.asleep = true;
    return true;
  case CARE_WAKE:
    if (!pet.asleep) {
      return false;
    }
    pet.asleep = false;
    return true;
  }
  return false;
}

void care_advance(PetSnapshot& pet, uint32_t elapsed_ms) {
  if (pet.asleep && pet.bars.energy >= 100) {
    pet.asleep = false;
  }
  if (!pet.asleep) {
    apply_awake(pet.bars, elapsed_ms);
    return;
  }

  const uint32_t until_full = ms_until_energy_full(pet.bars.energy);
  if (elapsed_ms < until_full) {
    apply_asleep(pet.bars, elapsed_ms);
    if (pet.bars.energy >= 100) {
      pet.asleep = false;
    }
    return;
  }

  apply_asleep(pet.bars, until_full);
  pet.bars.energy = 100;
  pet.asleep = false;
  care_advance(pet, elapsed_ms - until_full);
}

#include "care.hpp"

#include "growth.hpp"
#include "health.hpp"

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

void apply_rate(uint8_t& bar, int per_hour, uint32_t elapsed_ms, int32_t& carry) {
  if (per_hour == 0 || elapsed_ms == 0) {
    return;
  }
  const int64_t acc = static_cast<int64_t>(carry) + static_cast<int64_t>(per_hour) * static_cast<int64_t>(elapsed_ms);
  const int64_t delta = acc / static_cast<int64_t>(kHourMs);
  carry = static_cast<int32_t>(acc % static_cast<int64_t>(kHourMs));
  if (delta != 0) {
    bar = static_cast<uint8_t>(clamp_bar(static_cast<int>(bar) + static_cast<int>(delta)));
  }
}

void apply_awake(Bars& bars, BarCarry& carry, uint32_t elapsed_ms) {
  apply_rate(bars.hunger, kAwakeHunger, elapsed_ms, carry.hunger);
  apply_rate(bars.energy, kAwakeEnergy, elapsed_ms, carry.energy);
  apply_rate(bars.fun, kAwakeFun, elapsed_ms, carry.fun);
  apply_rate(bars.hygiene, kAwakeHygiene, elapsed_ms, carry.hygiene);
}

void apply_asleep(Bars& bars, BarCarry& carry, uint32_t elapsed_ms) {
  apply_rate(bars.hunger, kAsleepHunger, elapsed_ms, carry.hunger);
  apply_rate(bars.energy, kAsleepEnergy, elapsed_ms, carry.energy);
  apply_rate(bars.fun, kAsleepFun, elapsed_ms, carry.fun);
  apply_rate(bars.hygiene, kAsleepHygiene, elapsed_ms, carry.hygiene);
}

uint32_t ms_until_energy_full(uint8_t energy, int32_t energy_carry) {
  if (energy >= 100) {
    return 0;
  }
  // Falta (100 - energy) pontos; o carry positivo já conta como progresso.
  int64_t need = (static_cast<int64_t>(100 - energy) * static_cast<int64_t>(kHourMs)) - static_cast<int64_t>(energy_carry);
  if (need <= 0) {
    return 0;
  }
  return static_cast<uint32_t>((need + kAsleepEnergy - 1) / kAsleepEnergy);
}

void advance_bars(PetSnapshot& pet, uint32_t elapsed_ms) {
  if (pet.asleep && pet.bars.energy >= 100) {
    pet.asleep = false;
  }
  if (!pet.asleep) {
    apply_awake(pet.bars, pet.bar_carry, elapsed_ms);
    return;
  }

  const uint32_t until_full = ms_until_energy_full(pet.bars.energy, pet.bar_carry.energy);
  if (until_full == 0) {
    apply_asleep(pet.bars, pet.bar_carry, 0);
    pet.bars.energy = 100;
    pet.bar_carry.energy = 0;
    pet.asleep = false;
    if (elapsed_ms > 0) {
      advance_bars(pet, elapsed_ms);
    }
    return;
  }
  if (elapsed_ms < until_full) {
    apply_asleep(pet.bars, pet.bar_carry, elapsed_ms);
    if (pet.bars.energy >= 100) {
      pet.bars.energy = 100;
      pet.bar_carry.energy = 0;
      pet.asleep = false;
    }
    return;
  }

  apply_asleep(pet.bars, pet.bar_carry, until_full);
  pet.bars.energy = 100;
  pet.bar_carry.energy = 0;
  pet.asleep = false;
  advance_bars(pet, elapsed_ms - until_full);
}

}  // namespace

bool care_apply(PetSnapshot& pet, CareAction action) {
  if (action == CARE_ADOPT) {
    return health_adopt(pet, pet.last_tick_ms);
  }
  if (pet.on_street) {
    return false;
  }

  switch (action) {
  case CARE_FEED:
    if (pet.asleep) {
      return false;
    }
    pet.bars.hunger = static_cast<uint8_t>(clamp_bar(pet.bars.hunger + kFeedHunger));
    return true;
  case CARE_PLAY:
    if (pet.asleep || pet.sick || pet.bars.energy < kPlayMinEnergy) {
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
  case CARE_ADOPT:
    break;
  }
  return false;
}

void care_advance(PetSnapshot& pet, uint32_t elapsed_ms) {
  if (pet.on_street) {
    return;
  }
  growth_advance(pet, elapsed_ms);
  advance_bars(pet, elapsed_ms);
  health_advance(pet, elapsed_ms);
}

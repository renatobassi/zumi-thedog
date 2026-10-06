#pragma once

#include <stdint.h>

// Contrato do Zumi entre regra, tela e gravação.
// O ciclo de cuidado mora em care.hpp. Fase e game over entram com o PRD de cada um.

enum Phase {
  PHASE_BLANKET = 0,
  PHASE_PUPPY = 1,
  PHASE_ADULT_SITTING = 2,
  PHASE_ADULT = 3
};

struct Bars {
  uint8_t hunger;
  uint8_t energy;
  uint8_t fun;
  uint8_t hygiene;
};

struct PetSnapshot {
  Phase phase;
  Bars bars;
  bool asleep;
  uint32_t last_tick_ms;
};

inline PetSnapshot pet_snapshot_newborn(uint32_t now_ms) {
  PetSnapshot snap;
  snap.phase = PHASE_BLANKET;
  snap.bars.hunger = 100;
  snap.bars.energy = 100;
  snap.bars.fun = 100;
  snap.bars.hygiene = 100;
  snap.asleep = false;
  snap.last_tick_ms = now_ms;
  return snap;
}

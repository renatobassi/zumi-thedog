#pragma once

#include <stdint.h>

// Contrato do Zumi entre regra, tela e gravação.
// Decaimento, fase e game over só entram com PRD aprovado.

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
  uint32_t last_tick_ms;
};

inline PetSnapshot pet_snapshot_newborn(uint32_t now_ms) {
  PetSnapshot snap;
  snap.phase = PHASE_BLANKET;
  snap.bars.hunger = 100;
  snap.bars.energy = 100;
  snap.bars.fun = 100;
  snap.bars.hygiene = 100;
  snap.last_tick_ms = now_ms;
  return snap;
}

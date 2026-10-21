#pragma once

#include <stdint.h>

// Contrato do Zumi entre regra, tela e gravação.
// Cuidado: care.hpp. Idade: growth.hpp. Doença e rua: health.hpp.

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

// Resto da taxa por hora (barra * ms). Sem isso, o tick de 1 ms da placa arredonda a zero.
struct BarCarry {
  int32_t hunger;
  int32_t energy;
  int32_t fun;
  int32_t hygiene;
};

struct PetSnapshot {
  Phase phase;
  Bars bars;
  bool asleep;
  uint32_t last_tick_ms;
  uint32_t age_ms;
  bool sick;
  bool on_street;
  uint32_t low_ms;
  uint32_t sick_ms;
  BarCarry bar_carry;
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
  snap.age_ms = 0;
  snap.sick = false;
  snap.on_street = false;
  snap.low_ms = 0;
  snap.sick_ms = 0;
  snap.bar_carry.hunger = 0;
  snap.bar_carry.energy = 0;
  snap.bar_carry.fun = 0;
  snap.bar_carry.hygiene = 0;
  return snap;
}

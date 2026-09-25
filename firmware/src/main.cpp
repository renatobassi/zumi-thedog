#include <Arduino.h>

#include "domain/pet_snapshot.hpp"

// Composição. Sem regra de jogo e sem desenho até o PRD correspondente.

static PetSnapshot g_pet;

void setup() {
  g_pet = pet_snapshot_newborn(millis());
}

void loop() {
  (void)g_pet;
}

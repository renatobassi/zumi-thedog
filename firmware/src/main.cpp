#include <Arduino.h>

#include "domain/pet_snapshot.hpp"
#include "hal/display.hpp"
#include "ui/hello.hpp"

// Composição. Sem regra de jogo até o PRD correspondente.

static PetSnapshot g_pet;

void setup() {
  g_pet = pet_snapshot_newborn(millis());

  const Display& display = cyd_display();
  display.begin();
  hello_show(display);
}

void loop() {
  (void)g_pet;
}

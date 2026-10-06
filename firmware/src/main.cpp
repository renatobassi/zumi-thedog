#include <Arduino.h>

#include "domain/pet_snapshot.hpp"
#include "hal/display.hpp"
#include "ui/hello.hpp"

// Composição. A tela ainda é o Hello. O ciclo de cuidado fica no domínio e no teste nativo.

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

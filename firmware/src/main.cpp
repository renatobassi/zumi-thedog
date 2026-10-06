#include <Arduino.h>

#include <stdio.h>
#include <string.h>

#include "domain/care.hpp"
#include "domain/pet_snapshot.hpp"
#include "hal/display.hpp"
#include "persistence/boot.hpp"
#include "persistence/nvs_store.hpp"
#include "ui/hello.hpp"

// A tela continua o Hello. O ciclo roda e fica na flash da placa.

static PetSnapshot g_pet;
static PetStore g_store;

static void log_pet() {
  Serial.printf("zumi fome=%u energia=%u diversao=%u higiene=%u %s\n", g_pet.bars.hunger, g_pet.bars.energy,
                g_pet.bars.fun, g_pet.bars.hygiene, g_pet.asleep ? "dormindo" : "acordado");
}

static bool same_care(const PetSnapshot& a, const PetSnapshot& b) {
  return a.phase == b.phase && a.asleep == b.asleep && a.bars.hunger == b.bars.hunger &&
         a.bars.energy == b.bars.energy && a.bars.fun == b.bars.fun && a.bars.hygiene == b.bars.hygiene;
}

static void apply_estado(const char* line) {
  int hunger = 0;
  int energy = 0;
  int fun = 0;
  int hygiene = 0;
  char sleep_word[16];
  if (sscanf(line, "estado %d %d %d %d %15s", &hunger, &energy, &fun, &hygiene, sleep_word) != 5) {
    Serial.println("uso: estado <fome> <energia> <diversao> <higiene> acordado|dormindo");
    return;
  }
  if (hunger < 0 || hunger > 100 || energy < 0 || energy > 100 || fun < 0 || fun > 100 || hygiene < 0 ||
      hygiene > 100) {
    Serial.println("barras de 0 a 100");
    return;
  }

  const bool asleep = strcmp(sleep_word, "dormindo") == 0;
  const bool awake = strcmp(sleep_word, "acordado") == 0;
  if (!asleep && !awake) {
    Serial.println("uso: estado <fome> <energia> <diversao> <higiene> acordado|dormindo");
    return;
  }

  g_pet.bars.hunger = static_cast<uint8_t>(hunger);
  g_pet.bars.energy = static_cast<uint8_t>(energy);
  g_pet.bars.fun = static_cast<uint8_t>(fun);
  g_pet.bars.hygiene = static_cast<uint8_t>(hygiene);
  g_pet.asleep = asleep;
  g_pet.last_tick_ms = millis();
  if (!pet_commit(g_store, g_pet)) {
    Serial.println("zumi gravacao falhou");
    return;
  }
  log_pet();
}

static void poll_serial() {
  static char line[80];
  static size_t used = 0;
  while (Serial.available() > 0) {
    const char c = static_cast<char>(Serial.read());
    if (c == '\n' || c == '\r') {
      if (used > 0) {
        line[used] = '\0';
        apply_estado(line);
        used = 0;
      }
      continue;
    }
    if (used + 1 < sizeof line) {
      line[used++] = c;
    }
  }
}

void setup() {
  Serial.begin(115200);
  g_store = nvs_pet_store();
  g_pet = pet_restore(g_store, millis());
  log_pet();

  const Display& display = cyd_display();
  display.begin();
  hello_show(display);
}

void loop() {
  poll_serial();

  const uint32_t now = millis();
  const uint32_t elapsed = now - g_pet.last_tick_ms;
  if (elapsed == 0) {
    return;
  }

  const PetSnapshot before = g_pet;
  care_advance(g_pet, elapsed);
  g_pet.last_tick_ms = now;
  if (!same_care(before, g_pet)) {
    if (!pet_commit(g_store, g_pet)) {
      Serial.println("zumi gravacao falhou");
    }
    log_pet();
  }
}

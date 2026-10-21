#include <Arduino.h>

#include <stdio.h>
#include <string.h>

#include "domain/care.hpp"
#include "domain/mood.hpp"
#include "domain/pet_snapshot.hpp"
#include "hal/display.hpp"
#include "hal/touch.hpp"
#include "persistence/boot.hpp"
#include "persistence/nvs_store.hpp"
#include "ui/frame.hpp"
#include "ui/screen.hpp"
#include "ui/zumi.hpp"

// A tela mostra a pose, as barras e os quatro cuidados. O toque pede a ação; o ciclo decide.

static PetSnapshot g_pet;
static PetStore g_store;
static TouchLatch g_latch = {false, 0};
static CareNotice g_notice = {0, 0};
static bool g_notice_drawn = false;
static CareAction g_action = CARE_FEED;
static uint32_t g_action_until_ms = 0;
static int g_last_mood_frame = -1;

static MoodView current_mood(uint32_t now) {
  MoodView mood;
  mood.action = g_action;
  mood.action_until_ms = g_action_until_ms;
  mood.now_ms = now;
  return mood;
}

static void show_pet() {
  const uint32_t now = millis();
  const char* notice = care_notice_text(g_notice, now);
  zumi_show(cyd_display(), g_pet, notice, current_mood(now));
  g_notice_drawn = notice != 0;
  g_last_mood_frame = mood_frame_index(mood_choose(g_pet, g_action, now < g_action_until_ms), now);
}

static void log_pet() {
  const char* mood = "acordado";
  if (g_pet.on_street) {
    mood = "rua";
  } else if (g_pet.sick) {
    mood = "doente";
  } else if (g_pet.asleep) {
    mood = "dormindo";
  }
  Serial.printf("zumi fome=%u energia=%u diversao=%u higiene=%u idade_h=%u fase=%u %s\n", g_pet.bars.hunger,
                g_pet.bars.energy, g_pet.bars.fun, g_pet.bars.hygiene, g_pet.age_ms / (60u * 60u * 1000u),
                static_cast<unsigned>(g_pet.phase), mood);
}

static bool same_care(const PetSnapshot& a, const PetSnapshot& b) {
  return a.phase == b.phase && a.age_ms == b.age_ms && a.asleep == b.asleep && a.sick == b.sick &&
         a.on_street == b.on_street && a.low_ms == b.low_ms && a.sick_ms == b.sick_ms &&
         a.bars.hunger == b.bars.hunger && a.bars.energy == b.bars.energy && a.bars.fun == b.bars.fun &&
         a.bars.hygiene == b.bars.hygiene;
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
  show_pet();
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

static void apply_touch(uint32_t now) {
  const TouchRead sample = cyd_touch().read();
  if (!touch_accept(g_latch, sample.pressed, now)) {
    return;
  }

  const TouchOutcome outcome = touch_at(g_pet, sample.x, sample.y);
  if (!outcome.attempted) {
    return;
  }

  care_notice_show(g_notice, outcome.notice, now);
  if (outcome.accepted) {
    if (outcome.notice != 0 && strcmp(outcome.notice, "Adotou") == 0) {
      g_pet.last_tick_ms = now;
      g_action_until_ms = 0;
    } else if (outcome.notice != 0 &&
               (strcmp(outcome.notice, "Comeu") == 0 || strcmp(outcome.notice, "Brincou") == 0 ||
                strcmp(outcome.notice, "Banhou") == 0)) {
      if (strcmp(outcome.notice, "Comeu") == 0) {
        g_action = CARE_FEED;
      } else if (strcmp(outcome.notice, "Brincou") == 0) {
        g_action = CARE_PLAY;
      } else {
        g_action = CARE_BATHE;
      }
      g_action_until_ms = now + kMoodActionMs;
    }
    if (!pet_commit(g_store, g_pet)) {
      Serial.println("zumi gravacao falhou");
    }
  }
  Serial.println(outcome.notice);
  log_pet();
  show_pet();
}

void setup() {
  Serial.begin(115200);
  g_store = nvs_pet_store();
  g_pet = pet_restore(g_store, millis());
  log_pet();

  const Display& display = cyd_display();
  display.begin();
  cyd_touch().begin();
  show_pet();
}

void loop() {
  poll_serial();

  const uint32_t now = millis();
  apply_touch(now);
  if (g_notice_drawn && care_notice_text(g_notice, now) == 0) {
    show_pet();
  }

  const MoodId mood = mood_choose(g_pet, g_action, now < g_action_until_ms);
  const int frame_i = mood_frame_index(mood, now);
  if (frame_i != g_last_mood_frame) {
    show_pet();
  }

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
    show_pet();
  }
}

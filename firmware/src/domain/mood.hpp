#pragma once

#include "care.hpp"
#include "pet_snapshot.hpp"

// Humor e poses do PRD 0006. Não desenha pixel.

enum MoodId {
  MOOD_STREET = 0,
  MOOD_ACTION_FEED = 1,
  MOOD_ACTION_PLAY = 2,
  MOOD_ACTION_BATH = 3,
  MOOD_SLEEP = 4,
  MOOD_SICK = 5,
  MOOD_HUNGRY = 6,
  MOOD_WAG = 7,
  MOOD_PHASE = 8
};

static const uint32_t kMoodActionMs = 2500;

// Ação recente só conta se action_live for true (janela de 2,5 s ainda aberta).
MoodId mood_choose(const PetSnapshot& pet, CareAction action, bool action_live);

// Período entre trocas de quadro, em ms.
uint32_t mood_frame_period_ms(MoodId mood);

// 0 ou 1 enquanto a pose animada durar.
int mood_frame_index(MoodId mood, uint32_t now_ms);

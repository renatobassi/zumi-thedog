#pragma once

#include <stdint.h>

#include "../domain/pet_snapshot.hpp"
#include "frame.hpp"

// Toque do PRD 0004. O retângulo escolhe a ação; o ciclo decide se ela vale.

struct TouchOutcome {
  bool attempted;
  bool accepted;
  const char* notice;
};

struct TouchLatch {
  bool held;
  uint32_t ready_at_ms;
};

struct CareNotice {
  const char* text;
  uint32_t hide_at_ms;
};

static const uint32_t kTouchGapMs = 300;
static const uint32_t kCareNoticeMs = 2000;

TouchOutcome touch_at(PetSnapshot& pet, int x, int y);

// true só na borda de aperto. Segurar não repete; outro toque depois da folga vale.
bool touch_accept(TouchLatch& latch, bool pressed, uint32_t now_ms);

void care_notice_show(CareNotice& notice, const char* text, uint32_t now_ms);
const char* care_notice_text(const CareNotice& notice, uint32_t now_ms);

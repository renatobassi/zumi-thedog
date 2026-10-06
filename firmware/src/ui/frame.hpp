#pragma once

#include <stdint.h>

#include "../domain/pet_snapshot.hpp"

// Mapa da tela do PRD 0003. Não desenha pixel e não altera o snapshot.

static const int kZumiScreenW = 320;
static const int kZumiScreenH = 240;
static const int kZumiSpriteScale = 4;
static const int kZumiBarTrackPx = 160;
static const uint16_t kSpriteKey = 0xF81F;

enum PoseId { POSE_NONE = 0, POSE_MANTA = 1, POSE_SLEEP = 2 };

struct SpriteView {
  const uint16_t* pixels;
  int width;
  int height;
};

struct BarView {
  const char* name;
  uint8_t value;
  int fill_px;
};

struct ZumiFrame {
  PoseId pose;
  int dog_x;
  int dog_y;
  int dog_w;
  int dog_h;
  int track_x;
  int track_y;
  int track_w;
  int track_h;
  int track_pitch;
  BarView bars[4];
};

bool pose_versioned(PoseId pose);
PoseId zumi_pose(Phase phase, bool asleep);
int bar_fill_px(uint8_t value);
ZumiFrame zumi_frame(const PetSnapshot& pet);
SpriteView sprite_view(PoseId pose);

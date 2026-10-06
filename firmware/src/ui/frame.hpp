#pragma once

#include <stdint.h>

#include "../domain/pet_snapshot.hpp"

// Mapa da tela do PRD 0003. Não desenha pixel e não altera o snapshot.

static const int kZumiScreenW = 320;
static const int kZumiScreenH = 240;
static const int kZumiSpriteScale = 3;
static const int kZumiBarTrackPx = 59;
static const int kZumiDockX = 4;
static const int kZumiDockY = 188;
static const int kZumiDockW = 75;
static const int kZumiDockH = 48;
static const int kZumiDockGap = 4;
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
  int x;
  int y;
};

enum TouchAction {
  TOUCH_NONE = 0,
  TOUCH_FEED = 1,
  TOUCH_PLAY = 2,
  TOUCH_SLEEP = 3,
  TOUCH_BATH = 4
};

struct CareTarget {
  TouchAction action;
  const char* label;
  int x;
  int y;
  int w;
  int h;
};

struct ZumiFrame {
  PoseId pose;
  int dog_x;
  int dog_y;
  int dog_w;
  int dog_h;
  int track_w;
  int track_h;
  BarView bars[4];
  int notice_x;
  int notice_y;
  CareTarget targets[4];
};

bool pose_versioned(PoseId pose);
PoseId zumi_pose(Phase phase, bool asleep);
int bar_fill_px(uint8_t value);
ZumiFrame zumi_frame(const PetSnapshot& pet);
SpriteView sprite_view(PoseId pose);

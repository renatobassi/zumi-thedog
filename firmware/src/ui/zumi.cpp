#include "zumi.hpp"

#include <string.h>

#include "frame.hpp"

namespace {

int isqrt(int value) {
  int root = 0;
  while ((root + 1) * (root + 1) <= value) {
    ++root;
  }
  return root;
}

void paint_rug(const Display& display) {
  const int cx = 160;
  const int cy = 174;
  const int rx = 84;
  const int ry = 16;
  for (int y = cy - ry; y <= cy + ry && y < kZumiDockY; ++y) {
    const int dy = y - cy;
    const int inside = ry * ry - dy * dy;
    if (inside <= 0) {
      continue;
    }
    const int dx = rx * isqrt(inside) / ry;
    const uint16_t color = (dy * dy * 3 > ry * ry) ? COLOR_RUG_EDGE : COLOR_RUG;
    display.fill_rect(cx - dx, y, dx * 2, 1, color);
  }
}

void paint_window(const Display& display) {
  const int x = 8;
  const int y = 20;
  const int w = 44;
  const int h = 34;
  display.fill_rect(x, y, w, h, COLOR_INK);
  display.fill_rect(x + 3, y + 3, w - 6, h - 6, COLOR_SKY);
  display.fill_rect(x + w / 2 - 1, y + 3, 2, h - 6, COLOR_INK);
  display.fill_rect(x + 3, y + h / 2 - 1, w - 6, 2, COLOR_INK);
  display.fill_rect(x + 6, y + 6, 6, 6, COLOR_GOLD);
  display.fill_rect(x + 8, y + h - 9, 10, 2, COLOR_CREAM);
}

void paint_room(const Display& display) {
  for (int y = 0; y < kZumiScreenH; ++y) {
    uint16_t color = COLOR_WALL;
    if (y >= 156) {
      color = ((y - 156) % 6 < 3) ? COLOR_WOOD : COLOR_WOOD_LINE;
    } else if (y % 4 == 0) {
      color = COLOR_WALL_LINE;
    }
    display.fill_rect(0, y, kZumiScreenW, 1, color);
  }
  paint_rug(display);
  paint_window(display);
  display.text("ZUMI", 8, 2, 2, COLOR_GOLD);
}

void paint_icon(const Display& display, TouchAction action, int x, int y) {
  if (action == TOUCH_FEED) {
    display.fill_rect(x + 3, y, 6, 2, COLOR_GOLD);
    display.fill_rect(x, y + 3, 12, 2, COLOR_CREAM);
    display.fill_rect(x, y + 5, 2, 3, COLOR_CREAM);
    display.fill_rect(x + 10, y + 5, 2, 3, COLOR_CREAM);
    display.fill_rect(x, y + 8, 12, 2, COLOR_CREAM);
    display.fill_rect(x + 2, y + 5, 8, 3, COLOR_WHITE);
    return;
  }
  if (action == TOUCH_PLAY) {
    display.fill_rect(x + 3, y, 6, 2, COLOR_TOY);
    display.fill_rect(x + 1, y + 2, 10, 6, COLOR_TOY);
    display.fill_rect(x + 3, y + 8, 6, 2, COLOR_TOY);
    display.fill_rect(x + 3, y + 3, 2, 2, COLOR_WHITE);
    return;
  }
  if (action == TOUCH_SLEEP) {
    display.fill_rect(x + 1, y + 1, 8, 2, COLOR_GOLD);
    display.fill_rect(x, y + 3, 6, 4, COLOR_GOLD);
    display.fill_rect(x + 1, y + 7, 8, 2, COLOR_GOLD);
    return;
  }
  display.fill_rect(x, y + 3, 12, 2, COLOR_WHITE);
  display.fill_rect(x, y + 5, 2, 3, COLOR_WHITE);
  display.fill_rect(x + 10, y + 5, 2, 3, COLOR_WHITE);
  display.fill_rect(x, y + 8, 12, 2, COLOR_WHITE);
  display.fill_rect(x + 2, y + 5, 8, 3, COLOR_SKY);
}

int label_width(const char* label) {
  if (strcmp(label, "Brincar") == 0) {
    return 45;
  }
  if (strcmp(label, "Dormir") == 0) {
    return 39;
  }
  if (strcmp(label, "Acordar") == 0) {
    return 48;
  }
  return 36;
}

void paint_target(const Display& display, const CareTarget& target, const BarView& bar, int track_h) {
  display.fill_rect(target.x, target.y, target.w, target.h, COLOR_GOLD);
  display.fill_rect(target.x + 2, target.y + 2, target.w - 4, target.h - 4, COLOR_INK);
  paint_icon(display, target.action, target.x + (target.w - 12) / 2, target.y + 4);
  display.text(target.label, target.x + (target.w - label_width(target.label)) / 2, target.y + 16, 2, COLOR_CREAM);
  display.fill_rect(bar.x, bar.y, kZumiBarTrackPx, track_h, COLOR_BLACK);
  if (bar.fill_px > 0) {
    display.fill_rect(bar.x, bar.y, bar.fill_px, track_h, COLOR_CARAMEL);
  }
}

}  // namespace

void zumi_show(const Display& display, const PetSnapshot& pet, const char* notice) {
  const ZumiFrame frame = zumi_frame(pet);
  paint_room(display);

  const SpriteView sprite = sprite_view(frame.pose);
  if (sprite.pixels != 0 && frame.dog_w > 0 && frame.dog_h > 0) {
    display.sprite(frame.dog_x, frame.dog_y, sprite.width, sprite.height, sprite.pixels, kZumiSpriteScale, kSpriteKey);
  }

  if (notice != 0 && notice[0] != '\0') {
    display.text(notice, frame.notice_x, frame.notice_y, 2, COLOR_GOLD);
  }

  for (int i = 0; i < 4; ++i) {
    paint_target(display, frame.targets[i], frame.bars[i], frame.track_h);
  }
}

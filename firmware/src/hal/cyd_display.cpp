#include <Arduino.h>
#include <TFT_eSPI.h>

#include "cyd_pins.hpp"
#include "display.hpp"

static_assert(TFT_MOSI == CYD_TFT_MOSI, "platformio.ini e cyd_pins.hpp divergem");
static_assert(TFT_MISO == CYD_TFT_MISO, "platformio.ini e cyd_pins.hpp divergem");
static_assert(TFT_SCLK == CYD_TFT_SCLK, "platformio.ini e cyd_pins.hpp divergem");
static_assert(TFT_CS == CYD_TFT_CS, "platformio.ini e cyd_pins.hpp divergem");
static_assert(TFT_DC == CYD_TFT_DC, "platformio.ini e cyd_pins.hpp divergem");
static_assert(TFT_RST == CYD_TFT_RST, "platformio.ini e cyd_pins.hpp divergem");

static TFT_eSPI g_tft;

static void cyd_begin(void) {
  pinMode(CYD_TFT_BL, OUTPUT);
  digitalWrite(CYD_TFT_BL, HIGH);
  g_tft.init();
  g_tft.setRotation(1);
}

static void cyd_clear(uint16_t color) {
  g_tft.fillScreen(color);
}

static void cyd_text(const char* text, int x, int y, uint8_t font, uint16_t color) {
  g_tft.setTextColor(color);
  g_tft.setTextDatum(TL_DATUM);
  g_tft.drawString(text, x, y, font);
}

static void cyd_text_centered(const char* text, int y, uint8_t font, uint16_t color) {
  g_tft.setTextColor(color);
  g_tft.setTextDatum(TC_DATUM);
  g_tft.drawString(text, g_tft.width() / 2, y, font);
}

static void cyd_fill_rect(int x, int y, int w, int h, uint16_t color) {
  if (w <= 0 || h <= 0) {
    return;
  }
  g_tft.fillRect(x, y, w, h, color);
}

static void cyd_sprite(int x, int y, int w, int h, const uint16_t* pixels, int scale, uint16_t key) {
  if (pixels == 0 || w <= 0 || h <= 0 || scale <= 0) {
    return;
  }
  for (int sy = 0; sy < h; ++sy) {
    for (int sx = 0; sx < w; ++sx) {
      const uint16_t color = pixels[sy * w + sx];
      if (color == key) {
        continue;
      }
      g_tft.fillRect(x + sx * scale, y + sy * scale, scale, scale, color);
    }
  }
}

const Display& cyd_display() {
  static const Display display = {cyd_begin, cyd_clear, cyd_text, cyd_text_centered, cyd_fill_rect, cyd_sprite};
  return display;
}

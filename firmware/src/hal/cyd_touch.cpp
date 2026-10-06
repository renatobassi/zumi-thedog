#include <Arduino.h>
#include <SPI.h>

#include "cyd_pins.hpp"
#include "touch.hpp"

// XPT2046 do CYD clássico, SPI próprio (não o da tela). Rotação 1, paisagem.
// Faixa crua usual desta placa; o passo na mesa confirma os quatro cantos.

static const int kZThreshold = 300;
static const int kRawXMin = 200;
static const int kRawXMax = 3700;
static const int kRawYMin = 240;
static const int kRawYMax = 3800;
static const int kScreenW = 320;
static const int kScreenH = 240;

static SPIClass g_touch_spi(VSPI);

static int16_t best_two_avg(int16_t x, int16_t y, int16_t z) {
  const int16_t da = x > y ? x - y : y - x;
  const int16_t db = x > z ? x - z : z - x;
  const int16_t dc = z > y ? z - y : y - z;
  if (da <= db && da <= dc) {
    return static_cast<int16_t>((x + y) >> 1);
  }
  if (db <= da && db <= dc) {
    return static_cast<int16_t>((x + z) >> 1);
  }
  return static_cast<int16_t>((y + z) >> 1);
}

static int map_raw(int raw, int raw_min, int raw_max, int out_max) {
  if (raw < raw_min) {
    raw = raw_min;
  }
  if (raw > raw_max) {
    raw = raw_max;
  }
  return (raw - raw_min) * out_max / (raw_max - raw_min);
}

static void touch_begin(void) {
  pinMode(CYD_TOUCH_CS, OUTPUT);
  digitalWrite(CYD_TOUCH_CS, HIGH);
  pinMode(CYD_TOUCH_IRQ, INPUT);
  g_touch_spi.begin(CYD_TOUCH_CLK, CYD_TOUCH_MISO, CYD_TOUCH_MOSI, CYD_TOUCH_CS);
}

static TouchRead touch_read(void) {
  TouchRead sample;
  sample.pressed = false;
  sample.x = 0;
  sample.y = 0;

  g_touch_spi.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CYD_TOUCH_CS, LOW);
  g_touch_spi.transfer(0xB1);
  const int16_t z1 = g_touch_spi.transfer16(0xC1) >> 3;
  int z = z1 + 4095;
  const int16_t z2 = g_touch_spi.transfer16(0x91) >> 3;
  z -= z2;

  int16_t data[6];
  if (z >= kZThreshold) {
    g_touch_spi.transfer16(0x91);
    data[0] = g_touch_spi.transfer16(0xD1) >> 3;
    data[1] = g_touch_spi.transfer16(0x91) >> 3;
    data[2] = g_touch_spi.transfer16(0xD1) >> 3;
    data[3] = g_touch_spi.transfer16(0x91) >> 3;
  } else {
    data[0] = data[1] = data[2] = data[3] = 0;
  }
  data[4] = g_touch_spi.transfer16(0xD0) >> 3;
  data[5] = g_touch_spi.transfer16(0) >> 3;
  digitalWrite(CYD_TOUCH_CS, HIGH);
  g_touch_spi.endTransaction();

  if (z < kZThreshold) {
    return sample;
  }

  const int raw_x = best_two_avg(data[0], data[2], data[4]);
  const int raw_y = best_two_avg(data[1], data[3], data[5]);
  sample.pressed = true;
  sample.x = map_raw(raw_x, kRawXMin, kRawXMax, kScreenW - 1);
  sample.y = map_raw(raw_y, kRawYMin, kRawYMax, kScreenH - 1);
  return sample;
}

const Touch& cyd_touch() {
  static const Touch touch = {touch_begin, touch_read};
  return touch;
}

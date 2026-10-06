#pragma once

#include <stdint.h>

// Contrato de desenho. Cores em RGB565; a tela é 320×240 em paisagem.

static const uint16_t COLOR_BLACK = 0x0000;
static const uint16_t COLOR_WHITE = 0xFFFF;
static const uint16_t COLOR_CARAMEL = 0xD3A6;

struct Display {
  void (*begin)(void);
  void (*clear)(uint16_t color);
  void (*text)(const char* text, int x, int y, uint8_t font, uint16_t color);
  void (*text_centered)(const char* text, int y, uint8_t font, uint16_t color);
  void (*fill_rect)(int x, int y, int w, int h, uint16_t color);
  void (*sprite)(int x, int y, int w, int h, const uint16_t* pixels, int scale, uint16_t key);
};

const Display& cyd_display();

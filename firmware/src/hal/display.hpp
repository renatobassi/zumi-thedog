#pragma once

#include <stdint.h>

// Contrato de desenho. Cores em RGB565; a tela é 320×240 em paisagem.
// Paleta: docs/product/identidade-visual.md

static const uint16_t COLOR_BLACK = 0x0000;
static const uint16_t COLOR_WHITE = 0xFFFF;
static const uint16_t COLOR_CARAMEL = 0xC449;  // #c68a4b
static const uint16_t COLOR_CREAM = 0xF739;    // #f5e6c8
static const uint16_t COLOR_EAR = 0x59C3;      // #5a3a1a
static const uint16_t COLOR_INK = 0x3901;      // #3b220c
static const uint16_t COLOR_GOLD = 0xE404;     // #e08020
static const uint16_t COLOR_WALL = 0x21AA;     // #243452
static const uint16_t COLOR_WALL_LINE = 0x1968; // #1e2c46
static const uint16_t COLOR_WOOD = 0x3922;     // #3e2614
static const uint16_t COLOR_WOOD_LINE = 0x59C4; // #5c3a20
static const uint16_t COLOR_RUG = 0x23CE;      // #207a70
static const uint16_t COLOR_RUG_EDGE = 0x12CA; // #165a52
static const uint16_t COLOR_SKY = 0x7DDB;      // #78badc
static const uint16_t COLOR_TOY = 0xF800;      // bola de brincar

struct Display {
  void (*begin)(void);
  void (*clear)(uint16_t color);
  void (*text)(const char* text, int x, int y, uint8_t font, uint16_t color);
  void (*text_centered)(const char* text, int y, uint8_t font, uint16_t color);
  void (*fill_rect)(int x, int y, int w, int h, uint16_t color);
  void (*sprite)(int x, int y, int w, int h, const uint16_t* pixels, int scale, uint16_t key);
};

const Display& cyd_display();

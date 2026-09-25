#pragma once

#include <stdint.h>

// Contrato de desenho. O driver (TFT_eSPI) entra com o PRD do primeiro pixel.

struct Display {
  void (*begin)(void);
  void (*clear)(uint16_t color);
};

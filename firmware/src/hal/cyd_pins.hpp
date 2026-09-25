#pragma once

// ESP32-2432S028R (CYD 2.8" resistivo, ILI9341).
// Único lugar com número de GPIO. Não incluir este header no domínio.

static const int CYD_TFT_MOSI = 13;
static const int CYD_TFT_MISO = 12;
static const int CYD_TFT_SCLK = 14;
static const int CYD_TFT_CS = 15;
static const int CYD_TFT_DC = 2;
static const int CYD_TFT_RST = -1;
static const int CYD_TFT_BL = 21;
static const int CYD_TOUCH_CS = 33;
static const int CYD_TOUCH_IRQ = 36;

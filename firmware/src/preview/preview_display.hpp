#pragma once

#include "../hal/display.hpp"

// Framebuffer 320×240. O mesmo contrato que o CYD usa para desenhar.

static const int kPreviewW = 320;
static const int kPreviewH = 240;

const Display& preview_display();
const uint16_t* preview_framebuffer();
bool preview_write_bmp(const char* path);

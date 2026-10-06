#include "preview_display.hpp"

#include "font2_data.hpp"

#include <stdio.h>

namespace {

uint16_t g_pixels[kPreviewW * kPreviewH];

void plot(int x, int y, uint16_t color) {
  if (x < 0 || y < 0 || x >= kPreviewW || y >= kPreviewH) {
    return;
  }
  g_pixels[y * kPreviewW + x] = color;
}

void preview_begin(void) {}

void preview_clear(uint16_t color) {
  for (int i = 0; i < kPreviewW * kPreviewH; ++i) {
    g_pixels[i] = color;
  }
}

int glyph_index(unsigned char c) {
  if (c < 32 || c > 127) {
    c = '?';
  }
  return c - 32;
}

void draw_glyph(int x, int y, int index, uint16_t color) {
  const int width = kFont2Width[index];
  const int bytes = (width + 6) / 8;
  const uint8_t* glyph = kFont2Bits + kFont2Offset[index];
  for (int row = 0; row < 16; ++row) {
    for (int k = 0; k < bytes; ++k) {
      const uint8_t line = glyph[row * bytes + k];
      for (int bit = 0; bit < 8; ++bit) {
        if (line & (0x80 >> bit)) {
          plot(x + k * 8 + bit, y + row, color);
        }
      }
    }
  }
}

int text_width(const char* text) {
  int width = 0;
  if (text == 0) {
    return 0;
  }
  for (const char* p = text; *p != '\0'; ++p) {
    width += kFont2Width[glyph_index(static_cast<unsigned char>(*p))];
  }
  return width;
}

void preview_text(const char* text, int x, int y, uint8_t font, uint16_t color) {
  (void)font;
  if (text == 0) {
    return;
  }
  for (const char* p = text; *p != '\0'; ++p) {
    const int index = glyph_index(static_cast<unsigned char>(*p));
    draw_glyph(x, y, index, color);
    x += kFont2Width[index];
  }
}

void preview_text_centered(const char* text, int y, uint8_t font, uint16_t color) {
  const int width = text_width(text);
  preview_text(text, (kPreviewW - width) / 2, y, font, color);
}

void preview_fill_rect(int x, int y, int w, int h, uint16_t color) {
  if (w <= 0 || h <= 0) {
    return;
  }
  for (int row = y; row < y + h; ++row) {
    for (int col = x; col < x + w; ++col) {
      plot(col, row, color);
    }
  }
}

void preview_sprite(int x, int y, int w, int h, const uint16_t* pixels, int scale, uint16_t key) {
  if (pixels == 0 || w <= 0 || h <= 0 || scale <= 0) {
    return;
  }
  for (int sy = 0; sy < h; ++sy) {
    for (int sx = 0; sx < w; ++sx) {
      const uint16_t color = pixels[sy * w + sx];
      if (color == key) {
        continue;
      }
      preview_fill_rect(x + sx * scale, y + sy * scale, scale, scale, color);
    }
  }
}

uint8_t expand5(int value) {
  return static_cast<uint8_t>((value * 255) / 31);
}

uint8_t expand6(int value) {
  return static_cast<uint8_t>((value * 255) / 63);
}

}  // namespace

const Display& preview_display() {
  static const Display display = {preview_begin, preview_clear, preview_text, preview_text_centered,
                                  preview_fill_rect, preview_sprite};
  return display;
}

const uint16_t* preview_framebuffer() {
  return g_pixels;
}

bool preview_write_bmp(const char* path) {
  FILE* file = fopen(path, "wb");
  if (file == 0) {
    return false;
  }

  const int row_bytes = (kPreviewW * 3 + 3) & ~3;
  const int pixel_bytes = row_bytes * kPreviewH;
  const int file_bytes = 54 + pixel_bytes;
  unsigned char header[54] = {};
  header[0] = 'B';
  header[1] = 'M';
  header[2] = static_cast<unsigned char>(file_bytes);
  header[3] = static_cast<unsigned char>(file_bytes >> 8);
  header[4] = static_cast<unsigned char>(file_bytes >> 16);
  header[5] = static_cast<unsigned char>(file_bytes >> 24);
  header[10] = 54;
  header[14] = 40;
  header[18] = static_cast<unsigned char>(kPreviewW);
  header[19] = static_cast<unsigned char>(kPreviewW >> 8);
  header[22] = static_cast<unsigned char>(kPreviewH);
  header[23] = static_cast<unsigned char>(kPreviewH >> 8);
  header[26] = 1;
  header[28] = 24;
  if (fwrite(header, 1, 54, file) != 54) {
    fclose(file);
    return false;
  }

  unsigned char row[960];
  for (int y = kPreviewH - 1; y >= 0; --y) {
    int used = 0;
    for (int x = 0; x < kPreviewW; ++x) {
      const uint16_t color = g_pixels[y * kPreviewW + x];
      row[used++] = expand5(color & 0x1F);
      row[used++] = expand6((color >> 5) & 0x3F);
      row[used++] = expand5((color >> 11) & 0x1F);
    }
    while (used < row_bytes) {
      row[used++] = 0;
    }
    if (fwrite(row, 1, static_cast<size_t>(row_bytes), file) != static_cast<size_t>(row_bytes)) {
      fclose(file);
      return false;
    }
  }

  fclose(file);
  return true;
}

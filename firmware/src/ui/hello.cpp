#include "hello.hpp"

// As fontes embutidas do TFT_eSPI não têm acento.
void hello_show(const Display& display) {
  display.clear(COLOR_BLACK);
  display.text_centered("Ola!", 70, 4, COLOR_CARAMEL);
  display.text_centered("A placa esta pronta.", 120, 4, COLOR_WHITE);
  display.text_centered("ESP32-2432S028R - 320x240", 200, 2, COLOR_WHITE);
}

#pragma once

// Leitura já em pixel da tela. O número de pino fica no driver.

struct TouchRead {
  bool pressed;
  int x;
  int y;
};

struct Touch {
  void (*begin)(void);
  TouchRead (*read)(void);
};

const Touch& cyd_touch();

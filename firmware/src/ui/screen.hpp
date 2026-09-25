#pragma once

#include "../domain/pet_snapshot.hpp"

enum TouchAction {
  TOUCH_NONE = 0,
  TOUCH_FEED = 1,
  TOUCH_PLAY = 2,
  TOUCH_SLEEP = 3,
  TOUCH_BATH = 4
};

// A tela observa o snapshot e devolve a ação. Não altera barras.
TouchAction screen_action_at(int x, int y);

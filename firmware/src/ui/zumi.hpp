#pragma once

#include "../domain/pet_snapshot.hpp"
#include "../hal/display.hpp"

// Desenha a pose, as barras, os quatro alvos e um aviso que some. Não altera o snapshot.
void zumi_show(const Display& display, const PetSnapshot& pet, const char* notice);

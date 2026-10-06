#pragma once

#include "../domain/pet_snapshot.hpp"
#include "../hal/display.hpp"

// Desenha a pose versionada e as quatro barras. Não altera o snapshot.
void zumi_show(const Display& display, const PetSnapshot& pet);

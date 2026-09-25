#pragma once

#include "../domain/pet_snapshot.hpp"

// Grava o snapshot. Não aplica regra de jogo.

struct PetStore {
  bool (*load)(PetSnapshot *out);
  bool (*save)(const PetSnapshot *snap);
};

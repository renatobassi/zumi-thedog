#pragma once

#include "../domain/pet_snapshot.hpp"

// Grava o snapshot. Não aplica regra de jogo.
// ctx é o armazenamento (memória falsa no teste, flash na placa).

struct PetStore {
  void* ctx;
  bool (*load)(void* ctx, PetSnapshot* out);
  bool (*save)(void* ctx, const PetSnapshot* snap);
};

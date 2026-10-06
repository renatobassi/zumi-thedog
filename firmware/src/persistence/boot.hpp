#pragma once

#include <stdint.h>

#include "store.hpp"

// Devolve o ciclo gravado com o relógio desta ligada.
// O tempo entre o corte e esta chamada não entra nas barras.
// Sem gravação, ou com gravação inválida, nasce acordado com as barras em 100.

PetSnapshot pet_restore(const PetStore& store, uint32_t now_ms);

bool pet_commit(const PetStore& store, const PetSnapshot& snap);

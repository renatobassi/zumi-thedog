#pragma once

#include <stddef.h>
#include <stdint.h>

#include "../domain/pet_snapshot.hpp"

// Registro versão 1, pouco endian, sem relógio de parede:
//   Z U M I | versão | tamanho | fase, 4 barras, sono, last_tick_ms | crc16
// A leitura começa no recém-nascido e só cobre os campos que a versão traz.
// Campo que uma gravação antiga não tem fica no valor inicial. Registro curto,
// crc errado ou versão desconhecida não vira estado pela metade.

constexpr size_t kPetRecordV1Size = 18;

bool pet_snapshot_can_persist(const PetSnapshot& snap);

bool pet_record_encode(const PetSnapshot& snap, uint8_t* dest, size_t cap, size_t* written);

bool pet_record_decode(const uint8_t* bytes, size_t len, PetSnapshot* out);

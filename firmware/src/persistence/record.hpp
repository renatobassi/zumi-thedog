#pragma once

#include <stddef.h>
#include <stdint.h>

#include "../domain/pet_snapshot.hpp"

// Registro pouco endian, sem relógio de parede:
//   Z U M I | versão | tamanho | payload | crc16
// v1: fase, 4 barras, sono, last_tick_ms
// v2: v1 + age_ms
// A leitura começa no recém-nascido e só cobre os campos que a versão traz.

constexpr size_t kPetRecordV1Size = 18;
constexpr size_t kPetRecordV2Size = 22;

bool pet_snapshot_can_persist(const PetSnapshot& snap);

bool pet_record_encode(const PetSnapshot& snap, uint8_t* dest, size_t cap, size_t* written);

bool pet_record_decode(const uint8_t* bytes, size_t len, PetSnapshot* out);

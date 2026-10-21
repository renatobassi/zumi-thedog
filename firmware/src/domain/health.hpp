#pragma once

#include "pet_snapshot.hpp"

// Doença e rua do PRD 0007.

constexpr uint32_t kSickAfterMs = 60u * 60u * 1000u;
constexpr uint32_t kStreetAfterMs = 24u * 60u * 60u * 1000u;
constexpr uint8_t kCriticalBar = 10;
constexpr uint8_t kRecoverBar = 25;

// Atualiza doente e rua a partir das barras atuais e do tempo ligado.
void health_advance(PetSnapshot& pet, uint32_t elapsed_ms);

// Recomeça o ciclo. Só vale na rua.
bool health_adopt(PetSnapshot& pet, uint32_t now_ms);

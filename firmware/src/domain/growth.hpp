#pragma once

#include "pet_snapshot.hpp"

// Crescimento do PRD 0005. Idade é tempo de placa ligada desde a adoção.

constexpr uint32_t kGrowthPuppyMs = 24u * 60u * 60u * 1000u;
constexpr uint32_t kGrowthAdultSittingMs = 72u * 60u * 60u * 1000u;
constexpr uint32_t kGrowthAdultMs = 168u * 60u * 60u * 1000u;

Phase phase_for_age(uint32_t age_ms);

// Soma idade ligada e atualiza a fase. Não mexe nas barras.
void growth_advance(PetSnapshot& pet, uint32_t elapsed_ms);

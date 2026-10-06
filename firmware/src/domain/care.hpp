#pragma once

#include "pet_snapshot.hpp"

// Ciclo de cuidado do PRD 0001. O tempo entra em milissegundos; este módulo não lê o relógio.

enum CareAction {
  CARE_FEED = 0,
  CARE_PLAY = 1,
  CARE_BATHE = 2,
  CARE_SLEEP = 3,
  CARE_WAKE = 4
};

// true quando a ação altera o estado. Recusa deixa barras e sono como estavam.
bool care_apply(PetSnapshot& pet, CareAction action);

// Aplica a taxa do perfil atual. Dormindo, ao chegar a 100 de energia acorda naquele instante
// e o restante do intervalo usa a taxa de acordado.
void care_advance(PetSnapshot& pet, uint32_t elapsed_ms);

# Arquitetura

O PRD descreve o comportamento. Este documento descreve onde esse comportamento mora no código, para o case continuar legível quando houver mais de uma feature.

## Contexto

O Zumi da V0 roda offline num ESP32-2432S028R. A tela e o touch já ocupam quase todos os pinos. A regra do bichinho (barras, fase, abandono) não depende do desenho do pixel. Quem lê o case precisa achar a regra sem abrir o driver da tela.

## Decisão

Firmware em C++ com PlatformIO, no diretório `firmware/`.

PlatformIO porque a placa, as flags e as dependências ficam no repositório. O setup de pinos do CYD não mora num `User_Setup.h` da máquina de quem compila.

Quatro módulos, uma direção de dependência:

```text
main.cpp
  → ui        traduz toque em comando e estado em tela
  → domain    barras, fase, doença, game over
  → persistence   grava e lê um snapshot do domínio
  → hal       pino, display, touch, flash
```

- `domain` não inclui display, GPIO, Wi-Fi nem driver.
- `ui` não decide se o Zumi adoece.
- `persistence` não aplica regra de jogo.
- `hal` é o único lugar com número de pino e, no futuro, com TFT_eSPI.
- `main.cpp` só liga os módulos.

Regra de jogo entra no `domain` com PRD aprovado e teste que roda no computador, sem gravar a placa. O alvo `native` do PlatformIO existe para isso. O alvo `cyd` existe para o firmware da placa e ainda não desenha o pet.

## Mapa

```text
firmware/
  platformio.ini
  src/main.cpp
  src/domain/      contrato do estado (PetSnapshot)
  src/ui/          interface da tela, sem regra
  src/hal/         pinos do CYD e contrato de display/touch
  src/persistence/ contrato de gravar o snapshot
  test/            testes do domínio no ambiente nativo
```

O snapshot em `domain/pet_snapshot.hpp` é o contrato entre regra, tela e gravação. Ainda não há decaimento, sprite nem toque implementados: isso seria feature sem PRD.

## Fora até um PRD dizer o contrário

- HTTP, chave de API, reconhecimento de fala.
- Microfone e alto-falante. No CYD clássico isso disputa pino com a tela e o cartão.
- Biblioteca de display puxada “por precaução”. Ela entra no PRD que for desenhar o primeiro pixel.

## Leitura de suporte

- Decisão registrada: [adr/0001-camadas-e-platformio.md](adr/0001-camadas-e-platformio.md)
- Barra de merge: [definition-of-done.md](definition-of-done.md)

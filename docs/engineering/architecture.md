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
- `hal` é o único lugar com número de pino e com TFT_eSPI. A configuração da tela que o TFT_eSPI lê fica nos `build_flags` do `platformio.ini` e é conferida contra `hal/cyd_pins.hpp` na compilação.
- `main.cpp` só liga os módulos.

Regra de jogo entra no `domain` com PRD aprovado e teste que roda no computador, sem gravar a placa. O alvo `native` do PlatformIO existe para isso. O alvo `cyd` grava o firmware da placa. A tela desenha o pet a partir do snapshot; o que cabe na tela é testado no `native`, sem o driver.

## Mapa

```text
firmware/
  platformio.ini
  src/main.cpp
  src/domain/      contrato do estado (PetSnapshot)
  src/ui/          tela sem regra (frame.cpp: pose, barras e alvos; screen.cpp: toque do PRD 0004; hello.cpp: tela do PRD 0000)
  src/hal/         pinos do CYD, contrato de display/touch, driver TFT_eSPI e SPI do XPT2046
  src/persistence/ registro do snapshot, leitura ao ligar e flash NVS no alvo cyd
  test/            testes do domínio no ambiente nativo
```

O snapshot em `domain/pet_snapshot.hpp` é o contrato entre regra, tela e gravação. O ciclo de cuidado do PRD 0001 mora em `domain/care` e roda no teste nativo. A gravação do PRD 0002 mora em `persistence`: o registro e a leitura no teste nativo, a flash NVS só no alvo `cyd`. Ao ligar, o relógio da sessão recomeça; o intervalo desligado não entra nas barras. A tela do PRD 0003 mora em `ui/frame`: escolhe a pose versionada, o comprimento das barras e os quatro alvos, e o teste nativo confere o encaixe em 320×240. O desenho no TFT fica em `ui/zumi` e no `hal`. O toque do PRD 0004 mora em `ui/screen`: o retângulo vira uma ação do ciclo, e o ciclo continua dono do número. Segurar o dedo não repete. O aviso some sozinho. O SPI do XPT2046 fica no `hal`, separado do SPI da tela. A pose versionada é o adulto sentado; fase sem sprite próprio volta para a pose anterior. A paleta dessa pose e da tela está em [identidade visual](../product/identidade-visual.md). O alvo `preview` desenha essa mesma tela numa janela do computador.

## Fora até um PRD dizer o contrário

- HTTP, chave de API, reconhecimento de fala.
- Microfone e alto-falante. No CYD clássico isso disputa pino com a tela e o cartão.
- Biblioteca de display puxada “por precaução”. Ela entra no PRD que for desenhar o primeiro pixel.

## Leitura de suporte

- Decisão registrada: [adr/0001-camadas-e-platformio.md](adr/0001-camadas-e-platformio.md)
- Barra de merge: [definition-of-done.md](definition-of-done.md)

# Firmware

Alvo `cyd`: ESP32-2432S028R (CYD clássico). Alvo `native`: testes do domínio no computador.

Hoje o `cyd` grava o Hello do [PRD 0000](../docs/product/prds/0000-hello-na-placa.md): um cumprimento fixo na tela, sem Zumi. O ciclo do [PRD 0001](../docs/product/prds/0001-ciclo-de-cuidado.md) mora no domínio e só roda no teste nativo.

- `src/domain` — contrato do estado e o ciclo de cuidado. Testável sem a placa.
- `src/ui` — toque entra, ação sai. Não mexe em barra. `hello.cpp` é a tela do PRD 0000.
- `src/hal` — pinos do ESP32-2432S028R e o driver da tela (TFT_eSPI).
- `src/persistence` — contrato de gravar o snapshot.
- `src/main.cpp` — sobe um recém-nascido em memória, que não aparece na tela, e mostra o Hello.

Arquitetura: [docs/engineering/architecture.md](../docs/engineering/architecture.md).

## Preparar o computador

1. Instale o [PlatformIO](https://platformio.org/install): a extensão do VS Code/Cursor ou o `pip install platformio`. Biblioteca e configuração da tela vêm do `platformio.ini`; não há `User_Setup.h` para editar.
2. Instale o driver da ponte USB da placa. A maioria dos CYD usa CH340 ([driver da WCH](https://www.wch-ic.com/downloads/CH341SER_EXE.html)); alguns usam CP2102 ([driver da Silicon Labs](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers)). O nome do chip está impresso perto do conector USB.

## Ver a porta

Conecte a placa com um cabo que transmite dados. No Windows, abra o Gerenciador de Dispositivos e procure em **Portas (COM e LPT)** algo como `USB-SERIAL CH340 (COM5)`. Ou, no terminal:

```bash
pio device list
```

Sem porta nenhuma:

- Troque o cabo. Cabo que só carrega acende a placa e não cria porta.
- Confira o driver do passo 2 e reconecte.

## Gravar o Hello

Dentro de `firmware/`:

```bash
pio run -e cyd -t upload
```

O PlatformIO acha a porta sozinho. Com mais de uma, acrescente `--upload-port COM5`.

Se a gravação parar em `Connecting...`, segure o botão **BOOT** da placa quando essa linha aparecer e solte quando a porcentagem começar a subir.

## O que se espera na tela

Fundo preto, em paisagem:

- `Ola!` em caramelo;
- `A placa esta pronta.` em branco;
- `ESP32-2432S028R - 320x240` embaixo, menor.

Sem pet, sem barra, sem toque. Tela apagada depois de uma gravação que terminou não conta como Hello: anote o que apareceu no log e não feche o PRD.

Se o texto sair espelhado ou com as cores trocadas, o lote da placa usa outro controlador. Anote e abra um `fix/` contra o PRD 0000; não ajuste em `User_Setup.h` local.

## Testes do domínio

O computador precisa de `g++` no PATH. Dentro de `firmware/`:

```bash
pio test -e native
```

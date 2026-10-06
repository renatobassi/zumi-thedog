# Firmware

Alvo `cyd`: ESP32-2432S028R (CYD clássico). Alvo `native`: testes do domínio no computador.

Hoje o `cyd` desenha o Zumi do [PRD 0003](../docs/product/prds/0003-zumi-na-tela.md) e os quatro cuidados do [PRD 0004](../docs/product/prds/0004-cuidado-pelo-toque.md). O ciclo do [PRD 0001](../docs/product/prds/0001-ciclo-de-cuidado.md) roda no domínio e, no firmware da placa, também no tempo ligado. O [PRD 0002](../docs/product/prds/0002-estado-na-placa.md) grava esse ciclo na flash da própria placa. Desligar não avança as barras.

- `src/domain` — contrato do estado e o ciclo de cuidado. Testável sem a placa.
- `src/ui` — estado entra, tela sai. Não mexe em barra por conta própria. `frame.cpp` escolhe pose, comprimento e alvos; `screen.cpp` traduz o toque na ação do ciclo; `zumi.cpp` desenha. `hello.cpp` é a tela antiga do PRD 0000.
- `src/hal` — pinos do ESP32-2432S028R, o driver da tela (TFT_eSPI) e o SPI separado do toque.
- `src/persistence` — grava e lê o snapshot. No computador o teste usa memória falsa. Na placa, a flash NVS.
- `src/main.cpp` — restaura o ciclo ao ligar, deixa o tempo correr enquanto a placa está na tomada, aplica um toque por aperto e grava quando o cuidado muda.

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

## Gravar a tela

Dentro de `firmware/`:

```bash
pio run -e cyd -t upload
```

O PlatformIO acha a porta sozinho. Com mais de uma, acrescente `--upload-port COM5`.

Se a gravação parar em `Connecting...`, segure o botão **BOOT** da placa quando essa linha aparecer e solte quando a porcentagem começar a subir.

## O que se espera na tela

Fundo preto, em paisagem: o caramelo na pose da manta à esquerda, quatro barras com os nomes Fome, Energia, Diversao e Higiene, e à direita os alvos Comer, Brincar, Dormir e Banho. No nascimento as quatro barras vão até o fim da trilha. A barra baixa é mais curta. A fonte da placa não tem acento, então Diversão aparece como Diversao.

Um toque em Comer, Brincar, Dormir ou Banho pede essa ação uma vez. Segurar o dedo não repete. Dormindo, o mesmo lugar diz Acordar. Se a ação não vale, a frase some sozinha e as barras ficam iguais: “Nao brincou” quando falta energia, “Esta dormindo” quando ele está no sono. Toque fora dos quatro nomes não muda nada. O serial mostra a mesma frase.

Para ver a fome mais curta sem esperar o decaimento, no serial a 115200:

```text
estado 20 100 100 100 acordado
```

A fome fica bem menor que as outras três. Fase sem sprite próprio, e dormindo enquanto não houver pose de sono, continuam na manta.

Tela apagada depois de uma gravação que terminou não conta: anote o que apareceu no log.

Se o desenho sair espelhado ou com as cores trocadas, o lote da placa usa outro controlador. Anote e abra um `fix/` contra o PRD 0003; não ajuste em `User_Setup.h` local.

Se o dedo acerta o nome errado, o lote calibrado do toque é outro. Anote o canto e abra um `fix/` contra o PRD 0004. O toque usa o SPI próprio do CYD (CLK 25, MOSI 32, MISO 39, CS 33), não o SPI da tela.

## Estado depois de desligar

O serial a 115200 mostra o ciclo, por exemplo `zumi fome=100 energia=100 diversao=100 higiene=100 acordado`. Para repetir os casos 1 e 3 do PRD 0002, envie uma linha e desligue a USB:

```text
estado 40 70 55 80 acordado
```

Ao ligar de novo, a mesma linha tem de voltar com esses números, mesmo que a placa tenha ficado horas sem energia. O tempo da gaveta não entra nas barras. Se a flash estiver inválida ou vazia, nasce acordado com as quatro barras em 100.

## Testes do domínio

No Windows, se não houver `g++` no PATH, o teste usa o MinGW que o PlatformIO já baixou. Dentro de `firmware/`:

```bash
pio test -e native
```

# ADR 0001 — Camadas e PlatformIO

## Status

Aceito.

## Contexto

O produto é um pet offline num ESP32 com a pinagem quase toda tomada pela tela. O repositório também serve de case: alguém de produto precisa achar a regra do Zumi sem ler driver, e alguém de engenharia precisa testar essa regra sem a placa na USB.

A descoberta começou em Arduino IDE, com `User_Setup.h` editado na pasta de bibliotecas da máquina. Isso não viaja com o repositório e não distingue regra de desenho.

## Decisão

- PlatformIO em `firmware/`, com ambiente `cyd` (placa) e `native` (teste).
- Domínio sem hardware. HAL com os pinos do ESP32-2432S028R. UI e persistência dependem do snapshot, não uma da outra.
- Driver de tela e áudio só entram com PRD da feature que os usa.

## Consequências

- Dá para revisar um PR de regra de jogo olhando `src/domain` e `test/`.
- O primeiro firmware que gravar na placa precisa de um PRD de “pixel na tela”; o esqueleto sozinho não mostra o Zumi.
- Trocar o CYD por um ESP32-S3 muda `hal` e um ADR novo. O domínio do pet permanece.

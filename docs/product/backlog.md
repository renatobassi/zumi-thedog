# Backlog

Fila de produto. O detalhe está no PRD. Status de código segue o status do arquivo: só `aprovado` libera branch de firmware.

O 0000, o 0001, o 0002, o 0003 e o 0004 estão `aprovado`. O 0000 está entregue na placa. O 0001 está entregue no teste nativo. O 0002 está entregue no teste nativo e no firmware da flash; o corte da USB ainda não foi visto na mesa. O 0003 desenha a pose da manta e as barras no teste nativo; o reconhecimento na placa ainda não foi visto na mesa. O 0004 dispara os quatro cuidados no teste nativo; acertar os alvos na placa ainda não foi visto na mesa. Os outros estão `em crítica`: a coluna Decisão é a recomendação da seção Crítica, ainda sem aceite.

| Ordem | PRD | Entrega | Depende de | Decisão | Código |
|---|---|---|---|---|---|
| 1 | [0000](prds/0000-hello-na-placa.md) | Placa reconhecida e Hello na tela | — | seguir | entregue: Hello visto na placa |
| 2 | [0001](prds/0001-ciclo-de-cuidado.md) | Barras, sono e ações no tempo ligado | — | seguir | entregue: oito casos no teste nativo |
| 3 | [0002](prds/0002-estado-na-placa.md) | O ciclo sobrevive a desligar | 0001 | seguir | entregue no teste nativo; flash no firmware; falta ver o corte da USB |
| 4 | [0003](prds/0003-zumi-na-tela.md) | Zumi e barras na tela 320×240 | 0000, 0001, sprites no repo | encolher | entregue no teste nativo; falta reconhecer na placa |
| 5 | [0004](prds/0004-cuidado-pelo-toque.md) | Quatro cuidados pelo toque | 0001, 0003 | seguir | entregue no teste nativo; falta acertar na placa |
| 6 | [0005](prds/0005-crescimento.md) | Quatro fases pela idade ligada | 0001, 0002, 0003 | encolher | espera aprovação |
| 7 | [0007](prds/0007-doenca-e-a-rua.md) | Doente e volta pra rua | 0001, 0002, 0004 | seguir | espera aprovação |
| 8 | [0006](prds/0006-humor-e-poses.md) | Pose e animação curta | 0003, 0004, 0005, 0007, sprites | encolher | espera arte e aprovação |
| — | [0008](prds/0008-cara-de-culpa.md) | Cara de culpa | loop na mesa | adiar | não abre |
| — | [0009](prds/0009-susto-com-barulho.md) | Susto com barulho alto | hardware de áudio | adiar | não abre |
| — | [0010](prds/0010-voz-e-latido.md) | “Passear” falado e latido | outro hardware ou rede | adiar | não abre |
| — | [0011](prds/0011-presenca-fora-da-placa.md) | Telegram, app ou Wi-Fi | problema fora da mesa | adiar | não abre |

## Como sair da crítica

1. ~~Começar pelo Hello na placa.~~ Feito.
2. ~~Ciclo de cuidado.~~ Feito em 2026-10-05, com a tabela 0.1. Se a tabela mudar, a versão do 0001 sobe e os casos acompanham.
3. ~~Estado na placa.~~ Feito em 2026-10-05 no computador. O firmware grava na flash. O corte da USB ainda precisa ser visto na mesa.
4. ~~Zumi na tela.~~ Feito em 2026-10-05 no computador, com a pose da manta no repositório. O reconhecimento na placa ainda precisa ser visto na mesa.
5. ~~Cuidado pelo toque.~~ Feito em 2026-10-05 no computador. Os casos 1 a 6 passam com toque simulado. A mesa ainda precisa ver o dedo acertar os alvos.
6. Trocar o status para `aprovado` só com a decisão `seguir` ou `encolher` já reescrita no corpo.
7. Aí sim a branch de código, uma por PRD.

## Premissas que a aprovação do 0001 trava

Estas escolhas não foram medidas com uso. Estão escritas para o primeiro ciclo ser implementável. Se mudarem, mudam no 0001 e a versão sobe.

- A placa permanece ligada. Hora é hora de firmware rodando.
- Acordado, por hora: fome −8, energia −6, diversão −10, higiene −4.
- Dormindo, por hora: fome −4, energia +20, diversão −2, higiene 0.
- Alimentar +40 fome. Brincar +40 diversão e −15 energia, se energia ≥ 15. Banho +50 higiene e −10 diversão. Tudo limitado a 0–100.
- Doente: fome ou energia ≤ 10 por 60 minutos. Rua: 24 horas doente. Fases: 24 h, 72 h e 168 h de placa ligada.

Mapa: [roadmap.md](roadmap.md).

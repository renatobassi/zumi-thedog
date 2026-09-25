# Backlog

Fila de produto. O detalhe está no PRD. Status de código segue o status do arquivo: só `aprovado` libera branch de firmware.

Hoje todos estão `em crítica`. A coluna Decisão é a recomendação da seção Crítica, ainda sem aceite.

| Ordem | PRD | Entrega | Depende de | Decisão | Código |
|---|---|---|---|---|---|
| 1 | [0000](prds/0000-hello-na-placa.md) | Placa reconhecida e Hello na tela | — | seguir | espera aprovação |
| 2 | [0001](prds/0001-ciclo-de-cuidado.md) | Barras, sono e ações no tempo ligado | — | seguir | espera aprovação |
| 3 | [0002](prds/0002-estado-na-placa.md) | O ciclo sobrevive a desligar | 0001 | seguir | espera aprovação |
| 4 | [0003](prds/0003-zumi-na-tela.md) | Zumi e barras na tela 320×240 | 0000, 0001, sprites no repo | encolher | espera arte e aprovação |
| 5 | [0004](prds/0004-cuidado-pelo-toque.md) | Quatro cuidados pelo toque | 0001, 0003 | seguir | espera aprovação |
| 6 | [0005](prds/0005-crescimento.md) | Quatro fases pela idade ligada | 0001, 0002, 0003 | encolher | espera aprovação |
| 7 | [0007](prds/0007-doenca-e-a-rua.md) | Doente e volta pra rua | 0001, 0002, 0004 | seguir | espera aprovação |
| 8 | [0006](prds/0006-humor-e-poses.md) | Pose e animação curta | 0003, 0004, 0005, 0007, sprites | encolher | espera arte e aprovação |
| — | [0008](prds/0008-cara-de-culpa.md) | Cara de culpa | loop na mesa | adiar | não abre |
| — | [0009](prds/0009-susto-com-barulho.md) | Susto com barulho alto | hardware de áudio | adiar | não abre |
| — | [0010](prds/0010-voz-e-latido.md) | “Passear” falado e latido | outro hardware ou rede | adiar | não abre |
| — | [0011](prds/0011-presenca-fora-da-placa.md) | Telegram, app ou Wi-Fi | problema fora da mesa | adiar | não abre |

## Como sair da crítica

1. Começar pelo Hello na placa. O ciclo de cuidado pode ser lido em paralelo: ele não usa a tela.
2. Se a tabela de taxas do 0001 não servir, mudar a tabela e subir a versão antes de aprovar.
3. Trocar o status para `aprovado` só com a decisão `seguir` ou `encolher` já reescrita no corpo.
4. Aí sim a branch de código, uma por PRD.

## Premissas que a aprovação do 0001 trava

Estas escolhas não foram medidas com uso. Estão escritas para o primeiro ciclo ser implementável. Se mudarem, mudam no 0001 e a versão sobe.

- A placa permanece ligada. Hora é hora de firmware rodando.
- Acordado, por hora: fome −8, energia −6, diversão −10, higiene −4.
- Dormindo, por hora: fome −4, energia +20, diversão −2, higiene 0.
- Alimentar +40 fome. Brincar +40 diversão e −15 energia, se energia ≥ 15. Banho +50 higiene e −10 diversão. Tudo limitado a 0–100.
- Doente: fome ou energia ≤ 10 por 60 minutos. Rua: 24 horas doente. Fases: 24 h, 72 h e 168 h de placa ligada.

Mapa: [roadmap.md](roadmap.md).

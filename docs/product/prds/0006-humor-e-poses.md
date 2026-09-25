# PRD — Humor e poses

| Campo | Valor |
|---|---|
| Status | `em crítica` |
| Versão | 0.1 |
| Autor | Produto |
| Última edição | 2026-09-25 |

## 1. Propósito e escopo

O Zumi precisa parecer o estado em que está, não só a barra. Esta entrega escolhe a pose pelo humor e troca dois quadros nas ações e no abano.

Entra: prioridade de pose; abano quando está bem; faminto; dormindo; doente; os dois quadros de brincar, comer e banho logo depois da ação aceita.

Não entra: cara de culpa, quadro desenhado que não esteja no repositório, som.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | Reconhecer feliz, fome, sono, doença e a ação que acabou de pedir |
| Produto | A arte da descoberta ter hora certa de aparecer |
| Engenharia | Uma ordem única quando duas poses poderiam valer ao mesmo tempo |

## 3. Pesquisa

No chat, a pose de feliz virou abanar o rabo quando a média das barras passa de 60, em dois quadros. Brincar, comer e banho duram 2 a 3 segundos depois do comando, também em dois quadros. Dormindo e doente já eram emoções da arte. Faminto é a fome baixa, com o osso. Não há teste de quantos quadros a pessoa percebe no TFT. A premissa é dois quadros, como a descoberta pediu ao dizer que cada animação precisava de pelo menos dois para “ganhar vida”.

Os tempos ficam no meio da faixa dita no chat: 2,5 segundos de ação. A alternância dos dois quadros é contínua enquanto a pose durar. A descoberta citou cerca de 6 trocas por segundo no abano, 4 na bolinha e 3 em comer e banho. Esta versão usa isso.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Uma pose por vez | Duas emoções ao mesmo tempo não cabem no centro | Misturar sprites |
| Abano, fome, sono, doença | A barra sozinha não comunica o humor | Texto duplicando a pose |
| Ação em 2,5 s | O toque não tem resposta de corpo | Animação que muda a regra |

## 5. Casos de uso

1. **Bem.** Dado acordado, não doente, média das quatro barras maior que 60, fome maior que 25, quando a tela repousa, então a pose é abanando, alternando dois quadros.
2. **Faminto.** Dado fome ≤ 25, acordado, não doente, sem ação recente, quando a tela repousa, então a pose é faminto, mesmo se a média ainda passar de 60.
3. **Sono.** Dado dormindo, quando a tela desenha, então a pose é dormindo, por cima de fome e de abano.
4. **Doente.** Dado doente e acordado, quando a tela repousa, então a pose é doente, por cima de faminto e de abano.
5. **Ação.** Dado brincar aceito, quando passam até 2,5 segundos, então a pose é brincando em dois quadros e, ao fim, volta à pose de repouso. O mesmo vale para comer e para banho, cada um com a sua pose.
6. **Ação recusada.** Dado brincar recusado, quando o toque acaba, então a pose de brincar não entra.
7. **Rua.** Dado que voltou pra rua, quando a tela desenha, então não há pose de cuidado; vale o adeus do PRD da rua.
8. **Sprite faltando.** Dado humor sem os dois quadros no repositório, quando a pose seria essa, então fica o quadro único se existir um, ou a pose parada da fase. A entrega não se dá por pronta se o quadro daquele humor não está versionado.

## 6. Fluxo

Caminho principal: a tela consulta o estado, aplica a prioridade, desenha o quadro e troca com o par enquanto a pose durar.

Prioridade, da que ganha para a que perde: rua; ação aceita nos últimos 2,5 segundos; dormindo; doente; faminto; abano; pose parada da fase.

Caminho de falha: ação recusada não inicia os 2,5 segundos. Sprite ausente cai para a pose mais simples, e a liberação exige a arte no repositório.

## 7. Requisitos

**Uso.** A pessoa distingue abano, fome, sono, doença, brincar, comer e banho sem ler um dicionário. As barras continuam visíveis durante a ação.

**Técnicos, como restrição.** A pose não altera barra. Dois quadros versionados por pose animada. Enquanto a pose durar, os quadros alternam nesta cadência: abano cerca de 6 vezes por segundo, brincar cerca de 4, comer e banho cerca de 3. Dormindo alterna o par se os dois quadros existirem, senão fica parado. Offline. Resolução 320×240.

**Suporte.** Incluir a cara de culpa no futuro não muda esta prioridade: ela entra por PRD próprio, por cima ou por baixo, escrito lá. Trocar a arte não muda a prioridade.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| Prioridade | Teste que, para cada caso 1 a 7, informa a pose escolhida | A pose é a da seção 5 |
| Leitura humana | Na placa, uma pessoa vê abano, fome, sono e uma ação | Nomeia os quatro sem legenda externa |

## 9. Marcos

1. A prioridade passa no computador, sem desenhar pixel.
2. Os pares de sprite estão no repositório.
3. A placa mostra os casos 1, 2, 4 e 5.

## 10. Critérios de liberação

- [ ] Os casos de uso da seção 5 passam.
- [ ] O KPI da seção 8 foi observado do jeito descrito.
- [ ] Product SEO está `não se aplica`.
- [ ] Os quadros usados estão no repositório.

## 11. Product SEO

`não se aplica`

Animação só na placa.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | O Zumi fica na pose da fase para sempre e o toque não tem corpo |
| Corte menor | Sete poses com a prioridade acima e 2,5 segundos. Sem culpa e sem quadro extra |
| Solução mais completa | Mais quadros, piscada aleatória e easter egg aumentam arte antes do humor básico estar na placa |

O corte menor é a proposta.

## 13. Crítica

- O propósito é um problema de leitura: a pessoa já terá barras, e ainda assim a descoberta aprovou o mascote pelas expressões.
- A pesquisa sustenta quais poses existem e a faixa de 2 a 3 segundos. A cadência em trocas por segundo veio do chat, sem teste no TFT. Se na placa o abano ficar nervoso, a versão sobe e só a cadência muda.
- O CYD segura dois quadros pequenos alternados. Não segura vídeo.
- “Ganhar vida” sem alguém nomear a pose seria vaidade. O KPI pede o nome.
- O que piora: durante 2,5 segundos a pose de repouso some. As barras ficam. É curto de propósito.

Decisão: `encolher`.

Não aprovar sem os sprites no repositório.

## 14. Fora desta entrega

Cara de culpa, latido, susto, mais de dois quadros, pose que muda número de barra.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Prioridade de humor e ações de 2,5 segundos em dois quadros. |

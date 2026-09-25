# PRD — Cuidado pelo toque

| Campo | Valor |
|---|---|
| Status | `em crítica` |
| Versão | 0.1 |
| Autor | Produto |
| Última edição | 2026-09-25 |

## 1. Propósito e escopo

O cuidado precisa acontecer com o dedo na placa, sem computador e sem aplicativo. Esta entrega liga o toque às ações do ciclo e mostra quando a ação foi recusada.

Entra: quatro alvos — Comer, Brincar, Dormir, Banho — e o alvo Dormir virando Acordar enquanto dorme; retorno visível de ação aceita e de ação recusada.

Não entra: pose animada da ação, voz, botão físico extra, gesto de arrastar.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | Cuidar só com a tela que já está na mão |
| Produto | O touch resistivo do CYD não virar controle de precisão |
| Engenharia | Separar o dedo da regra: o toque pede a ação, não decide o número |

## 3. Pesquisa

A descoberta escolheu o toque que a placa já tem, na variante resistiva ESP32-2432S028R. Toque resistivo erra mais com a unha do que com a ponta, e a própria descoberta recomendou caneta se viesse no anúncio. Não houve teste de usabilidade na placa. A premissa é alvo grande, um por vez, com nome escrito.

As recusas já estão no ciclo: dormir bloqueia comer, brincar e banho; brincar exige energia de pelo menos 15.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Quatro alvos nomeados | Sem rótulo, a pessoa não descobre o cuidado | Desenho artístico do botão |
| Dormir vira Acordar | Sem isso, o sono não tem saída pelo dedo | Acordar sozinho quando a energia enche, que já é regra |
| Recusa visível | Toque que não muda nada parece placa quebrada | Explicar a taxa por hora |

## 5. Casos de uso

1. **Comer.** Dado acordado com fome 50 e a tela do Zumi visível, quando a pessoa acerta Comer, então a fome sobe 40 como no ciclo e a tela mostra que comeu.
2. **Brincar sem energia.** Dado energia 14, quando a pessoa acerta Brincar, então as barras não mudam e a tela mostra que ele não brincou.
3. **Dormir.** Dado acordado, quando a pessoa acerta Dormir, então ele fica dormindo e o mesmo lugar passa a dizer Acordar.
4. **Acordar.** Dado dormindo, quando a pessoa acerta Acordar, então ele fica acordado e o lugar volta a dizer Dormir.
5. **Cuidado dormindo.** Dado dormindo, quando a pessoa acerta Comer, Brincar ou Banho, então nada muda nas barras e a tela mostra a recusa.
6. **Toque torto.** Dado um toque fora dos quatro alvos, quando a tela lê, então nenhuma ação dispara.

## 6. Fluxo

Caminho principal: olhar o Zumi, escolher um nome, tocar, ver a barra ou o sono mudar.

Caminho de falha: toque fora não faz nada. Toque numa ação recusada avisa e não muda o ciclo. Um segundo toque no alvo certo funciona. Não há confirmação dupla: um acerto dispara uma vez.

## 7. Requisitos

**Uso.** Os quatro nomes cabem na tela junto do Zumi e das barras. O alvo é grande o bastante para a ponta do dedo ou a caneta, não um pixel. O nome está em português: Comer, Brincar, Dormir ou Acordar, Banho. A recusa é uma frase curta ou um sinal que suma sozinho, sem tapar as barras para sempre.

**Técnicos, como restrição.** Touch resistivo do CYD clássico. Offline. O toque só escolhe a ação do ciclo. Não altera número por conta própria. Segurar o dedo não repete a ação em rajada: um toque, uma tentativa.

**Suporte.** Continua verdadeiro se a pose mudar de tamanho, desde que os quatro alvos permaneçam acertáveis. Atualizar firmware não muda o significado dos quatro nomes.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| Acerto | Na placa, uma pessoa que não programou o firmware | Completa os casos 1, 3 e 4 sem instrução oral além dos nomes na tela |
| Erro entendível | A mesma pessoa, no caso 2 | Diz que a brincadeira não aconteceu, sem achar que a tela morreu |

## 9. Marcos

1. Os quatro alvos disparam o ciclo no computador com toque simulado, inclusive recusa e toque fora.
2. Os casos 1 a 6 na placa.

## 10. Critérios de liberação

- [ ] Os casos de uso da seção 5 passam.
- [ ] O KPI da seção 8 foi observado do jeito descrito.
- [ ] Product SEO está `não se aplica`.

## 11. Product SEO

`não se aplica`

Interação na placa, sem página pública.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | O ciclo só existe para quem tem o cabo e um depurador |
| Corte menor | Quatro alvos e recusa visível. Sem menu escondido e sem tela só de status |
| Solução mais completa | Tela de status separada e gesto longo não cabem no touch resistivo como primeiro cuidado |

O corte menor é a proposta.

## 13. Crítica

- O propósito é um problema: a visão é cuidar pelo toque, sem aplicativo.
- A pesquisa sustenta resistivo e quatro ações. Não houve teste de tamanho de alvo. Alvo grande é o corte contra esse risco.
- O CYD segura esses quatro alvos. Não segura alvo pequeno nem arraste preciso.
- KPI de “satisfação” seria vaidade. O KPI é concluir o cuidado e entender a recusa.
- O que piora: um toque errado no meio da tela não faz nada, e a pessoa pode tentar de novo. Rajada de toque não entra, para um dedo parado não esvaziar a energia.

Decisão: `seguir`.

## 14. Fora desta entrega

Animação da ação, tela extra de estatística, som de clique, botão físico, voz.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Quatro alvos e a recusa visível no touch resistivo. |

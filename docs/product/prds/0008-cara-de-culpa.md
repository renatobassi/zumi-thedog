# PRD — Cara de culpa

| Campo | Valor |
|---|---|
| Status | `em crítica` |
| Versão | 0.1 |
| Autor | Produto |
| Última edição | 2026-09-25 |

## 1. Propósito e escopo

A descoberta pediu uma pose de culpa, com vaso quebrado, sem ligação com as barras. Esta entrega descreveria esse aparecimento. No corte atual ela não entra.

Entra, se um dia a decisão mudar: a pose por poucos segundos, rara, sem alterar barras.

Não entra agora: nada no firmware.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | Não precisa disto para cuidar |
| Produto | Guardar a ideia sem deixar ela furar a fila |
| Engenharia | Não abrir branch |

## 3. Pesquisa

No chat, a cara de culpa ficou como easter egg: cerca de 2 segundos, perto de 5% de chance por dia, ou depois de uma ausência, sem depender das barras. Não há problema de cuidado associado. Não há como observar “5% ao dia” numa mesa só.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Pose de culpa | Nenhum problema de cuidado. É personalidade | Barra, doença, ação |

## 5. Casos de uso

1. **Aparição.** Dado um dia de placa ligada, quando a chance dispara, então a pose aparece cerca de 2 segundos e as barras ficam iguais.
2. **Silêncio.** Dado que a chance não disparou, quando o dia passa, então a pose não aparece. Este caso não distingue “deu azar” de “não foi feito”.

## 6. Fluxo

Não há fluxo nesta fase. A pose não tem lugar na prioridade do humor enquanto a decisão for adiar.

## 7. Requisitos

**Uso.** Nenhum requisito de uso entra agora.

**Técnicos, como restrição.** O CYD clássico até desenha a pose. O que não segura é um KPI de evento raro.

**Suporte.** Adiar não apaga a arte. Se voltar, a prioridade de poses ganha uma linha nova e a versão daquele PRD sobe.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| Nenhum | Não há observação útil de 5% ao dia numa placa | Não liberar |

Um KPI que não dá para observar não entra. Por isso a entrega não libera.

## 9. Marcos

Nenhum marco demonstrável sozinho além de “não construir”.

## 10. Critérios de liberação

- [ ] Não se aplica enquanto a decisão for adiar.
- [ ] Product SEO está `não se aplica`.

## 11. Product SEO

`não se aplica`

Não há entrega pública nem de firmware.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | É a decisão desta versão |
| Corte menor | Culpa só depois de ausência longa, sem dado, ainda é extra |
| Solução mais completa | Vaso, chance diária e piscada |

## 13. Crítica

- O propósito é um desejo de personalidade, não um problema de quem cuida.
- A pesquisa ilustra a pose. Não sustenta a chance.
- O CYD desenha a pose. O limite não é o hardware.
- O KPI de 5% é vaidade: não dá para saber se falhou.
- O que piora se entrar agora: disputa a prioridade das poses e a atenção da primeira versão, antes do ciclo estar na mesa.

Decisão: `adiar`.

Não abre branch de código. Reabrir só com um problema observável e um KPI que uma pessoa vê de propósito, não por sorte.

## 14. Fora desta entrega

Tudo, até a decisão mudar.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Registrada para não entrar na fila do V0. |

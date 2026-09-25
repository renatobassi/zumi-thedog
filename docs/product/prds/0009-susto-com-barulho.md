# PRD — Susto com barulho

| Campo | Valor |
|---|---|
| Status | `em crítica` |
| Versão | 0.1 |
| Autor | Produto |
| Última edição | 2026-09-25 |

## 1. Propósito e escopo

A descoberta quis que um barulho alto assustasse o Zumi, com microfone, ainda offline. Esta entrega não entra no CYD clássico desta fase.

Entra, se um dia houver hardware aceito: uma pose de susto quando o som passa de um limiar, sem reconhecer palavra.

Não entra agora: microfone, pose, limiar, firmware.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | O Zumi da mesa não depende de ouvir a casa |
| Produto | Separar “volume alto” de “entender passear” |
| Engenharia | Não gastar pino da tela num microfone sem PRD aprovado |

## 3. Pesquisa

O chat separou duas ideias. Assustar com volume foi descrito como medição simples, offline, com um microfone INMP441. Entender a palavra “passear” foi descrito como inviável no ESP32 clássico sem nuvem. A lista de compra da V0 ficou só na placa. A visão recusa microfone até um PRD próprio. Este é esse PRD, e a crítica adia.

No clássico, tela e toque já ocupam quase todos os pinos. Microfone entra dividindo pino com o cartão, que esta fase também não usa. Não há medida de que barulho alto seja o problema de quem cuida do Zumi.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Susto por volume | Nenhum problema demonstrado. Seria reação de ambiente | Reconhecer fala |
| Pose assustada | Sem o microfone, não tem gatilho | Latido |

## 5. Casos de uso

1. **Estalo.** Dado o microfone instalado e um limiar combinado, quando o volume passa do limiar, então a pose de susto aparece por um instante e as barras não mudam.
2. **Casa quieta.** Dado volume abaixo do limiar, quando o tempo passa, então a pose de susto não aparece.

Estes casos não são meta desta versão.

## 6. Fluxo

Não há fluxo na placa atual. O Zumi não ouve.

## 7. Requisitos

**Uso.** Nenhum.

**Técnicos, como restrição.** O CYD clássico não tem microfone na compra. Acrescentar um disputa pino com a tela. A visão não aceita esse hardware nesta fase. Reconhecimento de palavra continua fora mesmo deste PRD.

**Suporte.** Adiar deixa o cuidado válido sem áudio.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| Nenhum na V0 | Sem microfone não há sinal | Não liberar |

## 9. Marcos

Nenhum. O primeiro marco, no futuro, seria o hardware aceito num PRD que substitua este.

## 10. Critérios de liberação

- [ ] Não se aplica enquanto a decisão for adiar.
- [ ] Product SEO está `não se aplica`.

## 11. Product SEO

`não se aplica`

Sem entrega.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | É a decisão |
| Corte menor | Susto sem palavra ainda pede microfone e pino |
| Solução mais completa | Voz e latido no mesmo passo |

## 13. Crítica

- O propósito é um desejo de reação, não o problema de quem esquece de cuidar.
- A pesquisa mostra que o volume é mais viável que a fala. Não mostra que alguém precise disso para o Zumi existir.
- O CYD clássico não segura o microfone sem negociar pino. Esse é o corte.
- Um KPI de “se assustou” sem limiar medido na casa real seria vaidade.
- O que piora se entrar agora: a primeira versão para de ser só a placa e o toque.

Decisão: `adiar`.

Não abre branch. Reabrir com a placa que tenha pino de sobra, ou com um problema de cuidado que o som resolva.

## 14. Fora desta entrega

Microfone, limiar, pose de susto, palavra falada, alto-falante.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Susto registrado e adiado no CYD clássico. |

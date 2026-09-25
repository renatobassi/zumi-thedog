# PRD — Presença fora da placa

| Campo | Valor |
|---|---|
| Status | `em crítica` |
| Versão | 0.1 |
| Autor | Produto |
| Última edição | 2026-09-25 |

## 1. Propósito e escopo

A descoberta sugeriu Telegram, um espelho no celular e Wi-Fi para avisar que o Zumi está com fome. A visão recusa aplicativo, Telegram, Wi-Fi e API para o bichinho existir. Esta entrega não entra.

Entra, só se um problema futuro for “não estou na mesa e preciso saber”: um aviso fora da placa.

Não entra agora: conta, mensagem, widget, sincronização, relógio pela internet.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | O Zumi existe com a tomada e o toque |
| Produto | A fila não reintroduzir o assistente conectado |
| Engenharia | O domínio do pet continua sem rede |

## 3. Pesquisa

O chat listou persistência local, Telegram, widget e “modo Jarvis” como evolução porque o CYD tem Wi-Fi. A pessoa não descreveu um caso em que esteja longe da mesa e precise do aviso. A compra e a visão fecharam o produto na mesa, offline. Não há usuário esperando mensagem.

Hora pela internet também resolveria o tempo desligado. Isso é outro problema, já cortado no PRD de estado: sem energia não há relógio, e a rede não é o conserto desta fase.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Aviso de fome no Telegram | Nenhum caso atual. A pessoa está na mesa | Cuidar pelo celular |
| Widget com o mesmo estado | Duplica a tela sem um segundo lugar de uso | Conta |
| Hora via Wi-Fi | Faria o tempo da gaveta contar, e a visão não pediu | RTC |

## 5. Casos de uso

1. **Longe.** Dado que a pessoa não está na mesa e o Zumi ficou com fome crítica, quando o aviso existir, então ela fica sabendo sem olhar a placa.

Este caso não é promessa desta versão. O caso prometido é olhar a placa.

## 6. Fluxo

Não há fluxo fora da placa. Sem rede, sem mensagem, sem aplicativo.

## 7. Requisitos

**Uso.** Nenhum fora da mesa.

**Técnicos, como restrição.** Sem API, sem token, sem Wi-Fi para o pet funcionar. O CYD até tem rádio. A visão não usa.

**Suporte.** O estado continua só na placa. Não há o que dessincronizar.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| Nenhum | Não há canal externo | Não liberar |

## 9. Marcos

Nenhum.

## 10. Critérios de liberação

- [ ] Não se aplica enquanto a decisão for adiar.
- [ ] Product SEO está `não se aplica`.

## 11. Product SEO

`não se aplica`

Não nasce página, aplicativo nem URL.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | O Zumi da visão mora na mesa |
| Corte menor | Só um aviso, ainda assim pede conta e rede |
| Solução mais completa | App que também cuida, mais Telegram, mais nuvem |

## 13. Crítica

- O propósito é desejo de produto conectado. O problema real desta fase é o cuidado na mesa.
- A pesquisa cita o Wi-Fi do chip. Não cita alguém longe da placa.
- O clássico conecta. O produto desta fase não precisa, e a rede piora o offline.
- Mensagem enviada seria um KPI fácil de vaidade, sem um usuário que a espere.
- O que piora: o bichinho deixa de existir se a conta, o token ou a internet falham — o oposto da aposta.

Decisão: `adiar`.

Não abre branch. Reabrir só com um caso real de ausência, escrito de novo neste PRD, e com SEO se nascer página ou app.

## 14. Fora desta entrega

Telegram, aplicativo, widget, Wi-Fi, API, NTP, conta.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Presença fora da placa registrada e adiada. |

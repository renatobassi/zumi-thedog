# PRD — Voz e latido

| Campo | Valor |
|---|---|
| Status | `em crítica` |
| Versão | 0.1 |
| Autor | Produto |
| Última edição | 2026-09-25 |

## 1. Propósito e escopo

A descoberta quis que o Zumi latisse quando ouvisse “passear”, e um alto-falante para o latido. No CYD clássico isso não é o produto. Brincar continua sendo toque.

Entra, só numa geração de hardware ou de rede que a visão ainda não aceita: ouvir uma palavra e responder com som.

Não entra agora: microfone, alto-falante, modelo de fala, nuvem, a palavra “passear” como comando.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | Brincar sem falar e sem internet |
| Produto | Não reabrir o Jarvis dentro do tamagotchi |
| Engenharia | Não colocar API nem áudio no domínio do pet |

## 3. Pesquisa

O chat começou no Jarvis e saiu dele porque o clássico não transcreve fala. Três caminhos foram ditos: nuvem, troca para ESP32-S3 com modelo treinado em português, ou botão na tela. A pessoa comprou o CYD clássico. O S3 no Brasil ficou mais caro e irregular do que a primeira estimativa. A visão recusa microfone, alto-falante, a palavra “passear” reconhecida no clássico, e migração para S3 até um PRD próprio.

Este arquivo é esse PRD. A crítica adia os três caminhos.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Ouvir “passear” | Não resolve o cuidado. O toque em Brincar já pede a ação | Assistente geral |
| Latido | Não há problema de feedback que o texto e a pose não cubram na V0 | Música |

## 5. Casos de uso

1. **Palavra.** Dado um hardware que reconheça “passear” offline e em português, quando a pessoa fala, então a ação de brincar do ciclo dispara uma vez.
2. **Latido.** Dado o alto-falante aceito, quando a brincadeira é aceita, então soa um latido curto.

Não são meta enquanto a decisão for adiar. O caso vivo hoje é o toque em Brincar.

## 6. Fluxo

Na placa atual o fluxo de brincar é o toque. Fala não tem caminho. Se a rede cair, nada do Zumi pode depender disso — e por isso a fala não entra.

## 7. Requisitos

**Uso.** Nenhum requisito novo de fala.

**Técnicos, como restrição.** O ESP32 clássico não reconhece a palavra localmente com qualidade, segundo a descoberta. Nuvem quebra o offline da visão. S3 pede outra placa, outro preço e um modelo em português que o chat marcou como o trabalho mais difícil. Alto-falante disputa pino com a tela.

**Suporte.** O significado de Brincar permanece o do ciclo, com ou sem voz no futuro.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| Nenhum | Sem hardware de voz | Não liberar |

## 9. Marcos

Nenhum marco de construção.

## 10. Critérios de liberação

- [ ] Não se aplica enquanto a decisão for adiar.
- [ ] Product SEO está `não se aplica`.

## 11. Product SEO

`não se aplica`

Sem entrega.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | Brincar pelo toque já está no PRD de cuidado |
| Corte menor | Latido sem ouvir a palavra ainda pede alto-falante e pino |
| Solução mais completa | Jarvis com nuvem é o caminho que a descoberta abandonou |

## 13. Crítica

- O propósito é o desejo inicial de assistente, não o problema que o tamagotchi veio resolver.
- A pesquisa sustenta a limitação do clássico. Ela não sustenta comprar outra placa agora.
- O CYD clássico não segura a palavra offline. A nuvem viola o offline. O S3 é outra fase.
- “Latir é mais vivo” sem alguém dependendo do som para cuidar é vaidade nesta etapa.
- O que piora: o Zumi passa a precisar de peça, pino e talvez internet para uma ação que o dedo já faz.

Decisão: `adiar`.

Não abre branch. Reabrir só com hardware novo explícito na visão, ou com um problema de cuidado que o toque não resolva.

## 14. Fora desta entrega

Microfone, alto-falante, “passear” falado, latido, ESP32-S3, API de transcrição.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Voz e latido registrados e adiados. |

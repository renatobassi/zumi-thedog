# PRD — Crescimento

| Campo | Valor |
|---|---|
| Status | `em crítica` |
| Versão | 0.1 |
| Autor | Produto |
| Última edição | 2026-09-25 |

## 1. Propósito e escopo

O cuidado ao longo dos dias precisa mudar quem é o Zumi, não só as barras. Esta entrega faz a fase acompanhar o tempo de placa ligada desde a adoção.

Entra: quatro fases — recém-adotado na manta, filhote, adulto sentado, adulto pleno — e a pose parada correspondente quando o sprite existir.

Não entra: fase por nota de cuidado, evolução por Wi-Fi, pose de humor, volta de fase.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | Ver o filhote da manta crescer se a placa continua com ele |
| Produto | Um crescimento que não exige minijogo extra |
| Engenharia | Idade ligada guardada com o resto do estado |

## 3. Pesquisa

A descoberta desenhou quatro momentos: manta de recém-adotado, filhote, adulto sentado, adulto pleno. A visão repete essas fases. Não há dado de quantos dias uma pessoa aguenta olhar a mesma pose. Os limiares abaixo são premissa: um dia, três dias e sete dias de placa ligada. Batem a frase “horas depois” no primeiro salto e não exigem um mês para ver o adulto.

Idade é tempo de firmware rodando, o mesmo relógio do ciclo. Tempo na gaveta não envelhece, pelo mesmo limite do PRD de estado.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Idade desde a adoção | Sem idade, a manta é eterna | Contar só horas “bem cuidado” |
| Quatro fases | O desenho aprovado não aparece | Fase secreta |
| Pose da fase | A pessoa não lê um número de nível | Animação |

## 5. Casos de uso

1. **Manta.** Dado adoção nova, quando a idade ligada é menor que 24 horas, então a fase é recém-adotado na manta.
2. **Filhote.** Dado 24 horas ligadas desde a adoção e menos de 72, quando o estado avança, então a fase é filhote.
3. **Adulto sentado.** Dado 72 horas e menos de 168, então a fase é adulto sentado.
4. **Adulto pleno.** Dado 168 horas ou mais, então a fase é adulto pleno e não muda mais com a idade.
5. **Gaveta.** Dado 10 horas ligadas e depois um dia sem energia, quando liga, então a idade continua 10 horas e a fase continua a manta.
6. **Tela.** Dado que a pose da fase está versionada, quando a fase muda, então a tela mostra essa pose.

## 6. Fluxo

Caminho principal: a placa fica ligada, os dias passam, a pose muda nos três limiares. As barras continuam o ciclo, independentes da fase.

Caminho de falha: sprite da fase nova ausente usa a pose da fase anterior, como a tela já permite. A fase no estado ainda muda.

## 7. Requisitos

**Uso.** A pessoa não escolhe a fase. Ela percebe a troca olhando. Não há número de nível na tela.

**Técnicos, como restrição.** Limiares em horas de placa ligada desde a última adoção: 24, 72 e 168. A idade entra no estado gravado. Desligar não soma idade. A fase não altera as taxas do ciclo.

**Suporte.** Uma gravação antiga sem idade nasce com idade 0 e fase manta, sem travar. Nova adoção, quando existir no PRD da rua, zera a idade.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| Limiar | Teste do domínio com tempo injetado | Casos 1 a 5 com a fase exata |
| Pose | Placa, no limiar de 24 horas simuladas ou aceleradas de um jeito visível no teste | A pose deixa de ser a manta |

## 9. Marcos

1. Casos 1 a 5 no computador.
2. A idade sobrevive a desligar, junto do estado.
3. A pose na placa acompanha o caso 6.

## 10. Critérios de liberação

- [ ] Os casos de uso da seção 5 passam.
- [ ] O KPI da seção 8 foi observado do jeito descrito.
- [ ] Product SEO está `não se aplica`.

## 11. Product SEO

`não se aplica`

Crescimento só na placa.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | O Zumi não cresce e a arte de quatro fases não tem função |
| Corte menor | Idade ligada, sem bônus por barra alta. É esta entrega |
| Solução mais completa | Fase só se a média das barras ficou alta exige histórico de cuidado e pune quem esquece um dia — isso é doença, não crescimento |

O corte menor é a proposta.

## 13. Crítica

- O propósito mistura problema e desejo. O problema real é a arte de crescimento não ter regra. O desejo é “ver evoluir”. O corte por idade ligada resolve os dois sem minijogo.
- A pesquisa ilustra as quatro fases. Não prova 24, 72 e 168. Os números ficam nesta versão para serem trocados antes do `aprovado` se quiser ver o filhote no mesmo dia de demo: aí a versão sobe.
- O CYD segura quatro poses paradas. Não segura dezena de fases.
- KPI de retenção de sete dias seria vaidade nesta entrega. O KPI é o limiar.
- O que piora: esquecer a placa ligada uma semana faz o Zumi virar adulto mesmo negligenciado. A negligência é o PRD da rua, não uma fase a menos.

Decisão: `encolher`.

## 14. Fora desta entrega

Humor, doença, adoção de novo, acelerar crescimento por ação, fase que regride.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Quatro fases por idade de placa ligada. |

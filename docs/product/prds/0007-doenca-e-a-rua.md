# PRD — Doença e a rua

| Campo | Valor |
|---|---|
| Status | `em crítica` |
| Versão | 0.1 |
| Autor | Produto |
| Última edição | 2026-09-25 |

## 1. Propósito e escopo

Abandono longo precisa ter fim. Se fome ou energia ficam no chão, o Zumi adoece. Se continua assim por um dia ligado, ele volta pra rua. A pessoa pode adotar de novo.

Entra: estado doente, fim “voltou pra rua”, adoção que recomeça o ciclo, e um aviso dessas duas situações na tela.

Não entra: pose desenhada de doença se o sprite ainda não existir, veterinário, mais de uma vida paralela.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | Entender que esqueceu demais, e ter como começar outra vez sem apagar o firmware |
| Produto | A frase da visão, “volta pra rua”, com regra observável |
| Engenharia | Fim de jogo testável no computador, com o tempo injetado |

## 3. Pesquisa

A descoberta disse que descuido longo deixa doente ou faz o bichinho ir embora, e o briefing resumido no chat fixou “volta pra rua” depois de 24 horas sem cuidado. A visão repete o abandono. Não há teste com usuário. A premissa desta versão: o gatilho não é “qualquer barra”, é fome ou energia no chão, porque são as que impedem o bichinho de seguir. Diversão e higiene baixas mudam o humor depois; não matam nesta entrega.

Vinte e quatro horas contam com a placa ligada, como o resto do tempo do produto.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Doente | O chão da barra não tem consequência | Pose animada |
| Voltou pra rua | Doente eterno não tem fim | Mensagem no Telegram |
| Adotar de novo | A placa não pode ficar morta | Várias adoções com histórico |

## 5. Casos de uso

1. **Ainda não.** Dado fome 10 e energia 10 há 59 minutos ligados, quando o minuto não fecha 60, então não está doente.
2. **Fica doente.** Dado fome ≤ 10, ou energia ≤ 10, por 60 minutos ligados seguidos, quando o minuto fecha, então fica doente. Brincar passa a ser recusado mesmo com energia ≥ 15.
3. **Melhora.** Dado doente, quando fome e energia estão ambas ≥ 25, então deixa de estar doente e brincar volta a seguir o ciclo.
4. **A rua.** Dado doente por 24 horas ligadas seguidas, sem o caso 3 no meio, quando a hora fecha, então o cuidado para, as barras não descem nem sobem, e a tela diz que o Zumi voltou pra rua.
5. **Adotar.** Dado na rua, quando a pessoa adota de novo, então volta o nascimento do ciclo: acordado, barras 100, idade 0, fase manta, não doente.
6. **Queda no meio.** Dado 10 horas doente já contadas, quando desliga e liga, então continua doente com essas 10 horas, não com zero e não com o tempo da gaveta somado.

## 6. Fluxo

Caminho principal: a barra crítica fica no chão, passa uma hora, a tela marca doente. Comer, dormir e banho ainda valem. Se fome e energia sobem, a doença sai. Se o dia ligado acaba antes disso, a tela para no adeus.

Caminho de falha: na rua, Comer, Brincar, Dormir e Banho não fazem nada. O único passo é adotar. Toque fora desse convite não cria outro Zumi.

## 7. Requisitos

**Uso.** “Doente” aparece escrito mesmo sem sprite de orelha caída. “Voltou pra rua” cabe na tela e não depende de cor sozinha. Adotar de novo é um alvo tão grande quanto os cuidados.

**Técnicos, como restrição.** Offline. Critério: fome ≤ 10 ou energia ≤ 10 por 60 minutos ligados seguidos. Alta: as duas ≥ 25. Rua: 24 horas ligadas seguidas doente. O relógio do doente e o da rua fazem parte do estado gravado. Tempo sem energia não entra. Na rua o ciclo não avança.

**Suporte.** Gravação antiga sem estes campos nasce não doente e não na rua. Atualizar o firmware no meio das 10 horas não zera o contador se a gravação era válida.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| 60 minutos e 24 horas | Teste do domínio com tempo injetado | Casos 1 a 6 |
| Adeus legível | Na placa, estado forçado na rua | Uma pessoa lê que ele foi embora e acha adotar de novo sem ajuda de quem programou |

## 9. Marcos

1. Casos 1 a 6 no computador.
2. O contador sobrevive ao desligamento.
3. A placa mostra doente e a rua, e a adoção recomeça.

## 10. Critérios de liberação

- [ ] Os casos de uso da seção 5 passam.
- [ ] O KPI da seção 8 foi observado do jeito descrito.
- [ ] Product SEO está `não se aplica`.

## 11. Product SEO

`não se aplica`

Texto de fim de jogo só na placa.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | A placa abandonada fica para sempre num cachorro vazio |
| Corte menor | Doente e rua com texto, adoção única sem arquivo de vidas. É esta entrega |
| Solução mais completa | Morte por higiene, por diversão e por um dia sem nenhum toque, mesmo com barras altas, pune uma placa que só ficou quieta com o Zumi bem |

O corte menor é a proposta.

## 13. Crítica

- O propósito é um problema: sem fim, abandono não tem peso e a placa não tem recomeço.
- A pesquisa sustenta “doente” e “24 horas, volta pra rua”. Não sustenta quais barras. Fome e energia são a premissa escrita, trocável nesta versão.
- O CYD segura texto e um alvo de adoção. Não segura notificação longe da mesa.
- “Emocional” seria vaidade. O KPI é o relógio e a frase lida.
- O que piora: um dia ligado no chão acaba o Zumi. Quem viaja desliga a placa e o relógio para, pelo PRD de estado. Quem deixa ligado e esquece perde o bichinho. É a regra, dita antes de aprovar.

Decisão: `seguir`.

## 14. Fora desta entrega

Sprite de doente, som de choro, aviso no celular, mais de um Zumi, rua por higiene ou diversão.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Doença por fome ou energia e rua em 24 horas ligadas. |

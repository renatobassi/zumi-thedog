# PRD — Ciclo de cuidado

| Campo | Valor |
|---|---|
| Status | `em crítica` |
| Versão | 0.1 |
| Autor | Produto |
| Última edição | 2026-09-25 |

## 1. Propósito e escopo

O Zumi só é um bichinho se o cuidado mudar o estado com o tempo. Esta entrega define as quatro barras, o sono e as quatro ações, para que horas de placa ligada deixem o Zumi diferente de quando foi deixado.

Entra: fome, energia, diversão e higiene; acordado e dormindo; alimentar, brincar, dormir, banho e acordar; taxas por hora de placa ligada.

Não entra: pixel, toque, fase, doença, game over, som, rede.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | Saber que alimentar, brincar, dormir e dar banho têm efeito, e que o tempo sozinho piora o estado |
| Produto | Um ciclo fechado, com números que dá para mudar numa versão só |
| Engenharia | Regra testável no computador, sem tela e sem placa |

## 3. Pesquisa

O [chat de descoberta](https://agent.adapta.one/shared-chat/01a0c706-c54c-731d-81a3-0d01ff7a4667) trocou o assistente de voz por um tamagotchi no CYD clássico. A visão fixou quatro barras — fome, energia, diversão e higiene — e quatro cuidados: alimentar, brincar, dormir e dar banho. O decaimento foi descrito por hora, diferente acordado e dormindo. As taxas numéricas não estavam no texto visível do chat; a tabela abaixo é calibração para a promessa “horas depois, o estado mudou”, com a placa deixada ligada. Ainda não houve observação numa placa real.

O CYD clássico comprado não entra com relógio que sobreviva desligado. O tempo deste PRD é tempo de firmware rodando.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Quatro barras de 0 a 100 | Sem medida, não há descuido nem cuidado | O que a barra desenha na tela |
| Decaimento acordado | Ligado e esquecido, o Zumi não muda | Doença e game over |
| Perfil dormindo | Dormir não seria diferente de esperar | Animação de sono |
| Ações com recusa | Toque futuro não teria regra quando não pode | Área de toque |

## 5. Casos de uso

1. **Esquecer acordado.** Dado o Zumi acordado com as quatro barras em 100, quando passa 1 hora ligada sem ação, então fome fica 92, energia 94, diversão 90 e higiene 96.
2. **Alimentar.** Dado fome em 50 e acordado, quando alimenta, então fome fica 90. Dado fome em 80, quando alimenta, então fome fica 100.
3. **Brincar cansado.** Dado energia em 14 e acordado, quando brinca, então diversão e energia não mudam. Dado energia em 15 e diversão em 50, quando brinca, então diversão fica 90 e energia fica 0.
4. **Banho.** Dado higiene em 40 e diversão em 30, acordado, quando toma banho, então higiene fica 90 e diversão fica 20.
5. **Dormir e acordar sozinho.** Dado energia em 0 e as outras barras em 100, acordado, quando começa a dormir e passam 5 horas ligadas, então energia fica 100 e o Zumi está acordado. Nesse intervalo a fome cai 20 e a diversão cai 10. A higiene não muda.
6. **Acordar no meio.** Dado dormindo com energia em 40, quando acorda, então passa a acordado na hora, com as barras iguais às do instante do acorde.
7. **Cuidado no sono.** Dado dormindo, quando alimenta, brinca ou dá banho, então as barras não mudam e ele continua dormindo.
8. **Tempo parcial.** Dado acordado com barras em 100, quando passam 30 minutos ligados, então a variação é a metade inteira da hora: fome −4, energia −3, diversão −5, higiene −2.

## 6. Fluxo

Caminho principal, ainda sem tela: o Zumi nasce acordado, barras em 100. O tempo ligado aplica a taxa. A pessoa dispara uma ação. A ação aceita altera as barras na hora. Dormir troca o perfil até a energia chegar a 100 ou até acordar.

Caminho de falha: ação recusada não altera barra nem o fato de estar dormindo. Frações de hora arredondam o efeito para o inteiro mais próximo, sem sair de 0–100. O caso de 30 minutos fixa o arredondamento da metade.

## 7. Requisitos

**Uso.** Quem cuida consegue alimentar, brincar, mandar dormir, dar banho e acordar. Entende, quando houver tela, que uma ação recusada não aconteceu. Este PRD não exige a tela.

**Técnicos, como restrição.** Offline. O tempo não usa rede nem relógio externo. As taxas são por hora de execução e o efeito é proporcional ao tempo corrido. Valores:

| | Fome | Energia | Diversão | Higiene |
|---|---|---|---|---|
| Acordado, por hora | −8 | −6 | −10 | −4 |
| Dormindo, por hora | −4 | +20 | −2 | 0 |

| Ação | Efeito | Recusa |
|---|---|---|
| Alimentar | fome +40 | dormindo |
| Brincar | diversão +40, energia −15 | dormindo, ou energia &lt; 15 antes da ação |
| Banho | higiene +50, diversão −10 | dormindo |
| Dormir | passa a dormindo | já dormindo |
| Acordar | passa a acordado, barras iguais | já acordado |

Ao atingir energia 100 dormindo, acorda naquele instante. Nenhuma barra passa de 100 nem fica abaixo de 0.

**Suporte.** A mesma hora simulada duas vezes produz os mesmos números. Uma versão futura pode trocar a tabela; os casos deste PRD descrevem a 0.1.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| Hora esquecida | Teste do domínio no computador, sem placa | Os oito casos da seção 5, com os números exatos |
| Ação recusada | O mesmo teste | Barra e sono iguais aos de antes da recusa |

## 9. Marcos

1. Os oito casos passam no computador, com o tempo injetado, sem gravar a placa.

## 10. Critérios de liberação

- [ ] Os casos de uso da seção 5 passam.
- [ ] O KPI da seção 8 foi observado do jeito descrito.
- [ ] Product SEO está `não se aplica`.

## 11. Product SEO

`não se aplica`

A entrega é regra de cuidado. Não muda URL, página, título, mídia nem dado estruturado.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | Sem ciclo não há Zumi, só desenho |
| Corte menor | Uma barra só não cobre comer, sono, brincadeira e banho, que a descoberta já separou |
| Solução mais completa | Doença, fase e pixel junto atrasam a primeira regra testável |

## 13. Crítica

- O propósito é um problema: sem decaimento e sem ação, o cuidado não existe.
- A pesquisa sustenta as quatro barras e as quatro ações. Não sustenta os números. A tabela é premissa de calibração, concentrada aqui para mudar numa versão.
- O CYD clássico segura esta regra. Ela não pede pino, microfone nem rede.
- O KPI é o número do teste, não “engajamento”.
- Quem cuida ainda não vê nada. Esta entrega não piora a mesa; também não a melhora até os PRDs de tela e toque.

Decisão: `seguir`.

`aprovado` só depois desta crítica ser aceita. Se a tabela mudar, a versão sobe e os casos da seção 5 acompanham a tabela.

## 14. Fora desta entrega

Fase, pose, doença, “voltou pra rua”, toque, pixel, persistência, cara de culpa, áudio, voz e qualquer aviso fora da placa.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Primeira especificação do ciclo, com taxas de calibração. |

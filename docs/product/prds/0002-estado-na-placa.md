# PRD — Estado na placa

| Campo | Valor |
|---|---|
| Status | `em crítica` |
| Versão | 0.1 |
| Autor | Produto |
| Última edição | 2026-09-25 |

## 1. Propósito e escopo

O Zumi deixa de existir se desligar a placa apaga o cuidado. Esta entrega guarda o ciclo e o devolve igual ao ligar de novo.

Entra: gravar e ler o estado do cuidado que já existir; sobreviver a desligar e ligar; tempo desligado não avança as barras.

Não entra: relógio com pilha, nuvem, cartão microSD, a regra nova de barra, tela.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | Tirar da tomada e achar o mesmo Zumi, não um recém-nascido |
| Produto | A promessa “o estado fica na placa” sem depender de conta |
| Engenharia | Um contrato de gravar e ler, testável sem desenhar pixel |

## 3. Pesquisa

A visão exige estado gravado na própria placa. A lista de compra da descoberta é a placa, fonte e cabo. Não inclui relógio com bateria nem cartão. O ESP32 clássico perde a hora quando corta a energia. Por isso o tempo desligado não pode entrar no decaimento sem hardware que esta fase não comprou. A placa foi pensada para ficar na tomada; o desligamento é queda ou mudança de lugar, não a passagem da noite.

Não há medida de quantas vezes a pessoa desliga. A premissa é que perder o bichinho numa queda de energia quebra a confiança mais do que “pausar” a noite desligado.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Gravar o ciclo | Queda de energia volta o Zumi ao nascimento | O que cada barra significa |
| Restaurar ao ligar | A pessoa não recomeça o cuidado sem querer | Animação de “acordei” |
| Tempo desligado parado | Sem relógio, inventar horas seria mentira | RTC, NTP, Wi-Fi |

## 5. Casos de uso

1. **Queda no meio do cuidado.** Dado fome 40, energia 70, diversão 55, higiene 80, acordado, quando a placa desliga e liga, então os quatro números e o acordado voltam iguais.
2. **Queda dormindo.** Dado dormindo com energia 30 e fome 60, quando desliga e liga, então continua dormindo com energia 30 e fome 60.
3. **Horas na gaveta.** Dado um estado qualquer gravado, quando a placa fica horas sem energia e volta, então as barras são as gravadas, não as barras menos o tempo da gaveta.
4. **Primeira vez.** Dado que nunca houve gravação, quando liga, então o Zumi nasce como o ciclo define: acordado, barras em 100.
5. **Gravação falhou.** Dado que a leitura não fecha um estado válido, quando liga, então nasce de novo, acordado, barras em 100, e a pessoa não fica numa placa muda.

## 6. Fluxo

Caminho principal: o cuidado muda, a placa guarda, a energia cai, a energia volta, o mesmo cuidado aparece.

Caminho de falha: leitura inválida ou ausente começa uma vida nova. Não tenta adivinhar o meio do arquivo.

## 7. Requisitos

**Uso.** Depois de ligar, a pessoa encontra o Zumi do instante em que a energia caiu. Ela não precisa configurar conta nem cartão.

**Técnicos, como restrição.** A gravação cabe na memória da própria placa, sem rede e sem microSD. O instante de relógio de parede não é fonte do decaimento. Campos que uma entrega futura acrescentar nascem no valor inicial dessa entrega quando a gravação antiga não os tiver. Uma gravação antiga não impede a placa de ligar.

**Suporte.** Atualizar o firmware não pode transformar leitura inválida em travamento. O caso 5 continua valendo depois da atualização.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| Mesmo Zumi | Teste que grava, “desliga” e lê, mais uma vez na placa: desligar da USB e ligar de novo | Casos 1 a 4 com os números iguais aos de antes do corte |
| Não trava | Teste com gravação inválida | Caso 5: nasce de novo e aceita cuidado |

## 9. Marcos

1. Casos 1 a 5 no computador, com o armazenamento substituído por um falso.
2. Casos 1 e 3 repetidos na placa, desligando a USB.

## 10. Critérios de liberação

- [ ] Os casos de uso da seção 5 passam.
- [ ] O KPI da seção 8 foi observado do jeito descrito, inclusive o desligar da USB.
- [ ] Product SEO está `não se aplica`.

## 11. Product SEO

`não se aplica`

Não há página pública. O estado fica na placa de quem cuida.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | Cada queda apaga o cuidado e o Zumi não é de estimação |
| Corte menor | Pausar o tempo desligado já é o corte. Menor que isso é não gravar |
| Solução mais completa | Relógio com pilha ou hora pela rede contam a noite fora da tomada, e nenhum dos dois está comprado nem aceito na visão |

## 13. Crítica

- O propósito é um problema: perder o bichinho ao desligar.
- A pesquisa sustenta gravar na placa. A decisão de não contar o tempo desligado é limite do hardware comprado, não medida de preferência.
- O CYD clássico segura gravar na própria memória. Não segura hora certa depois do corte sem peça extra.
- KPI de “nunca perde” seria vaidade. O KPI é a igualdade antes e depois do corte, mais o nascimento limpo se a gravação quebrar.
- Quem cuida perde a passagem do tempo enquanto a placa está na gaveta. Isso é o custo do corte. Fica escrito para não parecer bug.

Decisão: `seguir`.

## 14. Fora desta entrega

Contar horas desligado, microSD, nuvem, tela, toque, doença, fase.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Persistência do ciclo com o tempo pausado sem energia. |

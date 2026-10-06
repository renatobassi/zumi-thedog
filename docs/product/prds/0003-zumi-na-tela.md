# PRD — Zumi na tela

| Campo | Valor |
|---|---|
| Status | `aprovado` |
| Versão | 0.2 |
| Autor | Produto |
| Última edição | 2026-10-05 |

## 1. Propósito e escopo

Quem está na mesa precisa reconhecer o Zumi e ler como ele está. Esta entrega coloca o cachorro e as quatro barras na tela 320×240.

Entra: uma pose parada por fase já existente no estado; as quatro barras com nome; o fato de estar dormindo, se o ciclo já estiver dormindo, com a pose de sono quando o sprite existir.

Não entra: toque, animação de dois quadros, poses de ação, doença desenhada, texto de game over.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | Olhar e saber quem é o Zumi e qual barra está baixa |
| Produto | A arte aprovada na descoberta entra no produto, não fica só no chat |
| Engenharia | Saber que pixel sem sprite versionado não é entrega |

## 3. Pesquisa

A descoberta fechou o mascote: vira-lata caramelo, não dragão. As fases desenhadas foram recém-adotado na manta, filhote, adulto sentado e adulto pleno. As emoções desenhadas foram feliz, faminto, dormindo e doente. Esta entrega usa pose parada. A fase ainda não muda até o PRD de crescimento; até lá a pose inicial é a da manta, que é o nascimento do ciclo.

A pose parada da manta está em `firmware/assets/sprites/manta.png`, gerada do pixel em `firmware/assets/sprites/build_manta.py`. Sono e as fases seguintes ainda não têm sprite próprio. A tela do CYD clássico é 320×240, touch resistivo, vista de perto na mesa.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Zumi reconhecível no centro | Uma tela de números não é o bichinho | Abanar, comer, brincar, banho |
| Quatro barras nomeadas | Sem nome, a pessoa não sabe o que cuidar | O decaimento em si |
| Sono visível | Dormindo e acordado não podem parecer iguais quando a pose existir | Acordar pelo toque |

## 5. Casos de uso

1. **Primeiro olhar.** Dado o Zumi recém-nascido e a placa ligada, quando a tela acende, então aparece o caramelo na pose da fase atual e quatro barras em 100, com os nomes Fome, Energia, Diversão e Higiene.
2. **Barra baixa.** Dado fome em 20 e as outras em 100, quando a pessoa olha, então a fome é visivelmente menor que as outras três.
3. **Fase.** Dado que o estado já está numa fase posterior, quando a tela desenha, então a pose é a dessa fase, não a da manta.
4. **Dormindo.** Dado dormindo e o sprite de sono versionado, quando a tela desenha, então a pose é a de sono e as barras continuam legíveis.
5. **Sem arte.** Dado que o sprite daquela pose não está no repositório, quando alguém pede para gravar o firmware, então esta entrega não se considera pronta.

## 6. Fluxo

Caminho principal: ligar a placa, ver o Zumi, ler as barras.

Caminho de falha: sprite ausente não vira retângulo sem dizer que a entrega falta arte. A liberação para no caso 5.

## 7. Requisitos

**Uso.** Em 320×240, o Zumi cabe no centro e as quatro barras cabem junto, com nome legível à distância de uma mesa. Não exige lupa nem cor como único sinal: a barra baixa é mais curta, não só mais vermelha. A fonte da placa não tem acento, então Diversão aparece como Diversao.

**Técnicos, como restrição.** Offline. O desenho não altera barra nem fase. A tela do CYD clássico é a superfície. Os sprites usados são os que estiverem versionados no repositório, exportados a partir da arte que a descoberta aprovou. Chat não é fonte de pixel na hora de gravar.

**Suporte.** Trocar um sprite no repositório não muda o número das barras. Uma fase sem sprite próprio usa a pose da fase anterior já versionada, e o caso 5 só falha se não houver pose nenhuma.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| Reconhecimento | Uma pessoa que viu a arte olha a placa ligada, sem legenda de fora | Diz que é o Zumi caramelo |
| Leitura da fome | A mesma pessoa, com fome em 20 e o resto em 100 | Aponta a fome como a barra baixa |

## 9. Marcos

1. Sprites da pose inicial e das barras cabendo no repositório.
2. Placa ligada mostra o caso 1.
3. Estado com fome 20 mostra o caso 2.

## 10. Critérios de liberação

- [x] Os casos de uso da seção 5 passam no computador. O caso 4 espera sprite de sono; sem ele, a pose continua a da fase.
- [ ] O KPI da seção 8 foi observado do jeito descrito, na placa.
- [x] Product SEO está `não se aplica`.
- [x] Os sprites usados estão no repositório, não só no chat. A pose usada é a da manta.

## 11. Product SEO

`não se aplica`

A tela é a da placa. Esta entrega não publica página nem imagem na web.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | O ciclo fica invisível para quem cuida |
| Corte menor | Quatro barras e uma pose parada da fase. Sem animação e sem as cinco poses de ação |
| Solução mais completa | Todos os quadros e o toque no mesmo passo misturam arte, regra e dedo |

O corte menor é a proposta. Seções 1 a 10 já estão nele.

## 13. Crítica

- O propósito é um problema: sem imagem e sem barra, a pessoa não cuida.
- A pesquisa sustenta o mascote e o tamanho da tela. Não sustenta animação nesta entrega.
- O CYD clássico segura 320×240. Não segura arte que não está no firmware.
- “Ficou fofo” seria vaidade. O KPI é apontar a barra baixa.
- O que piora: uma pose só pode parecer estático. É o corte, não um defeito escondido. Animação fica no PRD de humor.

Decisão: `encolher`.

`aprovado` em 2026-10-05. A pose da manta está no repositório e o teste nativo cobre o primeiro olhar, a fome mais curta e a fase sem sprite próprio. Não há pose de sono, então dormindo reutiliza a manta. O KPI de reconhecimento ainda não foi visto na mesa, então esse critério da seção 10 continua aberto.

## 14. Fora desta entrega

Toque, dois quadros, brincando, comendo, banho, abano contínuo, cara de culpa, doença desenhada, game over.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Tela reduzida a pose parada da fase e quatro barras. |
| 0.2 | Crítica aceita com `encolher`. Pose da manta versionada. Casos 1, 2, 3 e 5 no teste nativo. O reconhecimento na placa fica para a mesa. |

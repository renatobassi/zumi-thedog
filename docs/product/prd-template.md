# PRD — <nome curto>

| Campo | Valor |
|---|---|
| Status | `rascunho` \| `em crítica` \| `aprovado` \| `recusado` |
| Versão | 0.1 |
| Autor | |
| Última edição | |

Copie para `docs/product/prds/NNNN-slug.md`. O PRD diz **o que** a solução precisa cumprir e **para quem**. Não descreve arquivo, pino nem biblioteca. Isso fica no desenho técnico depois da aprovação.

O documento é editável. Mudou o corte, suba a versão e registre o que mudou no final.

Referência de estrutura: [PRD na PM3](https://pm3.com.br/glossario/prd-product-requirements-document/).

## 1. Propósito e escopo

Por que esta entrega existe, em um parágrafo. O que entra. O que não entra.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | |
| Produto | |
| Engenharia | |

## 3. Pesquisa

O que já sabemos de uso, de hardware e de referências — e o que ainda é premissa. Sem esta seção, o PRD não sai de `rascunho`.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| | | |

## 5. Casos de uso

Nomeie o ator e o desfecho. Um caso por situação que o critério de liberação precisa cobrir.

1. **Nome.** Dado…, quando…, então…

## 6. Fluxo

O caminho principal e o caminho de falha, em passos que uma pessoa executa na placa (ou na página, se a entrega for digital).

## 7. Requisitos

**Uso.** O que a pessoa consegue fazer e o que ela entende na tela.

**Técnicos, como restrição.** Memória, offline, touch resistivo, o que a placa não tem. Sem desenho de código.

**Suporte.** O que precisa continuar verdadeiro depois de desligar a placa, atualizar o firmware ou reler o case daqui a seis meses.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| | Na placa, no simulador ou na página | |

Um KPI que não dá para observar não entra.

## 9. Marcos

Ordem de liberação. Sem data inventada. Cada marco é demonstrável sozinho.

1.

## 10. Critérios de liberação

- [ ] Os casos de uso da seção 5 passam.
- [ ] O KPI da seção 8 foi observado do jeito descrito.
- [ ] Product SEO está `não se aplica` ou a validação em [product-seo.md](product-seo.md) está marcada.

## 11. Product SEO

`não se aplica` ou `aplica`.

Não se aplica quando a entrega não muda URL, página indexável, conteúdo público, título, mídia ou dado estruturado. Escreva a frase que justifica.

Aplica quando muda. Preencha descoberta, refinamento e validação em [product-seo.md](product-seo.md). Nem todo item do checklist entra em todo produto: marque só o que esta entrega pode quebrar.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | |
| Corte menor | |
| Solução mais completa | |

Se o corte menor cumpre o propósito, ele passa a ser a proposta. Atualize as seções 1 a 10.

## 13. Crítica

Responda como revisor, antes de pedir `aprovado`:

- O propósito é um problema ou um desejo?
- A pesquisa sustenta a funcionalidade, ou só a ilustra?
- Qual requisito técnico o CYD clássico não segura?
- Qual KPI é vaidade?
- O que piora para quem cuida do Zumi se isto entrar agora?

Decisão: `seguir` | `encolher` | `adiar` | `matar`.

`aprovado` só com `seguir` ou `encolher`, e com o corte já reescrito no corpo do PRD.

## 14. Fora desta entrega

O que a próxima conversa vai pedir e este PRD recusa.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | |

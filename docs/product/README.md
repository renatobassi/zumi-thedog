# Produto

Nenhuma feature entra em código sem um PRD `aprovado` em `docs/product/prds/`.

O PRD segue a estrutura descrita pela PM3: propósito, stakeholders, funcionalidades e o problema de cada uma, casos de uso, fluxo, requisitos, marcos, KPI e critério de liberação. Ele alinha o que será construído. O modo de construir fica na [arquitetura](../engineering/architecture.md).

Modelo: [prd-template.md](prd-template.md). Glossário de referência: [PRD — PM3](https://pm3.com.br/glossario/prd-product-requirements-document/).

## Do rascunho ao código

1. Copie o modelo. Preencha pesquisa, alternativas e a crítica.
2. Se a entrega muda página pública, o Product SEO fica `aplica` e usa [product-seo.md](product-seo.md). Se não muda, registre `não se aplica` com uma frase.
3. Status `aprovado` só depois da crítica em `seguir` ou `encolher`, com o corte reescrito no PRD.
4. `adiar` e `matar` encerram a feature. Não abrem branch de código.
5. Um PRD, uma branch, um pull request. O PRD continua editável; mudança de corte sobe a versão.

## Barra da crítica

- O propósito cabe num parágrafo e o KPI é observável.
- Cada funcionalidade nomeia o problema que resolve.
- A alternativa menor foi considerada.
- Requisito técnico respeita o CYD clássico desta fase.
- SEO não foi ignorado em silêncio: ou aplica e tem validação, ou não aplica e está escrito.

Contexto: [vision.md](vision.md). Ordem das fatias: [roadmap.md](roadmap.md). Fila: [backlog.md](backlog.md).

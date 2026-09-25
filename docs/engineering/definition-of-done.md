# Pronto quando

Uma mudança está pronta para a `main` quando todos os itens abaixo são verdade.

- Saiu de uma branch criada a partir da `main` atualizada (`git fetch` + `pull --ff-only`).
- Feature de produto tem PRD `aprovado` e o pull request aponta para ele.
- A branch foi atualizada de novo com `origin/main` e os conflitos foram resolvidos.
- O comportamento novo está coberto por teste de domínio, ou por um passo reproduzível na placa ou no simulador, escrito no PR.
- Código novo respeita as camadas em [architecture.md](architecture.md).
- Product SEO está `não se aplica` no PRD, ou a validação em [product-seo.md](../product/product-seo.md) foi marcada para o que a página mudou.
- Não há segredo, arquivo de biblioteca baixada nem arte só no chat.

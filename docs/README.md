# Como ler o Zumi

Este repositório é o case de produto e a base de engenharia do Zumi, um cachorro caramelo virtual no ESP32 CYD clássico.

Leia nesta ordem:

1. [Visão](product/vision.md) — problema, aposta e o que ficou de fora.
2. [Como especificamos](product/README.md) — PRD no formato da PM3 e a crítica que libera código.
3. [Product SEO](product/product-seo.md) — checklist de descoberta, refinamento e validação quando a entrega tem superfície pública.
4. [Arquitetura](engineering/architecture.md) — por que o firmware é separado em camadas.
5. [Fluxo](engineering/workflow.md) — branch a partir da `main` atualizada e reconciliação antes do merge.

PRDs aprovados ficam em `product/prds/`. O esqueleto de código fica em `firmware/` e ainda não implementa regra de jogo.

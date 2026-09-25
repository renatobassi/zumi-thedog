# Fluxo de engenharia

A `main` é a linha estável. Trabalho acontece em branch curta, com pull request. Não se commita direto na `main`.

## Antes de qualquer modificação

```bash
git fetch origin
git checkout main
git pull --ff-only origin main
git checkout -b <tipo>/<slug>
```

Tipos: `feat`, `fix`, `docs`, `chore`.

O slug descreve o resultado (`feat/pet-hunger-decay`), não o ticket genérico (`feat/update`).

Se a `main` local divergiu e o `pull --ff-only` falhar, pare e resolva com a pessoa do repositório. Não faça reset destrutivo por conta própria.

## Durante o trabalho

- A branch sai da `main` atualizada naquele momento.
- Um PRD aprovado por feature de produto. Correção pequena de bug pode referenciar o PRD da feature que quebrou, sem PRD novo.
- Commits pequenos, mensagem no imperativo, dizendo o porquê.

## Antes de abrir ou atualizar o pull request

Atualize a branch com a `main` e resolva conflitos no seu ambiente, antes de pedir merge.

Branch ainda não enviada ao remoto:

```bash
git fetch origin
git rebase origin/main
```

Branch já publicada:

```bash
git fetch origin
git merge origin/main
```

Não use `push --force` na `main`. Não reescreva história de branch publicada sem pedido explícito. Conflito se resolve no conteúdo: leia os dois lados, preserve o comportamento das duas mudanças quando as duas ainda forem válidas, e rode o teste do que foi tocado.

O pull request aponta para `main`, descreve o PRD e os critérios de aceite. Merge só com o branch atualizado em relação à `main` e sem conflito.

## O que não fazer

- Editar na `main`.
- Abrir a branch a partir de outra feature não mergeada.
- Mandar a branch para a `main` com conflito ou desatualizada.
- Juntar feature sem PRD no mesmo pull request de documentação do processo.

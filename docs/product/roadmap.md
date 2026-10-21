# Roadmap

O Zumi da descoberta é um cachorro caramelo que vive na placa. Este mapa ordena o que vira PRD agora e o que fica parado até a visão mudar.

A descoberta está no [chat compartilhado](https://agent.adapta.one/shared-chat/01a0c706-c54c-731d-81a3-0d01ff7a4667). A [visão](vision.md) já recusou voz, microfone, alto-falante, ESP32-S3, aplicativo e rede. O chat não substitui estes PRDs.

O [Hello na placa](prds/0000-hello-na-placa.md), o [Ciclo de cuidado](prds/0001-ciclo-de-cuidado.md), o [Estado na placa](prds/0002-estado-na-placa.md), o [Zumi na tela](prds/0003-zumi-na-tela.md), o [Cuidado pelo toque](prds/0004-cuidado-pelo-toque.md) e o [Crescimento](prds/0005-crescimento.md) estão `aprovado`. O Hello já está na placa. O ciclo passa no computador e o firmware grava esse estado na flash. O corte da USB do 0002 ainda não foi visto na mesa. A [identidade visual](identidade-visual.md) já veste a tela: cômodo, faixa de cuidados e o adulto sentado da folha, pixel a pixel. A idade ligada muda a fase no estado; sprite próprio por fase ainda falta. Reconhecer o caramelo e acertar os alvos na mesa ainda são os passos do 0003 e do 0004. Próximo: a [Doença e a rua](prds/0007-doenca-e-a-rua.md). Nos outros, a crítica recomenda a decisão. Código só começa no arquivo que passar a `aprovado`, um PRD por branch.

## Agora — o bichinho na mesa

A placa fica ligada na tomada. O dono cuida pelo toque e, horas depois, vê outro estado. Desligar e ligar não apaga o Zumi. O tempo desligado não conta: o CYD clássico desta compra não tem relógio que sobreviva sem energia.

Ordem, cada marco demonstrável sozinho:

1. ~~[Hello na placa](prds/0000-hello-na-placa.md)~~ — feito em 2026-10-05: o firmware do repositório grava no CYD e a tela mostra “Ola!”. Sem Zumi.
2. ~~[Ciclo de cuidado](prds/0001-ciclo-de-cuidado.md)~~ — feito em 2026-10-05: barras, sono e quatro ações passam no computador. A placa ainda mostra o Hello.
3. ~~[Estado na placa](prds/0002-estado-na-placa.md)~~ — feito em 2026-10-05 no computador: gravar, ler e nascer de novo passam com armazenamento falso. O tempo desligado não mexe nas barras. O firmware da placa grava o ciclo na flash e o serial mostra os números; confirmar desligando a USB ainda é o passo na mesa. A tela continua o Hello.
4. ~~[Zumi na tela](prds/0003-zumi-na-tela.md)~~ — feito em 2026-10-05 no computador: as quatro barras com nome passam no teste. Em 2026-10-06 a tela ganhou o cômodo e a paleta da [identidade visual](identidade-visual.md); em 2026-10-20 o sprite virou o adulto sentado da folha, bloco a bloco. Sem pose de sono, dormindo reutiliza esse adulto. As outras fases da folha ficam para o crescimento. Reconhecer o caramelo na placa ainda é o passo na mesa.
5. ~~[Cuidado pelo toque](prds/0004-cuidado-pelo-toque.md)~~ — feito em 2026-10-05 no computador: os quatro alvos disparam o ciclo, a recusa aparece e o toque fora não muda nada. Dormir vira Acordar. Segurar o dedo não repete. A faixa de cuidados da identidade visual é o alvo. Acertar isso na placa ainda é o passo na mesa.
6. ~~[Crescimento](prds/0005-crescimento.md)~~ — feito em 2026-10-20 no computador: idade ligada, limiares 24/72/168 e registro v2 passam no teste. Desligar não soma idade. Sem sprite de filhote ou adulto pleno, a tela continua no adulto sentado.
7. [Doença e a rua](prds/0007-doenca-e-a-rua.md) — abandono longo termina em “voltou pra rua”, com adoção de novo.
8. [Humor e poses](prds/0006-humor-e-poses.md) — a pose acompanha o cuidado e a ação.

O 0006 vem depois do 0007 de propósito: a regra de abandono existe antes da animação. Na tela, a doença pode aparecer como estado escrito até a pose existir.

## Parado — especificado para não entrar no código

A descoberta pediu estas fatias. A crítica delas é `adiar`. Não abrem branch.

- [Cara de culpa](prds/0008-cara-de-culpa.md) — personalidade solta, sem problema de cuidado.
- [Susto com barulho](prds/0009-susto-com-barulho.md) — microfone no CYD clássico.
- [Voz e latido](prds/0010-voz-e-latido.md) — “passear” falado e alto-falante.
- [Presença fora da placa](prds/0011-presenca-fora-da-placa.md) — Wi-Fi, Telegram, aplicativo.

## O que destravaria o que está parado

- Culpa: quando o ciclo 0001–0007 já estiver na mão de quem cuida, e ainda assim faltar personalidade observável.
- Susto, voz e latido: um PRD novo, com a placa que segura o hardware. No clássico, a visão mantém a recusa.
- Fora da placa: um problema real de quem não está olhando a mesa. A visão de hoje é o contrário: o Zumi existe sem conta e sem rede.

Fila e dependências: [backlog.md](backlog.md).

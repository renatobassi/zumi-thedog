# Roadmap

O Zumi da descoberta é um cachorro caramelo que vive na placa. Este mapa ordena o que vira PRD agora e o que fica parado até a visão mudar.

A descoberta está no [chat compartilhado](https://agent.adapta.one/shared-chat/01a0c706-c54c-731d-81a3-0d01ff7a4667). A [visão](vision.md) já recusou voz, microfone, alto-falante, ESP32-S3, aplicativo e rede. O chat não substitui estes PRDs.

Nenhum PRD está `aprovado`. A crítica recomenda a decisão. Código só começa no arquivo que passar a `aprovado`, um PRD por branch.

## Agora — o bichinho na mesa

A placa fica ligada na tomada. O dono cuida pelo toque e, horas depois, vê outro estado. Desligar e ligar não apaga o Zumi. O tempo desligado não conta: o CYD clássico desta compra não tem relógio que sobreviva sem energia.

Ordem, cada marco demonstrável sozinho:

1. [Hello na placa](prds/0000-hello-na-placa.md) — computador reconhece o CYD, grava o firmware e a tela mostra um cumprimento. Sem Zumi.
2. [Ciclo de cuidado](prds/0001-ciclo-de-cuidado.md) — barras, sono e quatro ações, testáveis no computador.
3. [Estado na placa](prds/0002-estado-na-placa.md) — o mesmo ciclo continua depois de desligar.
4. [Zumi na tela](prds/0003-zumi-na-tela.md) — fase e barras legíveis. Sem os sprites no repositório, este PRD não aprova.
5. [Cuidado pelo toque](prds/0004-cuidado-pelo-toque.md) — comer, brincar, dormir e banho na tela.
6. [Crescimento](prds/0005-crescimento.md) — manta, filhote, adulto sentado, adulto pleno.
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

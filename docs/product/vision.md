# Zumi — visão de produto

## Para quem

Para quem quer um bichinho na mesa, sem conta, sem aplicativo e sem a placa depender de um computador ligado. O primeiro usuário é quem está montando o projeto: cuida do Zumi pelo toque na tela e percebe, horas depois, que o estado mudou.

## Problema

Um assistente de voz no estilo Jarvis, no hardware que cabe no orçamento, empurra transcrição e resposta para a nuvem e não tem fim claro. O ESP32 CYD clássico (ESP32-2432S028R, TFT 2,8" 320×240, touch resistivo) tem tela e toque, e não tem fôlego para reconhecer fala. O produto que esse hardware sustenta é outro: um tamagotchi offline, com personalidade de vira-lata caramelo.

## Aposta

O Zumi vive na placa. O dono alimenta, brinca, manda dormir e dá banho. Quatro barras — fome, energia, diversão e higiene — descem com o tempo. O humor e a fase acompanham o cuidado: recém-adotado na manta, filhote, adulto sentado, adulto pleno. Feliz, ele abana o rabo. Faminto, doente ou dormindo, a pose muda. Abandono longo demais e ele “volta pra rua”. O estado fica gravado na própria placa.

## O que esta visão recusa

- Assistente de voz e a palavra “passear” reconhecida no CYD clássico.
- Microfone, alto-falante e migração para ESP32-S3 até um PRD próprio.
- Aplicativo, Telegram, Wi-Fi ou API para o bichinho existir.
- Tratar o chat de descoberta como especificação. Cada fatia entra por um PRD.

## De onde veio

A descoberta está no [chat compartilhado](https://agent.adapta.one/shared-chat/01a0c706-c54c-731d-81a3-0d01ff7a4667): comparação de hardware, troca do dragão pelo caramelo, poses, lista de compra e a decisão de ficar no CYD clássico. A arte ainda não está versionada aqui. Sem sprite no repositório, renderizar o Zumi não é uma feature pronta para código.

## Como o case se desdobra

Cada feature vira um PRD editável, com propósito, casos de uso, requisitos, KPI e critério de liberação. O desenho de implementação fica na arquitetura, não no PRD. Quando a entrega muda uma página pública — case, documentação publicada, landing — o checklist de Product SEO entra no refinamento e na validação. Firmware que só roda na placa marca SEO como não aplicável e diz por quê.

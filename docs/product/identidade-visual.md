# Identidade visual

A tela do Zumi usa a arte da descoberta: o vira-lata caramelo da [folha de sprites](https://agent.adapta.one/shared-chat/01a0c706-c54c-731d-81a3-0d01ff7a4667) e a paleta do [preview na resolução do CYD](https://skip-artifacts-snapshots.application.production.adapta.tools/user_3CDVTYlI0xg3W0mEhiEbBi4XVRf/4dsrp5jm6urgh3kgf3vuim4zza/revisions/3cb774c3-6168-4ac4-9cb6-53ce358664c7/index.html). O pixel que a placa desenha é o que está no repositório.

Esta entrega veste o que os PRDs 0003 e 0004 já mostram. Não adiciona pose, animação nem cuidado novo.

## Paleta

| Token | Hex | RGB565 | Onde aparece |
|---|---|---|---|
| Preto | `#000000` | `0x0000` | Fundo da tela |
| Caramelo | `#c68a4b` | `0xC449` | Pelo e preenchimento da barra |
| Creme | `#f5e6c8` | `0xF739` | Focinho, peito e rótulo do cuidado |
| Orelha | `#5a3a1a` | `0x59C3` | Sombra do pelo e contorno |
| Tinta | `#3b220c` | `0x3901` | Contorno do sprite e miolo da pílula |
| Ouro | `#e08020` | `0xE404` | Borda da pílula, borda da barra e aviso |
| Olho | `#000000` | `0x0000` | Olho e nariz |

O ouro é o das etiquetas da folha. O caramelo, o creme, a orelha e a tinta são os do preview. A fonte da placa não tem acento: Diversão continua Diversao.

## Pose que entra agora

A tela mostra o adulto sentado da folha: orelhas caídas, focinho e peito creme, olhos e nariz pretos, rabo ao lado. É a única pose versionada até o crescimento. Dormindo continua nela, enquanto não houver pose de sono.

O desenho versionado está em `firmware/assets/sprites/build_manta.py` e o PNG ao lado. O cabeçalho que o firmware inclui sai desse script. No computador, `pio run -e preview` abre essa tela em 320×240.

## Tela 320×240

A referência fechada está em [referencias/tela-proxima-do-adapta.png](referencias/tela-proxima-do-adapta.png). Parede azul, chão de madeira, tapete, janela e o nome ZUMI. O cão fica no centro, com as patas no tapete. Os quatro cuidados ficam numa faixa embaixo, no tamanho do toque: ícone, nome e a barra daquele cuidado. A ordem das barras é Fome em Comer, Energia em Brincar, Diversao em Dormir e Higiene em Banho. A barra baixa é mais curta. O aviso da ação sai em ouro, acima da faixa, e some sozinho.

## O que a folha mostra e esta tela ainda não desenha

| Na folha | Quando entra |
|---|---|
| Filhote na manta, filhote pequeno, adulto pleno | [Crescimento](prds/0005-crescimento.md), quando estiver `aprovado` |
| Feliz, com fome, dormindo, comendo, brincando, banho | [Humor e poses](prds/0006-humor-e-poses.md), depois da regra de abandono |
| Doente | [Doença e a rua](prds/0007-doenca-e-a-rua.md) |
| Cara de culpa | [Cara de culpa](prds/0008-cara-de-culpa.md) está `adiar` |
| Som, latido, relógio, nível | A visão recusa alto-falante e rede. O preview do chat não libera isso |

Até o sprite da fase existir no repositório, a tela continua no adulto sentado. Dormindo também, enquanto não houver pose de sono versionada.

## Product SEO

`não se aplica`

A identidade muda a tela da placa e este documento. Não muda página pública.

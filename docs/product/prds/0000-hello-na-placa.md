# PRD — Hello na placa

| Campo | Valor |
|---|---|
| Status | `em crítica` |
| Versão | 0.1 |
| Autor | Produto |
| Última edição | 2026-09-25 |

## 1. Propósito e escopo

Antes do Zumi, a placa precisa provar que o computador grava nela e que a tela acende. Esta entrega é o Hello World no CYD clássico.

Entra: o computador reconhecer a placa, gravar um firmware deste repositório e mostrar um cumprimento legível na tela.

Não entra: Zumi, barras, toque, sprite, som, rede.

## 2. Stakeholders

| Quem | O que precisa deste PRD |
|---|---|
| Pessoa que usa a placa | Saber que a placa comprada funciona antes de cuidar do bichinho |
| Produto | O primeiro marco da descoberta, sem misturar com a regra do pet |
| Engenharia | Um alvo único: texto na tela do clássico, pelo caminho que o repositório já fixou |

## 3. Pesquisa

No fim do [chat de descoberta](https://agent.adapta.one/shared-chat/01a0c706-c54c-731d-81a3-0d01ff7a4667) a placa tinha chegado e o passo seguinte era configurar o computador e rodar um teste de tela, antes do Zumi. O chat citou cabo que só carrega, driver da ponte USB e o botão BOOT quando a gravação não começa. Isso é experiência de quem usa o CYD, não medida nova.

A arquitetura do repositório já escolheu como o firmware é construído. Este PRD não troca esse caminho nem pede outra IDE. O chat sugeriu um fluxo de IDE solta; aqui o cumprimento sai do próprio repositório.

A tela é 320×240 do ESP32-2432S028R. Não houve gravação registrada neste case ainda.

## 4. Funcionalidades e o problema que cada uma resolve

| Funcionalidade | Problema que resolve | Fora desta linha |
|---|---|---|
| Placa visível no computador | Sem porta, não há o que gravar | Instalar um ecossistema paralelo ao repositório |
| Gravação que termina | “Connecting…” eterno não é uma placa pronta | Zumi na mesma gravação |
| Cumprimento na tela | Tela apagada não distingue cabo, driver e display | Barra, pose, toque |

## 5. Casos de uso

1. **Placa na porta.** Dado o CYD clássico, um cabo que transmite dados e o driver da ponte USB instalado, quando a pessoa conecta, então o computador mostra uma porta serial da placa.
2. **Hello.** Dado a porta visível, quando a pessoa grava o firmware desta entrega a partir do repositório, então a gravação termina e a tela mostra um cumprimento fixo, legível, em 320×240.
3. **Cabo mudo.** Dado um cabo que só fornece energia, quando a pessoa conecta, então nenhuma porta serial aparece. O passo seguinte escrito no case é trocar o cabo, não mudar o produto.
4. **Gravação que não começa.** Dado a porta visível e a gravação parada em conexão, quando a pessoa segura BOOT no início da gravação, então o envio segue e o caso 2 volta a valer.
5. **Ainda não é o pet.** Dado o firmware desta entrega gravado, quando a pessoa olha a tela, então não há Zumi, barra nem alvo de cuidado.

## 6. Fluxo

Caminho principal: instalar o que o repositório pede para falar com o clássico, conectar com cabo de dados, ver a porta, gravar, ler o cumprimento na tela.

Caminho de falha: sem porta, trocar o cabo e conferir o driver. Com porta e sem gravação, segurar BOOT e tentar de novo. Tela apagada depois de uma gravação que disse ter acabado não conta como Hello: a entrega não libera.

## 7. Requisitos

**Uso.** O cumprimento cabe na tela e se lê na mesa, sem lupa. Uma pessoa que não escreveu o firmware consegue repetir os passos. O texto é estável: não pisca a ponto de não dar para ler, não depende de toque.

**Técnicos, como restrição.** Placa ESP32-2432S028R, tela 320×240, offline. A gravação usa o fluxo já decidido no repositório. Esta entrega não acrescenta microfone, alto-falante, cartão nem rede. Não desenha o pet.

**Suporte.** O mesmo firmware, gravado de novo, mostra o mesmo cumprimento. Uma gravação posterior do Zumi substitui esta tela; este PRD não promete que o Hello continue depois disso.

## 8. KPIs

| Sinal | Como observar | Meta desta entrega |
|---|---|---|
| Porta | Gerenciador de dispositivos, ou o equivalente, com a placa conectada | Uma porta serial da placa aparece no caso 1 e não aparece no caso 3 |
| Tela | Olho na placa, depois da gravação | O cumprimento do caso 2 está legível. O caso 5 continua verdadeiro |

## 9. Marcos

1. Passos de cabo, driver e BOOT escritos junto do case, para quem está com a placa na mão.
2. Gravação a partir do repositório termina na placa de quem cuida.
3. A tela mostra o cumprimento e nada do pet.

## 10. Critérios de liberação

- [ ] Os casos de uso da seção 5 passam.
- [ ] O KPI da seção 8 foi observado do jeito descrito, na placa.
- [ ] Product SEO está `não se aplica`.

## 11. Product SEO

`não se aplica`

A entrega é firmware e tela da placa. Não muda página, URL, título nem mídia pública.

## 12. Alternativas

| Alternativa | Por que não é esta entrega |
|---|---|
| Não fazer | O primeiro Zumi na tela mistura placa morta com regra errada |
| Corte menor | Só o cumprimento, sem gráfico de teste e sem toque. É esta entrega |
| Solução mais completa | Já desenhar o caramelo no primeiro envio junta arte, pinos e “a placa funciona?” |

O corte menor é a proposta.

## 13. Crítica

- O propósito é um problema: sem Hello, ninguém sabe se o próximo defeito é a placa, o cabo ou o pet.
- A pesquisa sustenta cabo, driver e BOOT. Não sustenta escolher outra IDE além da do repositório.
- O CYD clássico segura texto na tela. Não precisa de áudio nem de rede para este marco.
- “Ambiente configurado” sem frase na tela seria vaidade. O KPI é a porta e o cumprimento lido.
- O que piora: um passo a mais antes do bichinho. É o passo que evita gravar o Zumi numa placa que ainda não mostrou nada.

Decisão: `seguir`.

## 14. Fora desta entrega

Ciclo de cuidado, persistência, sprite, toque, fase, doença, humor.

## Histórico

| Versão | O que mudou |
|---|---|
| 0.1 | Primeiro marco: placa reconhecida e cumprimento na tela. |

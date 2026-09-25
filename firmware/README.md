# Firmware

Esqueleto do Zumi para o ESP32 CYD clássico. A regra do pet ainda não está aqui.

- `src/domain` — contrato do estado. Testável sem a placa.
- `src/ui` — toque entra, ação sai. Não mexe em barra.
- `src/hal` — pinos do ESP32-2432S028R.
- `src/persistence` — contrato de gravar o snapshot.
- `src/main.cpp` — sobe um recém-nascido em memória e não desenha.

```bash
pio test -e native
```

O alvo `cyd` compila para a placa quando o PlatformIO estiver instalado. Gravar firmware que mostre o Zumi depende de um PRD aprovado.

Arquitetura: [docs/engineering/architecture.md](../docs/engineering/architecture.md).

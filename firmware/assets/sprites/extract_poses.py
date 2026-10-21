# Amostra da folha de identidade as poses de humor (PRD 0006).
# Uso único: gera poses_grids.py, que fica versionado. build_poses.py lê esse arquivo.
# A folha é docs/product/referencias/folha-zumi.jpg (1024x1024).
#
# Cada pose: caixa na folha (esquerda, topo, direita, base) e largura/altura máximas da grade.
# O fundo é o preto conectado às bordas da caixa; olho e nariz pretos dentro do cão ficam como K.

from collections import deque
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[3]
SHEET = ROOT / "docs" / "product" / "referencias" / "folha-zumi.jpg"

# Paleta de docs/product/identidade-visual.md, mais vermelho para língua e termômetro.
PALETTE = {
    "O": (59, 34, 12),
    "D": (90, 58, 26),
    "B": (170, 96, 40),
    "C": (198, 138, 75),
    "H": (224, 160, 80),
    "L": (245, 230, 200),
    "W": (255, 255, 255),
    "K": (0, 0, 0),
    "R": (214, 76, 84),
}

# nome: (caixa na folha, largura máx., altura máx.)
POSES = {
    "FELIZ": ((750, 190, 998, 486), 66, 81),
    "FOME": ((262, 690, 486, 898), 70, 66),
    "SONO": ((498, 660, 742, 900), 78, 78),
    "DOENTE": ((790, 685, 998, 898), 66, 66),
}

BG_LIMIT = 46  # soma máxima de brilho (r+g+b)/3 para contar como fundo


def is_dark(px):
    return (px[0] + px[1] + px[2]) / 3 < BG_LIMIT


def nearest(color):
    best = None
    best_d = None
    for key, ref in PALETTE.items():
        d = sum((a - b) ** 2 for a, b in zip(color, ref))
        if best_d is None or d < best_d:
            best, best_d = key, d
    return best


def background_mask(img):
    w, h = img.size
    px = img.load()
    seen = [[False] * w for _ in range(h)]
    queue = deque()
    for x in range(w):
        for y in (0, h - 1):
            if is_dark(px[x, y]):
                queue.append((x, y))
                seen[y][x] = True
    for y in range(h):
        for x in (0, w - 1):
            if is_dark(px[x, y]) and not seen[y][x]:
                queue.append((x, y))
                seen[y][x] = True
    while queue:
        x, y = queue.popleft()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            nx, ny = x + dx, y + dy
            if 0 <= nx < w and 0 <= ny < h and not seen[ny][nx] and is_dark(px[nx, ny]):
                seen[ny][nx] = True
                queue.append((nx, ny))
    return seen


def sample(name, box, max_w, max_h):
    img = Image.open(SHEET).convert("RGB").crop(box)
    w, h = img.size
    bg = background_mask(img)
    px = img.load()

    # caixa do cão
    xs = [x for y in range(h) for x in range(w) if not bg[y][x]]
    ys = [y for y in range(h) for x in range(w) if not bg[y][x]]
    left, right = min(xs), max(xs) + 1
    top, bottom = min(ys), max(ys) + 1
    bw, bh = right - left, bottom - top

    cell = max(bw / max_w, bh / max_h)
    cols = int(round(bw / cell))
    rows = int(round(bh / cell))

    grid = []
    for r in range(rows):
        row = ""
        y0 = top + int(r * cell)
        y1 = top + max(int((r + 1) * cell), int(r * cell) + 1)
        for c in range(cols):
            x0 = left + int(c * cell)
            x1 = left + max(int((c + 1) * cell), int(c * cell) + 1)
            fg = []
            total = 0
            for y in range(y0, min(y1, h)):
                for x in range(x0, min(x1, w)):
                    total += 1
                    if not bg[y][x]:
                        fg.append(px[x, y])
            if total == 0 or len(fg) * 2 < total:
                row += "."
                continue
            mean = tuple(sum(p[i] for p in fg) // len(fg) for i in range(3))
            row += nearest(mean)
        grid.append(row)
    return grid


def main():
    lines = [
        "# Gerado por extract_poses.py a partir da folha. Versionado; build_poses.py lê este arquivo.",
        "",
        "GRIDS = {",
    ]
    for name, (box, mw, mh) in POSES.items():
        grid = sample(name, box, mw, mh)
        lines.append('    "%s": [' % name)
        for row in grid:
            lines.append('        "%s",' % row)
        lines.append("    ],")
        print(name, len(grid[0]), "x", len(grid))
    lines.append("}")
    (Path(__file__).with_name("poses_grids.py")).write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")


if __name__ == "__main__":
    main()

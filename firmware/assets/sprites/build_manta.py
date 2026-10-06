# Pose parada da manta. O texto abaixo é o pixel versionado.
# Gera o PNG (para olhar) e o cabeçalho RGB565 que o firmware desenha.
# Chave de transparência: magenta 0xF81F.

import struct
import zlib
from pathlib import Path

WIDTH = 40

ROWS = [
    "........................................",
    ".............OOOOOOOO...................",
    "...........OOCCCCCCCCOO.................",
    "..........OCCCCLCCLCCCCO................",
    ".........OCCCCCLCCCLCCCCO...............",
    "........OOCCCLLCCCCLLCCCOO..............",
    ".......OCCCCCWWCCCCWWCCCCCO.............",
    ".......OCCCCOOOCCCCCOOCCCCO.............",
    ".......OCCCCOEECCCCEEOCCCCO.............",
    ".......OCCCCCWWCCCCWWCCCCCO.............",
    "........OCCCCCCCNNCCCCCCCO..............",
    ".........OCCCCCNNNNCCCCCO...............",
    "..........OOCCCCNNCCCCOO................",
    "............OOOOOOOOOO..................",
    "..........OOWWWWWWWWWWOO................",
    "........OOWWWWWWWWWWWWWWWO..............",
    "......OOWWWWWWWWWWWWWWWWWWWO............",
    ".....OWWWWWWWWCCCCCCWWWWWWWWO...........",
    ".....OWWWWWWCCCCCCCCCCWWWWWWO...........",
    ".....OWWWWWCCCCCCCCCCCCWWWWWWO..........",
    ".....OWWWWCCCLLLLLLLCCCCWWWWWO..........",
    ".....OWWWWCCCCCCCCCCCCCCWWWWWO..........",
    ".....OWWWWWWCCCCCCCCCCWWWWWWWO..........",
    ".....OWWWWWWWWCCCCCCWWWWWWWWWO..........",
    "......OOWWWWWWWWWWWWWWWWWWWO............",
    "........OOWWWWWWWWWWWWWWWO..............",
    "..........OOOOOOOOOOOOOO................",
    "........................................",
]

PALETTE = {
    ".": None,
    "O": (92, 52, 32),
    "C": (214, 150, 82),
    "L": (242, 198, 142),
    "E": (42, 26, 18),
    "N": (168, 92, 78),
    "W": (236, 230, 216),
}

KEY = (255, 0, 255)


def rgb565(color):
    red, green, blue = color
    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | ((blue & 0xF8) >> 3)


def pixels():
    if any(len(row) != WIDTH for row in ROWS):
        raise SystemExit("linha com largura diferente de %d" % WIDTH)
    grid = []
    for row in ROWS:
        grid.append([PALETTE[ch] for ch in row])
    return grid


def write_png(path, grid):
    height = len(grid)
    width = len(grid[0])

    def chunk(tag, data):
        return struct.pack(">I", len(data)) + tag + data + struct.pack(">I", zlib.crc32(tag + data) & 0xFFFFFFFF)

    raw = bytearray()
    for row in grid:
        raw.append(0)
        for color in row:
            shown = color if color is not None else (0, 0, 0)
            raw.extend(shown)
    png = b"\x89PNG\r\n\x1a\n"
    png += chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0))
    png += chunk(b"IDAT", zlib.compress(bytes(raw), 9))
    png += chunk(b"IEND", b"")
    path.write_bytes(png)


def write_header(path, grid):
    height = len(grid)
    width = len(grid[0])
    values = []
    for row in grid:
        for color in row:
            values.append(rgb565(color if color is not None else KEY))
    lines = []
    for start in range(0, len(values), 12):
        chunk = ", ".join("0x%04X" % value for value in values[start : start + 12])
        lines.append("    " + chunk + ",")
    text = (
        "#pragma once\n\n"
        "#include <stdint.h>\n\n"
        "// Gerado por firmware/assets/sprites/build_manta.py. Não edite à mão.\n"
        "static const int kMantaWidth = %d;\n"
        "static const int kMantaHeight = %d;\n"
        "static const uint16_t kMantaPixels[%d] = {\n%s\n};\n"
        % (width, height, len(values), "\n".join(lines))
    )
    path.write_text(text, encoding="utf-8", newline="\n")


def main():
    grid = pixels()
    root = Path(__file__).resolve().parents[2]
    write_png(Path(__file__).with_name("manta.png"), grid)
    write_header(root / "src" / "ui" / "manta_pixels.hpp", grid)


if __name__ == "__main__":
    main()

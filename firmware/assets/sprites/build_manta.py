# Pose sentada do adulto, a que a tela mostra até o crescimento ter sprite próprio.
# O texto abaixo é o pixel versionado. Paleta: docs/product/identidade-visual.md
# Gera o PNG (para olhar) e o cabeçalho RGB565 que o firmware desenha.
# Chave de transparência: magenta 0xF81F.

import struct
import zlib
from pathlib import Path

WIDTH = 38

ROWS = [
    "....................O.ODD.............",
    "..................BDDODBDD............",
    ".............DBCBBBBCCBBDDDD..........",
    "........DBBODBCCBCCCBBBDDDDDDO........",
    ".......BBCBBBCCCCCCCCCDDDDDDDDD.......",
    "......DBBCCCCCCCCCCCCCBOODDDDDD.......",
    ".....BBBCCCCCCCCCCCCCCCDOODDDDDD......",
    "....BBCCCCBCCCCCCCCCCCCBBDDDDDDDO.....",
    "....BBBCBBDBCCCCCCCCCCCCBDODDDDDDD....",
    "..DBBBBBBBOBCCCCCCCCCCCCCBODDDDDDD....",
    "..DBBBBBBDOBCCCCCCCCCCCBCBDODDDDDD....",
    ".BBBBBBBB.BCCCCCCCCHCCCKKBB.DDDDDD....",
    "BBBBBBBBB.CCCD.BCCCLCCCKKDBODDDDDD....",
    "BBBBBBBBB.CCCKKKCCCCCCB.KDBDODDDDD....",
    "BBBBBBBBDOCCB.KKCHLLLLLLDCCC.DDDO.....",
    "BBBBBBBBODCCBOKOLLLO.KDLLHCC.ODDO.....",
    ".BBBBBBBOBCCCBBHLLCKKKKLLLHC..D.......",
    ".BBBBBBB.BCCCCCLLLCKKKKLLLLC..........",
    ".BBBBBBDDCCCCCLLLLLBOKCLLLLC..........",
    "..DBBBB.BCCCCHLLLLLLHDLLDCLB..........",
    "........BCCCCHLLDLLCODDOCLH...........",
    ".........BCCCCHLLBOOHLBLLHB...........",
    "..........DBCCCHLLLLLLLLC.............",
    "..........DBBBCCHLLLLLHBBD............",
    ".........DBBBBBBBCCCCCBDBD............",
    ".........BBBBBBCCCCCCCBBBBO...........",
    ".........BCCCCHHHHHHLLBCCBB...........",
    "........DCCCCHLLLLLLLLCCCCB.......LC..",
    "........BCCCHLLLLLLLLLLCCCBD......HLH.",
    "........BCCCHLLLLLLLLLLCCCCB......CLH.",
    ".......BBCCCHLLLLLLLLLHCCCCC......BHC.",
    "......DBBCCCHHLLLLLLLLHCCCCC.....DBCB.",
    ".......BBCCCCHLLLLLLLLCCCCBC.....BCCB.",
    "......BBBBCCCCHLLLLLLCCCCBBBB...BBCBD.",
    ".....BBBBBCCCCCLLLLLLCCCCBBBB...BBBB..",
    ".....DBBBDCCCCCLLLLLLCCCCBBCCBDDBBBBDD",
    "....BBCCBDCCCCBCLLLLHBCCCBDCCCC.BBBDBB",
    "....BCCCBOCCCCCBLLLHBCCCCBDCCCC.BBBBCB",
    "...BCCCCBOCCCCCDLLLCBCCCCBDCCCCCDDBCBB",
    "...BCCCCBOCCCCCOHLLBDCCCCBDCCCCCDDBCB.",
    "...BCCCCBOBCCCCOHHHBBCCCBBBCCCCCDDBD..",
    "...BCCCCBDBCCCCOHHHBDCCCDDBCCCCB..D...",
    "...BBCCCBBOBCCC.CCCDDCCCDDBCCCCB......",
    "...DBBBCBB.CCCCOBBBDDCCCDDBBBBBD......",
    "....DDBBBB.CCCCOBBDODCCC.DBBBBD.......",
    "...BBCCCBB.CHLLH.DDBHLLH.DBBCCCBD.....",
    "...BCCCBCB.HLLLL...CLLLLCDBCBCBCD.....",
    "...BBBBBBB.LHHHL...CHHHLBOBCBCDB......",
    "...........LBCDB....CBBB..............",
]

PALETTE = {
    ".": None,
    "O": (59, 34, 12),
    "D": (112, 64, 28),
    "B": (170, 96, 40),
    "C": (198, 138, 75),
    "H": (224, 160, 80),
    "L": (244, 214, 170),
    "K": (0, 0, 0),
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

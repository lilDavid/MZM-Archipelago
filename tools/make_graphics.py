#!/usr/bin/env python3

import itertools
from pathlib import Path
from PIL import Image
import sys


# This script converts a PNG image into the uncompressed 4bpp indexed format
# the GBA uses. To do that, it creates a .gfx file that contains the tile data
# and a .pal file that contains the palette.
#
# The image is converted into 8x8 pixel tiles, which are then stored in a 1D
# array format in row major order, as in the simplified example here:
#
# 00000000 44444444
# 11111111 55555555
# 22222222 66666666
# 33333333 77777777
#
# 88888888 CCCCCCCC
# 99999999 DDDDDDDD
# AAAAAAAA EEEEEEEE
# BBBBBBBB FFFFFFFF


def pixels_to_tiles(pixels: int):
    if pixels % 8 != 0:
        raise ValueError(f"Converting {pixels}px into 8px tiles")
    return pixels // 8


def gba_color(rgb_or_rgba: list[int]):
    r, g, b, *_ = map(lambda c: c >> 3, rgb_or_rgba)
    return r | g << 5 | b << 10


# https://docs.python.org/3.11/library/itertools.html
def batches(iterable, n):
    if n < 1:
        raise ValueError
    it = iter(iterable)
    while batch := tuple(itertools.islice(it, n)):
        yield batch


def main():
    in_path = Path(sys.argv[1]).with_suffix('.png')
    out_path = Path("data/rando", in_path.name)
    gfx_path = out_path.with_suffix(".gfx")
    pal_path = out_path.with_suffix(".pal")

    source_image = Image.open(in_path)

    if source_image.palette is None:
        raise ValueError(f"Image is not in indexed color format")
    max_color = max(source_image.palette.colors.values())
    if max_color >= 16:
        raise ValueError(f"Image has {max_color + 1} colors")

    width, height = map(pixels_to_tiles, source_image.size)
    pixels = []
    for row in range(height):
        for column in range(width):
            for y in range(8):
                for x in range(8):
                    color = source_image.getpixel((8 * column + x, 8 * row + y))
                    pixels.append(color)

    palette = map(gba_color, source_image.palette.colors.keys())

    with open(gfx_path, 'wb') as gfx:
        gfx.write(bytes(map(lambda p: p[1] << 4 | p[0], batches(pixels, 2))))

    with open(pal_path, 'wb') as pal:
        pal.write(b"".join(color.to_bytes(2, "little") for color in palette))


if __name__ == '__main__':
    main()

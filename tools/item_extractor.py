import itertools
from pathlib import Path
import struct
from typing import Iterable, Tuple


data = Path("data")
sprite_data = data / "sprites"
rando_data = data / "rando"


# Direct implementation of https://problemkaputt.de/gbatek-lz-decompression-functions.htm
# Taking only the typ = 0x10 path
def lzss_decompress(compressed: bytes):
    src = 0
    if compressed.startswith(b"LZ77") or compressed.startswith(b"CMPR"):
        src += 4
    typ = compressed[src]
    if typ != 0x10:
        raise ValueError("Data not in LZSS format")
    decompressed = bytearray(int.from_bytes(compressed[src:src+4], "little") // 0x100)
    src += 4
    dst = 0

    while True:
        flagbits = compressed[src]
        src += 1
        numflags = 8

        while True:
            if dst >= len(decompressed):
                return bytes(decompressed)
            if numflags == 0:
                break

            numflags -= 1
            flagbits *= 2
            if flagbits & 0x100 == 0:
                decompressed[dst] = compressed[src]
                dst += 1
                src += 1
            else:
                length = 3 + compressed[src] // 0x10
                disp = 1 + (compressed[src] & 0xF) * 0x100 + compressed[src + 1]
                src += 2

                for _ in range(length):
                    decompressed[dst] = decompressed[dst - disp]
                    dst += 1


def load(path: Path):
    with open(path, "rb") as stream:
        return stream.read()


def save(path: Path, data: bytes):
    with open(path, "wb") as stream:
        stream.write(data)


def decompress_file(path: Path):
    data = load(path)
    return lzss_decompress(data)


def make_4_frame_animation(data: bytes):
    middle_frame = data[0x80:0x100]
    return data + middle_frame


def get_tile(tiledata: bytes, x: int, y: int) -> bytes:
    offset = 0x20 * x + 0x400 * y
    return tiledata[offset:offset+0x20]


def get_sprites(tileset: bytes, start_x: int, start_y: int, sprites: int, rows: int = 2):
    return b"".join(get_tile(tileset, 2 * t + x, y)
                    for t in range(sprites)
                    for y in range(start_y, start_y + rows)
                    for x in range(start_x, start_x + 2))


def extract_chozo_statue_sprite(infilename: str, outfilename: str):
    statue = decompress_file(sprite_data / infilename)
    item = get_sprites(statue, 4, 4, 3)
    save(rando_data / outfilename, make_4_frame_animation(item))


def extract_unknown_chozo_statue_sprite(infilename: str, outfilename: str, y_offset: int):
    statue = decompress_file(sprite_data / infilename)
    tiles = get_sprites(statue, 4, 4, 2)
    byte_offset = y_offset * 4
    shifted = (tiles[byte_offset:0x20] + tiles[0x40:0x40 + byte_offset]
             + tiles[0x20 + byte_offset:0x40] + tiles[0x60:0x60 + byte_offset]
             + tiles[0x40 + byte_offset:0x60] + tiles[0x80:0x80 + byte_offset]
             + tiles[0x60 + byte_offset:0x80] + tiles[0xA0:0xA0 + byte_offset])
    save(rando_data / outfilename, 4 * shifted)


def main():
    # Tanks are already in needed format

    # Long Beam
    extract_chozo_statue_sprite("ChozoStatueLongBeam.gfx.lz", "longbeam.gfx")

    # Charge Beam
    charge = decompress_file(sprite_data / "ChargeBeam.gfx.lz")
    charge1 = get_sprites(charge, 18, 0, 1)
    charge2 = get_sprites(charge, 20, 0, 1)
    charge3 = bytearray(charge1)
    charge3[0x20:0x40] = get_tile(charge, 22, 0)
    save(rando_data / "chargebeam.gfx", bytes(charge1 + charge2 + charge3 + charge2))

    # Ice Beam
    extract_chozo_statue_sprite("ChozoStatueIceBeam.gfx.lz", "icebeam.gfx")

    # Wave Beam
    extract_chozo_statue_sprite("ChozoStatueWaveBeam.gfx.lz", "wavebeam.gfx")

    # Plasma Beam
    extract_unknown_chozo_statue_sprite("ChozoStatuePlasmaBeam.gfx.lz", "plasmabeamunknown.gfx", 4)

    # Bomb
    extract_chozo_statue_sprite("ChozoStatueBomb.gfx.lz", "bomb.gfx")

    # Varia Suit
    extract_chozo_statue_sprite("ChozoStatueVariaSuit.gfx.lz", "variasuit.gfx")

    # Gravity Suit
    extract_unknown_chozo_statue_sprite("ChozoStatueGravitySuit.gfx.lz", "gravitysuitunknown.gfx", 2)

    # Morph Ball
    morph = decompress_file(sprite_data / "MorphBall.gfx.lz")
    morph_core = get_sprites(morph, 0, 0, 3)
    morph_glass = get_sprites(morph, 6, 0, 1)
    morph_composited = bytearray(len(morph_core))
    for t in range(3):
        for y in range(2):
            for i in range(0x40):
                glass_pair = morph_glass[i + 0x40 * y]
                glass_left, glass_right = glass_pair & 0xF, glass_pair >> 4
                ball_pair = morph_core[i + 0x40 * y + 0x80 * t]
                ball_left, ball_right = ball_pair & 0xF, ball_pair >> 4
                if glass_left != 0:
                    ball_left = glass_left
                if glass_right != 0:
                    ball_right = glass_right
                combined = ball_right << 4 | ball_left
                morph_composited[i + 0x40 * y + 0x80 * t] = combined
    save(rando_data / "morphball.gfx", make_4_frame_animation(morph_composited))

    # Speed Booster
    extract_chozo_statue_sprite("ChozoStatueSpeedbooster.gfx.lz", "speedbooster.gfx")

    # Hi-Jump Boots
    extract_chozo_statue_sprite("ChozoStatueHighJump.gfx.lz", "hijump.gfx")

    # Screw Attack
    extract_chozo_statue_sprite("ChozoStatueScrewAttack.gfx.lz", "screwattack.gfx")

    # Space Jump
    extract_unknown_chozo_statue_sprite("ChozoStatueSpaceJump.gfx.lz", "spacejumpunknown.gfx", 2)

    # Power Grip
    powergrip = decompress_file(sprite_data / "PowerGrip.gfx.lz")
    powergrip = get_sprites(powergrip, 0, 0, 3)
    save(rando_data / "powergrip.gfx", make_4_frame_animation(powergrip))


if __name__ == "__main__":
    main()

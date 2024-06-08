import itertools
from pathlib import Path
import struct
from typing import Iterable, Tuple


data = Path("data")
sprite_data = data / "sprites"
rando_data = data / "rando"


def batched(iterable, n):
    "Batch data into tuples of length n. The last batch may be shorter."
    # batched('ABCDEFG', 3) --> ABC DEF G
    if n < 1:
        raise ValueError('n must be at least one')
    it = iter(iterable)
    while batch := tuple(itertools.islice(it, n)):
        yield batch


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


def get_tile(tiledata: bytes, x: int, y: int) -> bytes:
    offset = 0x20 * x + 0x400 * y
    return tiledata[offset:offset+0x20]


def get_sprites(tileset: bytes, start_x: int, start_y: int, sprites: int, rows: int = 2):
    return b"".join(get_tile(tileset, x, y)
                    for y in range(start_y, start_y + rows)
                    for x in range(start_x, start_x + 2 * sprites))


def extract_tank(tank_gfx: bytes, outfilename: str):
    top = tank_gfx[0:0x40] + tank_gfx[0x80:0xC0] + tank_gfx[0x100:0x140]
    bottom = tank_gfx[0x40:0x80] + tank_gfx[0xC0:0x100] + tank_gfx[0x140:0x180]
    save(rando_data / outfilename, top + bottom)


def extract_chozo_statue_sprite(infilename: str, outfilename: str):
    statue = decompress_file(sprite_data / infilename)
    item = get_sprites(statue, 4, 4, 3)
    save(rando_data / outfilename, item)


def extract_unknown_chozo_statue_sprite(infilename: str, outfilename: str, y_offset: int):
    statue = decompress_file(sprite_data / infilename)
    tiles = get_sprites(statue, 4, 4, 2)
    byte_offset = y_offset * 4
    top = tiles[byte_offset:0x20] + tiles[0x80:0x80 + byte_offset] + tiles[0x20 + byte_offset:0x40] + tiles[0xA0:0xA0 + byte_offset]
    bottom = tiles[0x80 + byte_offset:0xA0] + tiles[0x40:0x40 + byte_offset] + tiles[0xA0 + byte_offset:0xC0] + tiles[0x60:0x60 + byte_offset]
    save(rando_data / outfilename, 3 * top + 3 * bottom)


def main():
    # Tanks
    tanks = load(data / "animated_tiles/Tanks.gfx")
    extract_tank(tanks[0:0x180], "missiletank.gfx")
    extract_tank(tanks[0x200:0x380], "energytank.gfx")
    extract_tank(tanks[0x400:0x580], "powerbombtank.gfx")
    extract_tank(tanks[0x600:0x780], "supermissiletank.gfx")

    # Long Beam
    extract_chozo_statue_sprite("ChozoStatueLongBeam.gfx.lz", "longbeam.gfx")

    # Charge Beam
    charge = decompress_file(sprite_data / "ChargeBeam.gfx.lz")
    charge1 = get_sprites(charge, 18, 0, 2, 1)
    charge2 = get_sprites(charge, 18, 1, 2, 1)
    charge_final_1 = bytearray(0x20 * 2 * 3)
    charge_final_2 = bytearray(0x20 * 2 * 3)
    charge_final_1[0:0x80] = charge1
    charge_final_1[0x80:0xA0] = charge1[:0x20]
    charge_final_1[0xA0:] = get_tile(charge, 22, 0)
    charge_final_2[0:0x80] = charge2
    charge_final_2[0x80:] = charge2[:0x40]
    save(rando_data / "chargebeam.gfx", bytes(charge_final_1 + charge_final_2))

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
                ball_pair = morph_core[0x40 * t + i + 3 * 0x40 * y]
                ball_left, ball_right = ball_pair & 0xF, ball_pair >> 4
                if glass_left != 0:
                    ball_left = glass_left
                if glass_right != 0:
                    ball_right = glass_right
                combined = ball_right << 4 | ball_left
                morph_composited[0x40 * t + i + 3 * 0x40 * y] = combined
    save(rando_data / "morphball.gfx", morph_composited)

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
    save(rando_data / "powergrip.gfx", powergrip)



if __name__ == "__main__":
    main()

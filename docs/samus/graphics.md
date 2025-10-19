# Samus graphics

This document will go in detail about how Samus's graphics are stored, processed, and rendered.
It's a fairly involved process, but can easily be broken down into simple systems.

- [Data](#data)
  - [Graphics](#graphics)
  - [Palette](#palette)
  - [Animation data](#animation-data)
  - [Arm cannon](#arm-cannon)
  - [Effects](#effects)
- [Tables](#tables)
  - [Animation pointers table](#animation-pointers-table)
  - [Effects animation pointers table](#effects-animation-pointers-table)
  - [Arm cannon animation pointers table](#arm-cannon-animation-pointers-table)
  - [Palette](#palette-1)
- [Processing](#processing)
  - [Graphics/oam](#graphicsoam)
  - [Palette](#palette-2)
  - [Arm cannon](#arm-cannon-1)
  - [Animation](#animation)
- [Rendering](#rendering)
  - [Oam](#oam)
  - [Echo](#echo)
  - [VRAM layout](#vram-layout)
  - [PALRAM layout](#palram-layout)

## Data

### Graphics

Graphics are stored in 8x8 pixel blocks, each set of graphics contains 2 subsets of 8x8 blocks, their length is defined at the beginning of the graphics using 2 bytes :

| Offset | Size | Explanation |
|--------|------|-------------|
| 0 | 1 | First subset length (in blocks)
| 1 | 1 | Second subset length (in blocks)
| 2 | X | First subset
| X | X | Second subset

The graphics are not compressed, or formatted in any special way, they are raw, 4bpp graphics.

Considering that a block of 8x8 pixels takes up 32 bytes, the total length of a set of graphics can be computed like so : `2 + SizeSet1 * 32 + SizeSet2 * 32`.

The offset of the first subset of graphics will be 2, the offset of the second subset will be `2 + SizeSet1 * 32`.

The presence of the 2 byte header for the sizes is what makes the graphics so annoying to view in a graphics editor, every set of graphics will offset everything by 2 pixels, making the graphics more jumbled as you go on.

### Palette

Palettes are stored as regular palette data, they don't have any header, instead their size (meaning amount of rows) is "assumed" based on the role/type of the palette.

There are 9 types of palette :

| Rows | Type | Explanation |
|--------|------|-------------|
3  | Default        | Used by default and in other states as well.
5  | BeamRelease    | Used after shooting the beam, each row corresponds to a beam type : Ice (2), Plasma (4), Wave (3), Long (1), None (0).
2  | Flashing       | Used when taking damage/being invincible, cycles every 2 frames.
3  | Speedboost     | Used when speedboosting, each row is active for 2 frames, and the palette cycles.
2  | Unmorph        | Used when unmorphing, the first half of the animation used the first row, and the second half uses the second row.
3  | Saving         | Used when saving/loading the game.
10 | ChargingBeam   | Used when charging the beam, uses the same rules as the beam release, except each beam type has 2 rows, so every offset is doubled. The two rows alternate every 4 frame.
2  | DownloadingMap | Used when downloading the map.
3  | Frozen         | Used when frozen (unused in zero mission).

Additionally, there are 5 variations of each palette, depending on the suit type and current suit equipped :

- Fully powered + gravity
- Fully powered
- Normal suit + varia
- Normal suit
- Every other combination

### Animation data

The animation data is an extended `FrameData` struct, it contains a raw oam data pointer as well as a frame duration, but it also contains 2 pointers to graphics.

| Offset | Size | Explanation |
|--------|------|-------------|
| 0 | 4 | "Top" graphics pointer
| 4 | 4 | "Bottom" graphics pointer
| 8 | 4 | Oam pointer
| C | 1 | Frame duration/timer

### Arm cannon

Arm cannon is (most of the time) not in the samus graphics and is handled differently.

In those cases, it uses its own set of graphics and oam (raw oam only, it follows the same animation timer as samus).

Graphics are split in 2, top and bottom, and each graphics are 2 8x8 blocks, so 64 bytes in size.

Animation data for the arm cannon only contains 2 fields :

| Offset | Size | Explanation |
|--------|------|-------------|
| 0 | 4 | Offset pointer
| 4 | 4 | Oam pointer

The offset pointer points to an array of X/Y offsets (from samus) that determine where the arm cannon is located, there is one entry per animation frame.

The offsets use the same format as oam position, i.e. signed 8 bit for Y offset, and signed 9 bit for X offset.

### Effects

Effects are small parts of Samus' graphics that aren't directly stored in the normal graphics. They are used by the screw attack (electric outline), speedbooster (small speed particles) and shinespark (small speed particles) poses.

They are stored almost exactly the same as Samus' graphics and animations, with the only exception being that there's only a single graphics pointers in the animation data.

## Tables

All of the elements above are grouped into tables, and tables of pointers to tables.

### Animation pointers table

Contains the animation data for a specific pose, with its possible variations.

It's a two dimension array, the first index can vary depending on the table, and the second index will always be the facing direction (right or left).

The first index can be one of those options :
- Arm cannon direction (not necessarily all of them, depends on the pose).
- Forced movement.
- A simple boolean (whether arm cannon is armed, whether space jump is active during screw).

### Effects animation pointers table

Same as above, but for the effects animations.

### Arm cannon animation pointers table

Same as above, but for the arm cannon animations.

Arm cannon also has tables for the graphics pointers, they are indexed using the current arm cannon direction. There are 4 variations for each table depending on those 2 states : armed/not armed, right/left.

Moreover, each of them have 2 tables, upper graphics, and lower graphics.

### Palette

Palettes aren't stored in any table, they are accessed directly depending on the suit type and equipped suit, as mentionned in the [palette section](#palette).

There are 2 exceptions to that, the saving/loading palette and downloading map palette. Even though they both have a dedicated palette already, the final palette is a combinaison of the default and dedicated palette.

## Processing

### Graphics/oam

Graphics and oam are extracted from the different tables depending on Samus' state. If you want to know how a specific pose is handled, refer to the function `SamusUpdateGraphicsOam` in `src/samus.c`.

Each animation data has 2 graphics pointers, each having 2 subsets of graphics, this makes for 4 graphics subset per frame, each of them is assigned a (kind of bad) name :

- Top, subset 1 : Shoulders
- Top, subset 2 : Torso
- Bottom, subset 1 : Legs
- Bottom, subset 2 : Lower body

There is only a single oam pointer, it is named body oam.

### Palette

Palettes are fetched depending on the state as described in the [palette section](#palette), even so, most of the state actually use a mix of multiple palettes, mainly the default one + the specific one.
Refer to `SamusUpdatePalette` in `src/samus.c` for specifics.

### Arm cannon

A similar logic to the body is applied to the arm cannon graphics, though with far less entries : hanging, on zipline, running and everything else.
The graphics are stored in `arm cannon upper` and `arm cannon lower` respectively.

Oam is handled elsewhere (`SamusUpdateArmCannonPositionOffset` in `src/samus.c`) and this time in the same manner as the body.
Oam is stored in `arm cannon`.

### Animation

Animation update is handled in code, per pose, meaning that some poses have specific behavior, e..g looping on one specific frame, playing only a part of the animation...
However it still follows the same rules as the frame data, just with some exceptions here and there.

If Samus is slowed, the animations will also be slowed, this effect is achieved by doubling the animation timer, making each frame last twice as long (this still happens in 8bit space, so overflow can happen).

The animation used to update are not the same as the ones used to render, the animation fetches from the default/global pose table, in other words only the "default" animation for that pose is used for the update (default arm cannon direction, default forced movement.), meaning that the timer for the other animations is never used and does nothing.

## Rendering

### Oam

Samus is between the medium and low priority in the draw order, meaning it's possible for both sprites and projectiles to be behind or in front of her, but particles will also be in front of her.

Samus can have background priority 0 or 1 depending on the room header configuration.

Samus is drawn in 3 steps, body, arm cannon, effects

The body is always drawn, but the arm cannon and effects are optional. Arm cannon and effects can also be drawn in front or behind the body, this is specified in the raw oam, in the same halfword that holds the part count using bit 12 or bit 13 respectively.
At least one of those bits must be set, otherwise nothing will be drawn, moreover, both bits can be set to draw is both in front and behind of samus, they are not mutually exclusive.

### Echo

The echo re-draws the body oam only, it draws it using the previous positions over 64 frames. The echo always uses the second palette row. It is always drawn last so it has the lowest priority.

### VRAM layout

All graphics are sent to VRAM in pre-allocated space at the same time :

```
Shoulders         : Offset 0x000 in object VRAM (0x6010000).
Legs              : Offset 0x280 in object VRAM (0x6010280).
Torso             : Offset 0x400 in object VRAM (0x6010400).
Lower body        : Offset 0x680 in object VRAM (0x6010680).
Arm cannon upper  : Offset 0x800 in object VRAM (0x6010800).
Screw/speed       : Offset 0x840 in object VRAM (0x6010840).
Arm cannon lower  : Offset 0xC00 in object VRAM (0x6010C00).
Screw/shinespark  : Offset 0x840 in object VRAM (0x6010C40).
```

The transfer is done during v-blank to avoid flickering and visual oddities.

### PALRAM layout

The palette is copied to offset 0 in object PALRAM (0x5000200) and always takes 2 rows.

The transfer is done during v-blank to avoid flickering and visual oddities.

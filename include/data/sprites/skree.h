#ifndef SKREE_DATA_H
#define SKREE_DATA_H

#include "types.h"
#include "macros.h"
#include "oam.h"

static const i16 sSkreeFallingSpeed[8] = {
    2, 4, 6, 7, 12, 14, 16, SHORT_MAX
};

static const u32 sSkreeGreenGFX[264] = INCBIN_U32("data/sprites/SkreeGreen.gfx.lz");
static const u16 sSkreeGreenPAL[16] = INCBIN_U16("data/sprites/SkreeGreen.pal");
static const u32 sSkreeBlueGFX[264] = INCBIN_U32("data/sprites/SkreeBlue.gfx.lz");
static const u16 sSkreeBluePAL[16] = INCBIN_U16("data/sprites/SkreeBlue.pal");

static const u16 sSkreeOAM_Idle_Frame0[13] = {
    0x4,
    0x0, OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x200,
    0x10, OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x202,
    0x0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x200,
    0x10, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x202
};

static const u16 sSkreeOAM_Idle_Frame1[7] = {
    0x2,
    0x0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x20c,
    0x10, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x20e
};

static const u16 sSkreeOAM_Idle_Frame2[13] = {
    0x4,
    OBJ_SHAPE_VERTICAL | 0x0, 0x1fc, OBJ_SPRITE_OAM | 0x210,
    OBJ_SHAPE_VERTICAL | 0x10, 0x1fc, OBJ_SPRITE_OAM | 0x212,
    0x0, 0x4, OBJ_SPRITE_OAM | 0x211,
    0x0, OBJ_X_FLIP | 0x1f4, OBJ_SPRITE_OAM | 0x211
};

static const u16 sSkreeOAM_Idle_Frame3[7] = {
    0x2,
    0x0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x213,
    0x10, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x215
};

static const u16 sSkreeOAM_Spinning_Frame1[13] = {
    0x4,
    0x0, OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0x10, 0x1f0, OBJ_SPRITE_OAM | 0x20a,
    0x0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0x10, OBJ_X_FLIP | 0x0, OBJ_SPRITE_OAM | 0x20a
};

static const u16 sSkreeOAM_Spinning_Frame2[13] = {
    0x4,
    0x0, OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x204,
    OBJ_SHAPE_HORIZONTAL | 0x10, 0x1f0, OBJ_SPRITE_OAM | 0x206,
    0x0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x204,
    OBJ_SHAPE_HORIZONTAL | 0x10, OBJ_X_FLIP | 0x0, OBJ_SPRITE_OAM | 0x206
};

static const u16 sSkreeOAM_CrashingUnused_Frame0[13] = {
    0x4,
    0xf0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x200,
    0xe0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x202,
    0xf0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x200,
    0xe0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x202
};

static const u16 sSkreeOAM_CrashingUnused_Frame1[7] = {
    0x2,
    0xf0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x20c,
    0xe0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x20e
};

static const u16 sSkreeOAM_CrashingUnused_Frame2[13] = {
    0x4,
    OBJ_SHAPE_VERTICAL | 0xf0, OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x210,
    OBJ_SHAPE_VERTICAL | 0xe0, OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x212,
    0xf8, OBJ_Y_FLIP | 0x4, OBJ_SPRITE_OAM | 0x211,
    0xf8, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1f4, OBJ_SPRITE_OAM | 0x211
};

static const u16 sSkreeOAM_CrashingUnused_Frame3[7] = {
    0x2,
    0xf0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x213,
    0xe0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x215
};

static const u16 sSkreeOAM_CrashingUnused2_Frame1[13] = {
    0x4,
    0xf0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_Y_FLIP | 0x1f0, OBJ_SPRITE_OAM | 0x20a,
    0xf0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_Y_FLIP | 0x0, OBJ_SPRITE_OAM | 0x20a
};

static const u16 sSkreeOAM_CrashingUnused2_Frame2[13] = {
    0x4,
    0xf0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x204,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_Y_FLIP | 0x1f0, OBJ_SPRITE_OAM | 0x206,
    0xf0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x204,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_Y_FLIP | 0x0, OBJ_SPRITE_OAM | 0x206
};

static const u16 sSkreeExplosionOAM_GoingUp_Frame0[10] = {
    0x3,
    0x6, 0x1fb, OBJ_SPRITE_OAM | 0x238,
    0xf6, 0x1fb, OBJ_SPRITE_OAM | 0x217,
    0xfe, 0x1fb, OBJ_SPRITE_OAM | 0x218
};

static const u16 sSkreeExplosionOAM_GoingUp_Frame1[10] = {
    0x3,
    0xf8, 0x1fb, OBJ_SPRITE_OAM | 0x217,
    0xfd, 0x1fb, OBJ_SPRITE_OAM | 0x218,
    0x2, 0x1fb, OBJ_SPRITE_OAM | 0x238
};

static const u16 sSkreeExplosionOAM_GoingUp_Frame2[7] = {
    0x2,
    0xff, 0x1f9, OBJ_SPRITE_OAM | 0x238,
    0xf9, OBJ_Y_FLIP | 0x1f9, OBJ_SPRITE_OAM | 0x238
};

static const u16 sSkreeExplosionOAM_GoingDown_Frame0[10] = {
    0x3,
    OBJ_SHAPE_VERTICAL | 0xf6, 0x1fa, OBJ_SPRITE_OAM | 0x219,
    0x6, 0x1fa, OBJ_SPRITE_OAM | 0x23a,
    0xfe, 0x1fa, OBJ_SPRITE_OAM | 0x21a
};

static const u16 sSkreeExplosionOAM_GoingDown_Frame1[7] = {
    0x2,
    0xfa, 0x1fa, OBJ_SPRITE_OAM | 0x219,
    0xfe, 0x1fa, OBJ_SPRITE_OAM | 0x21a
};

static const u16 sSkreeExplosionOAM_GoingDown_Frame2[4] = {
    0x1,
    0xfc, 0x1fa, OBJ_SPRITE_OAM | 0x219
};

static const struct FrameData sSkreeOAM_Idle[5] = {
    sSkreeOAM_Idle_Frame0,
    0x8,
    sSkreeOAM_Idle_Frame1,
    0x8,
    sSkreeOAM_Idle_Frame2,
    0x8,
    sSkreeOAM_Idle_Frame1,
    0x8,
    NULL,
    0x0
};

static const struct FrameData sSkreeOAM_Spinning[6] = {
    sSkreeOAM_Idle_Frame0,
    0x4,
    sSkreeOAM_Spinning_Frame1,
    0x2,
    sSkreeOAM_Spinning_Frame2,
    0x2,
    sSkreeOAM_Spinning_Frame1,
    0x2,
    sSkreeOAM_Spinning_Frame2,
    0x2,
    NULL,
    0x0
};

static const struct FrameData sSkreeOAM_GoingDown[5] = {
    sSkreeOAM_Idle_Frame0,
    0x2,
    sSkreeOAM_Idle_Frame1,
    0x2,
    sSkreeOAM_Idle_Frame2,
    0x2,
    sSkreeOAM_Idle_Frame3,
    0x2,
    NULL,
    0x0
};

static const struct FrameData sSkreeOAM_Crashing[5] = {
    sSkreeOAM_Idle_Frame0,
    0x1,
    sSkreeOAM_Idle_Frame1,
    0x1,
    sSkreeOAM_Idle_Frame2,
    0x1,
    sSkreeOAM_Idle_Frame3,
    0x1,
    NULL,
    0x0
};

static const struct FrameData sSkreeOAM_CrashingUnused[5] = {
    sSkreeOAM_CrashingUnused_Frame0,
    0x8,
    sSkreeOAM_CrashingUnused_Frame1,
    0x8,
    sSkreeOAM_CrashingUnused_Frame2,
    0x8,
    sSkreeOAM_CrashingUnused_Frame3,
    0x8,
    NULL,
    0x0
};

static const struct FrameData sSkreeOAM_CrashingUnused2[6] = {
    sSkreeOAM_CrashingUnused_Frame0,
    0x4,
    sSkreeOAM_CrashingUnused2_Frame1,
    0x2,
    sSkreeOAM_CrashingUnused2_Frame2,
    0x4,
    sSkreeOAM_CrashingUnused2_Frame1,
    0x1,
    sSkreeOAM_CrashingUnused_Frame2,
    0x10,
    NULL,
    0x0
};

static const struct FrameData sSkreeOAM_CrashingUnused3[5] = {
    sSkreeOAM_CrashingUnused_Frame0,
    0x2,
    sSkreeOAM_CrashingUnused_Frame1,
    0x2,
    sSkreeOAM_CrashingUnused_Frame2,
    0x2,
    sSkreeOAM_CrashingUnused_Frame3,
    0x2,
    NULL,
    0x0
};

static const struct FrameData sSkreeOAM_CrashingUnused4[5] = {
    sSkreeOAM_CrashingUnused_Frame0,
    0x1,
    sSkreeOAM_CrashingUnused_Frame1,
    0x1,
    sSkreeOAM_CrashingUnused_Frame2,
    0x1,
    sSkreeOAM_CrashingUnused_Frame3,
    0x1,
    NULL,
    0x0
};

static const struct FrameData sSkreeExplosionOAM_GoingDown[4] = {
    sSkreeExplosionOAM_GoingDown_Frame0,
    0x8,
    sSkreeExplosionOAM_GoingDown_Frame1,
    0x6,
    sSkreeExplosionOAM_GoingDown_Frame2,
    0x6,
    NULL,
    0x0
};

static const struct FrameData sSkreeExplosionOAM_GoingUp[4] = {
    sSkreeExplosionOAM_GoingUp_Frame0,
    0x8,
    sSkreeExplosionOAM_GoingUp_Frame1,
    0x6,
    sSkreeExplosionOAM_GoingUp_Frame2,
    0x6,
    NULL,
    0x0
};

#endif
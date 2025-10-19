#ifndef MULTIBOOT_STRUCTS_H
#define MULTIBOOT_STRUCTS_H

#include "types.h"

#define READ_SIO_MULTI(i) (*(((vu16*)REG_SIO_MULTI) + i))

#define MULTIBOOT_MAX_CHILD     3
#define MULTIBOOT_HEADER_SIZE   0xC0
#define MULTIBOOT_SEND_SIZE_MIN 0x100
#define MULTIBOOT_SEND_SIZE_MAX 0x40000

#define MULTIBOOT_SERVER_TYPE_NORMAL 0
#define MULTIBOOT_SERVER_TYPE_QUICK  1

#define MULTIBOOT_CONNECTION_CHECK_WAIT CONVERT_SECONDS(.25f)

#define MULTIBOOT_HANDSHAKE_TIMEOUT 400

#define MULTIBOOT_ERROR_NO_PROBE_TARGET 0x50
#define MULTIBOOT_ERROR_NO_DL_READY 0x60

#define MULTIBOOT_PARENT_START_PROBE 0x61
#define MULTIBOOT_PARENT_INFO 0x62
#define MULTIBOOT_PARENT_REQUEST_DL_READY 0x63
#define MULTIBOOT_PARENT_START_DL 0x64
#define MULTIBOOT_PARENT_REQUEST_CRC 0x65
#define MULTIBOOT_PARENT_VERIFY_CRC 0x66

#define MULTIBOOT_ERROR_BOOT_FAILED 0x70
#define MULTIBOOT_ERROR_HANDSHAKE_FAILURE 0x71

#define MULTIBOOT_CLIENT_INFO 0x72
#define MULTIBOOT_CLIENT_DL_READY 0x73
#define MULTIBOOT_CLIENT_CALC_CRC 0x74
#define MULTIBOOT_CLIENT_CRC_READY 0x75

// Probe count values:
#define MULTIBOOT_REQ_PREP_REC                  0x0
#define MULTIBOOT_REQ_START_REC                 0x1
#define MULTIBOOT_REQ_PROC_REC                  0x2

#define MULTIBOOT_REC_COMPLETE                  0xc4

#define MULTIBOOT_REQ_TX_CHECK                  0xd0
#define MULTIBOOT_REQ_TX_START                  0xd1

#define MULTIBOOT_REQ_HANDSHAKE_START           0xe0
#define MULTIBOOT_REQ_HANDSHAKE_HEADER_CHECK_1  0xe1
#define MULTIBOOT_REQ_HANDSHAKE_HEADER_CHECK_2  0xe2
#define MULTIBOOT_REQ_HANDSHAKE_HEADER_CHECK_3  0xe3
#define MULTIBOOT_REQ_HANDSHAKE_HEADER_CHECK_4  0xe4
#define MULTIBOOT_REQ_HANDSHAKE_HEADER_CHECK_5  0xe5
#define MULTIBOOT_REQ_HANDSHAKE_HEADER_CHECK_6  0xe6
#define MULTIBOOT_REQ_HANDSHAKE_HEADER_CHECK_7  0xe7
#define MULTIBOOT_REQ_HANDSHAKE_HEADER_CHECK_8  0xe8
#define MULTIBOOT_HANDSHAKE_SUCCESS             0xe9

struct MultiBootData {
    u32 systemWork_1[5];
    u8 handshakeData;
    u16 handshakeTimeout;
    u8 probeCount;
    u8 clientData[MULTIBOOT_MAX_CHILD];
    u8 paletteData;
    u8 responseBit;
    u8 clientBit;
    u8 reserved_1;
    const u8* bootSourcePointer;
    const u8* bootEndPointer;
    const u8* dataSentPointer;
    u8* reserved_2[MULTIBOOT_MAX_CHILD];
    u32 systemWork_2[4];
    u8 sendFlag;
    u8 probeTargetBit;
    u8 checkWait;
    u8 serverType;
};

extern u16 gMultiBootRequiredData[MULTIBOOT_MAX_CHILD];

#endif /* MULTIBOOT_STRUCTS_H */

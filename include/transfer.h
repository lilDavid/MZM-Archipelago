#ifndef TRANSFER_H
#define TRANSFER_H

#include "types.h"

u32 TransferProcessSend(u32 size, const u32* pData);
void TransferReloadTransfer(void);
void TransferExchangeData(void);

#endif /* TRANSFER_H */

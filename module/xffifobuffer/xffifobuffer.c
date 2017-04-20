#include <string.h>

#include "xftypedef.h"
#include "xffifobuffer.h"

//#define NULL  0

void XF_FIFOBufferInit(XF_FIFOBuffer *fifoBuffer, void *buffer, uint16 size) {
    fifoBuffer->posHead = 0;
    fifoBuffer->postTail = 0;
    fifoBuffer->buffer = buffer;
    fifoBuffer->sizeBuffer = size;
    fifoBuffer->state = XF_FIFOBUFFER_STATE_RUN;
}

uint16 XF_FIFOBufferLoadSize(XF_FIFOBuffer *fifoBuffer) {
    return (fifoBuffer->posHead > fifoBuffer->postTail) ? (fifoBuffer->sizeBuffer - fifoBuffer->posHead + fifoBuffer->postTail) : (fifoBuffer->postTail - fifoBuffer->posHead);
}

uint16 XF_FIFOBufferUnloadSize(XF_FIFOBuffer *fifoBuffer) {
    return (fifoBuffer->posHead <= fifoBuffer->postTail) ? (fifoBuffer->sizeBuffer - fifoBuffer->postTail + fifoBuffer->posHead) : (fifoBuffer->posHead - fifoBuffer->postTail);
}


uint16 XF_FIFOBufferRead(XF_FIFOBuffer *fifoBuffer, void *data, uint16 size) {
    uint16 sizeFifo = (fifoBuffer->posHead > fifoBuffer->postTail) ? (fifoBuffer->sizeBuffer - fifoBuffer->posHead + fifoBuffer->postTail) : (fifoBuffer->postTail - fifoBuffer->posHead);  //FIFO可读数据长度
    uint16 sizeRead  = (size < sizeFifo) ? size : sizeFifo;//(size < fifoBuffer->sizeBuffer) ? size : fifoBuffer->sizeBuffer;  //实际要读的数据长度
	uint16 sizeCnt = 0;
    uint16 sizeTemp = 0;

    if (fifoBuffer->state != XF_FIFOBUFFER_STATE_RUN) return 0;

    sizeTemp = fifoBuffer->sizeBuffer - fifoBuffer->posHead;
    if (sizeTemp < sizeRead) {
        if ((sizeFifo >= sizeRead) || (sizeFifo < sizeRead && sizeFifo >= sizeTemp)) {
            memcpy((char*)data + sizeCnt, (char*)fifoBuffer->buffer + fifoBuffer->posHead, sizeTemp);
            sizeRead -= sizeTemp;
            sizeFifo -= sizeTemp;
            fifoBuffer->posHead = 0;
            sizeCnt += sizeTemp;
        }
    }

    sizeTemp = (sizeRead < sizeFifo) ? sizeRead : sizeFifo;
    memcpy((char*)data + sizeCnt, (char*)fifoBuffer->buffer + fifoBuffer->posHead, sizeTemp);
    sizeRead -= sizeTemp;
    sizeFifo -= sizeTemp;
    fifoBuffer->posHead = (fifoBuffer->posHead + sizeTemp) % fifoBuffer->sizeBuffer;
    sizeCnt += sizeTemp;

    return sizeCnt;
}

uint16 XF_FIFOBufferWrite(XF_FIFOBuffer *fifoBuffer, void *data, uint16 size) {
    uint16 sizeWrite = (size < fifoBuffer->sizeBuffer) ? size : fifoBuffer->sizeBuffer;
    uint16 sizeFifo = (fifoBuffer->posHead <= fifoBuffer->postTail) ? (fifoBuffer->sizeBuffer - fifoBuffer->postTail + fifoBuffer->posHead) : (fifoBuffer->posHead - fifoBuffer->postTail);  //FIFO可读数据长度
    uint16 sizeCnt = 0;
    uint16 sizeTemp = 0;
    uint8 overflow = (sizeWrite >= sizeFifo) ? 1 : 0;  //覆盖标志

    if (fifoBuffer->state != XF_FIFOBUFFER_STATE_RUN) return 0;

    //
    //if ((fifoBuffer->posHead == fifoBuffer->postTail) && (sizeWrite > 0)) {
    //    fifoBuffer->posHead = (fifoBuffer->posHead + 1) % fifoBuffer->sizeBuffer;
    //}

    sizeTemp = fifoBuffer->sizeBuffer - fifoBuffer->postTail;
    if (sizeTemp < sizeWrite) {
        memcpy((char*)fifoBuffer->buffer + fifoBuffer->postTail, (char*)data + sizeCnt, sizeTemp);
        sizeWrite -= sizeTemp;
        fifoBuffer->postTail = 0;
        sizeCnt += sizeTemp;
    }

    sizeTemp = sizeWrite;
    memcpy((char*)fifoBuffer->buffer + fifoBuffer->postTail, (char*)data + sizeCnt, sizeTemp);
    sizeWrite -= sizeTemp;
    fifoBuffer->postTail = (fifoBuffer->postTail + sizeTemp) % fifoBuffer->sizeBuffer;
    sizeCnt += sizeTemp;

    //数据被覆盖
    if(overflow) fifoBuffer->posHead = (fifoBuffer->postTail + 1) % fifoBuffer->sizeBuffer;

    return sizeCnt;
}


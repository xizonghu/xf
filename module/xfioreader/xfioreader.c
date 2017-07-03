#include <string.h>

#include "xftypedef.h"
#include "xfioreader.h"

#define resetIOReader(reader) {reader->posBuffer = 0;reader->state = XF_IOREADER_STATE_COMPLETE;}

static uint16 updateBuffer(char *dst, const char *src, uint16 size) {
    uint16 pos = 0;
    for (pos = 0; pos < size; pos++) {
        *((uint8*)dst + pos) = *((uint8*)src + pos);
    }
    return pos;
}

static void XF_IOReaderProcess(XF_IOReader *reader) {
    uint16 sizeBodyInBuf = 0, sizeBodyInHead = 0;
    //检查数据头长度
    if (reader->posBuffer < reader->sizeHead) {
        reader->state = XF_IOREADER_STATE_PORTION;
        reader->IF->setTimeout();
        return;
    }

    sizeBodyInBuf = reader->posBuffer - reader->sizeHead;  //读到buffer中的数据体长度
    sizeBodyInHead = reader->IF->getBodySize(reader->buffer, reader->posBuffer);  //数据头中指示的数据体长度

    //数据等于一帧
    if (sizeBodyInBuf == sizeBodyInHead) {
        reader->CB->processData(reader->buffer, reader->sizeHead + sizeBodyInHead);
        resetIOReader(reader);
        return;
    }
    //数据大于一帧
    else if (sizeBodyInBuf > sizeBodyInHead) {
        uint16 sizeData = reader->sizeHead + sizeBodyInHead;
        reader->CB->processData(reader->buffer, sizeData);
        updateBuffer(reader->buffer, (char*)((uint8*)reader->buffer + sizeData), sizeBodyInBuf - sizeBodyInHead);
        reader->posBuffer -= sizeData;
        XF_IOReaderProcess(reader);
    }
    //数据小于一帧
    else {
        reader->state = XF_IOREADER_STATE_PORTION;
        reader->IF->setTimeout();
    }
}

void XF_IOReaderInit(XF_IOReader *reader, char *buffer, uint16 sizeBuffer, uint8 sizeHead, int fd, const XF_IOReaderIf *IF, const XF_IOReaderCb *CB) {
    reader->posBuffer = 0;
    reader->state = XF_IOREADER_STATE_COMPLETE;
    reader->buffer = buffer;
    reader->sizeBuffer = sizeBuffer;
    reader->sizeHead = sizeHead;
    reader->fd = fd;
    reader->IF = IF;
    reader->CB = CB;
}

void XF_IOReaderPoll(XF_IOReader *reader) {
    uint16 size = 0;

    if(XF_NULL == reader->IF || XF_NULL == reader->CB) return;

    //读数据
    if (0 >= (size = reader->IF->readData(reader->fd, (char*)reader->buffer + reader->posBuffer, reader->sizeBuffer - reader->posBuffer))) {
        //检查超时
        if (XF_IOREADER_STATE_PORTION == reader->state && reader->IF->isTimeout()) {
            resetIOReader(reader);
        }
        return;
    }

    reader->posBuffer += size;

    XF_IOReaderProcess(reader);

    return;
}


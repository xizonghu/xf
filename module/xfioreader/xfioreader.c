#include "xfioreader.h"

#define NULL  0
#define resetIOReader(reader) {reader->posBuffer = 0;reader->state = XF_IOREADER_STATE_COMPLETE;}

void XF_IOReaderInit(XF_IOReader *reader,       const XF_IOReaderIf *IF, const XF_IOReaderCb *CB) {
    reader->posBuffer = 0;
    reader->state = XF_IOREADER_STATE_COMPLETE;
    reader->IF = IF;
    reader->CB = CB;
}

void XF_IOReaderScan(XF_IOReader *reader) {
    uint16 size = 0;
    uint16 sizeBodyBuffer = 0, sizeBody;

    if(NULL == reader->IF || NULL == reader->CB) return;

    //读数据
    if (0 >= (size = reader->IF->readData(reader->buffer + reader->posBuffer, reader->sizeBuffer - reader->posBuffer))) {
        //检查超时
        if (XF_IOREADER_STATE_PORTION == reader->state && reader->IF->isTimeout()) {
            resetIOReader(reader);
        }
        return;
    }

    //检查数据头长度
    if (size < reader->sizeHeadBuffer) {
        reader->state = XF_IOREADER_STATE_PORTION;
        reader->IF->setTimeout();
        return;
    }

    sizeBodyBuffer = size - reader->sizeHeadBuffer;  //读到buffer中的数据体长度
    sizeBody = reader->IF->getBodySize(reader->buffer);  //数据头中指示的数据体长度

    //数据头异常
    if(0 == sizeBody) {
        resetIOReader(reader);
    }

    //数据等于一帧
    if (sizeBodyBuffer == sizeBody) {
        reader->CB->processData(reader->buffer, reader->posBuffer);
        resetIOReader(reader);
        return;
    }
    //数据大于一帧
    else if (sizeBodyBuffer > sizeBody) {
        reader->CB->processData(reader->buffer, reader->posBuffer);
    }

    reader->state = XF_IOREADER_STATE_PORTION;
    reader->IF->setTimeout();

    return;
}


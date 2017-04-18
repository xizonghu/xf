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

    //������
    if (0 >= (size = reader->IF->readData(reader->buffer + reader->posBuffer, reader->sizeBuffer - reader->posBuffer))) {
        //��鳬ʱ
        if (XF_IOREADER_STATE_PORTION == reader->state && reader->IF->isTimeout()) {
            resetIOReader(reader);
        }
        return;
    }

    //�������ͷ����
    if (size < reader->sizeHeadBuffer) {
        reader->state = XF_IOREADER_STATE_PORTION;
        reader->IF->setTimeout();
        return;
    }

    sizeBodyBuffer = size - reader->sizeHeadBuffer;  //����buffer�е������峤��
    sizeBody = reader->IF->getBodySize(reader->buffer);  //����ͷ��ָʾ�������峤��

    //����ͷ�쳣
    if(0 == sizeBody) {
        resetIOReader(reader);
    }

    //���ݵ���һ֡
    if (sizeBodyBuffer == sizeBody) {
        reader->CB->processData(reader->buffer, reader->posBuffer);
        resetIOReader(reader);
        return;
    }
    //���ݴ���һ֡
    else if (sizeBodyBuffer > sizeBody) {
        reader->CB->processData(reader->buffer, reader->posBuffer);
    }

    reader->state = XF_IOREADER_STATE_PORTION;
    reader->IF->setTimeout();

    return;
}


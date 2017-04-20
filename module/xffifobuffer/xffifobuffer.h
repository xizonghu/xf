#ifndef __XF_FIFOBUFFER_H__
#define __XF_FIFOBUFFER_H__

//FIFOBuffer��ʱ�������Ǿ�����
//��ģ��ֻ��֤��ȡ���ݰ��������ԣ�����У������processData��������ɡ�

typedef enum {
    XF_FIFOBUFFER_STATE_NONE,
    XF_FIFOBUFFER_STATE_RUN,
} XF_FIFOBufferState;

typedef struct XF_FIFOBuffer_s {
    uint8 state;
    uint16 posHead;
    uint16 postTail;
    void *buffer;
    uint16 sizeBuffer;
} XF_FIFOBuffer;

extern void XF_FIFOBufferInit(XF_FIFOBuffer *fifoBuffer, void *buffer, uint16 size);
extern uint16 XF_FIFOBufferRead(XF_FIFOBuffer *fifoBuffer, void *data, uint16 size);
extern uint16 XF_FIFOBufferWrite(XF_FIFOBuffer *fifoBuffer, void *data, uint16 size);

#endif

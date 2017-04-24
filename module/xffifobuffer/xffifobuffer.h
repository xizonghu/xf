#ifndef __XF_FIFOBUFFER_H__
#define __XF_FIFOBUFFER_H__

//FIFOBuffer满时，将覆盖旧数据
//本模型只保证读取数据包的完整性，数据校验需在processData中自行完成。
//本模型不具备同步特性，如用在多线程中，请用同步技术进行二次封装。

typedef enum {
    XF_FIFOBUFFER_STATE_NONE,
    XF_FIFOBUFFER_STATE_INIT,
    XF_FIFOBUFFER_STATE_IDLE,
    XF_FIFOBUFFER_STATE_BUSY,
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
extern uint16 XF_FIFOBufferUsedSize(XF_FIFOBuffer *fifoBuffer);
extern uint16 XF_FIFOBufferUnusedSize(XF_FIFOBuffer *fifoBuffer);

#endif

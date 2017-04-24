#ifndef __XF_FIFOBUFFER_H__
#define __XF_FIFOBUFFER_H__

//FIFOBuffer满时，将覆盖旧数据
//本模型只保证读取数据包的完整性，数据校验需在processData中自行完成。

typedef enum {
    XF_FIFOBUFFER_STATE_NONE,
    XF_FIFOBUFFER_STATE_RUN,
} XF_FIFOState;

typedef struct XF_FIFO_S {
    uint8 state;
    uint16 posHead;
    uint16 postTail;
    void *bufItems;
    uint16 sizeItem;
    uint16 countItem;
} XF_Fifo;

extern void XF_FIFOInit(XF_Fifo *fifo, void *bufItems, uint16 sizeItem, uint16 countItem);
extern uint16 XF_FIFORead(XF_Fifo *fifo, void *item);
extern uint16 XF_FIFOWrite(XF_Fifo *fifo, void *item);
extern uint16 XF_FIFOUsedSize(XF_Fifo *fifo);
extern uint16 XF_FIFOUnusedSize(XF_Fifo *fifo);

#endif

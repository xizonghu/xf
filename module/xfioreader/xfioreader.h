#ifndef __XF_IOREADER_H__
#define __XF_IOREADER_H__

//IO通信协议设计必须遵守head+body的模式，head固定长度，body为可变长度(长度由head中字段给出)
//每读到一个数据包，就触发回调函数processData。
//本模型只保证读取数据包的完整性，数据校验需在processData中自行完成。

#define private

typedef enum {
    XF_IOREADER_STATE_NONE,
    XF_IOREADER_STATE_PORTION,
    XF_IOREADER_STATE_COMPLETE,
} XF_IOReaderState;

typedef struct {
    uint16 (*readData)(int fd, void *buffer, uint16 size);
    uint16 (*getBodySize)(void *head, uint16 size);
    void (*setTimeout)();
    uint8 (*isTimeout)();
} XF_IOReaderIf;

typedef struct {
    void (*processData)(void *buffer, uint16 size);
} XF_IOReaderCb;

typedef struct {
    int fd;
    uint8 state;
    uint16 posBuffer;
    void *buffer;
    uint16 sizeBuffer;
    uint8 sizeHead;
    const XF_IOReaderIf *IF;
    const XF_IOReaderCb *CB;
} XF_IOReader;

extern void XF_IOReaderInit(XF_IOReader *reader, void *buffer, uint16 sizeBuffer, uint8 sizeHead, int fd, const XF_IOReaderIf *IF, const XF_IOReaderCb *CB);
extern void XF_IOReaderScan(XF_IOReader *reader);

#endif
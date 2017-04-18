#ifndef __XF_IOREADER_H__
#define __XF_IOREADER_H__

//IO通信协议设计必须遵守head+body的模式，head固定长度，body为可变长度(长度由head中字段给出)
//本模型只保证读取数据包的完整性，数据校验需在processData中自行完成。

#define private

typedef enum {
    XF_IOREADER_STATE_NONE,
    XF_IOREADER_STATE_PORTION,
    XF_IOREADER_STATE_COMPLETE,
} XF_IOReaderState;

typedef struct {
    uint16 (*readData)(void *buffer, uint16 size);
    uint16 (*getBodySize)(void *head);
    void (*setTimeout)();
    uint8 (*isTimeout)();
} XF_IOReaderIf;

typedef struct {
    void (*processData)(void *buffer, uint16 size);
} XF_IOReaderCb;

typedef struct {
    uint8 state;
    uint16 posBuffer;
    const void *buffer;
    const uint16 sizeBuffer;
    const uint8 sizeHeadBuffer;
    const XF_IOReaderIf *IF;
    const XF_IOReaderCb *CB;
} XF_IOReader;

extern void XF_IOReaderInit(XF_IOReader *reader,       const XF_IOReaderIf *IF, const XF_IOReaderCb *CB);
extern void XF_IOReaderScan(XF_IOReader *reader);

#endif
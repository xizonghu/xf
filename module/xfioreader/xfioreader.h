#ifndef __XF_IOREADER_H__
#define __XF_IOREADER_H__

//IOͨ��Э����Ʊ�������head+body��ģʽ��head�̶����ȣ�bodyΪ�ɱ䳤��(������head���ֶθ���)
//��ģ��ֻ��֤��ȡ���ݰ��������ԣ�����У������processData��������ɡ�

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
#ifndef __XF_IOREADER_H__
#define __XF_IOREADER_H__

//IOͨ��Э����Ʊ�������head+body��ģʽ��head�̶����ȣ�bodyΪ�ɱ䳤��(������head���ֶθ���)
//ÿ����һ�����ݰ����ʹ����ص�����processData��
//��ģ��ֻ��֤��ȡ���ݰ��������ԣ�����У������processData��������ɡ�

#define private

typedef enum {
    XF_IOREADER_STATE_NONE,
    XF_IOREADER_STATE_PORTION,
    XF_IOREADER_STATE_COMPLETE,
} XF_IOReaderState;

//ģ���������Ľӿں����������ʵ���������ʵ��
typedef struct {
    uint16 (*readData)(int fd, char *buffer, uint16 size);  //
    uint16 (*getBodySize)(char *head, uint16 size);
    void (*setTimeout)();
    uint8 (*isTimeout)();
} XF_IOReaderIf;

//�ص�����
typedef struct {
    void (*processData)(char *buffer, uint16 size);
} XF_IOReaderCb;

typedef struct {
    int fd;
    uint8 state;
    uint16 posBuffer;
    char *buffer;
    uint16 sizeBuffer;
    uint8 sizeHead;
    const XF_IOReaderIf *IF;
    const XF_IOReaderCb *CB;
} XF_IOReader;

extern void XF_IOReaderInit(XF_IOReader *reader, char *buffer, uint16 sizeBuffer, uint8 sizeHead, int fd, const XF_IOReaderIf *IF, const XF_IOReaderCb *CB);
extern void XF_IOReaderPoll(XF_IOReader *reader);

#endif
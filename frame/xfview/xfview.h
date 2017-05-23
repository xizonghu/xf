#ifndef __XF_VIEW_H__
#define __XF_VIEW_H__

//����xfbgraph, xfmalloc��һ�׵�ɫUI��
//������xfevent��Ϲ���ϵͳ

typedef enum XF_VIEW_MESSAGE_TYPE_E {
    XF_VIEW_EVENT_FOCUS_NEXT = 1,
    XF_VIEW_EVENT_FOCUS_PREV,
    XF_VIEW_EVENT_SELECT,
    XF_VIEW_EVENT_QUIT,
} XF_ViewMessageType;

typedef struct XF_VIEW_MESSAGE_S {
    uint8 type;
    uint8 value;
} XF_ViewMessage;

//��ܽӿ�
extern void XF_ViewStart(XF_VIEW_Layout *layout);   //��һ������
extern void XF_ViewStop(XF_VIEW_Layout *layout);    //�ر�һ������

//���¼�ʱ�Ĵ�����
extern void XF_ViewActionHandler(uint8 msg);

#endif

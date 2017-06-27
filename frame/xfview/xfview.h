#ifndef __XF_VIEW_H__
#define __XF_VIEW_H__

#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"

//����xfbgraph, xfmalloc(�ɽ���xfmalloc�йصĺ���������һ��c�ļ���ʵ��)��һ�׵�ɫUI��
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
extern void XF_ViewMain(XF_VIEW_Layout *layout);    //������
extern void XF_ViewStart(XF_VIEW_Layout *layout);   //�´�һ������
extern void XF_ViewGoto(XF_VIEW_Layout *layout);    //�˳���ǰlayout,�´�һ������
extern void XF_ViewFocusUnit(XF_VIEW_Unit *unit);   //�۽�һ��unit
extern void XF_ViewSetVisiable(XF_VIEW_Unit *unit, uint8 visiable); //����һ��unit�Ƿ�ɼ�

extern void XF_ViewRefesh();        //ˢ��
//extern void XF_ViewDestroy();  //���ٵ�ǰlayout
extern void XF_ViewQuit();  //�˳��õ�ǰlayout�����ظ�layout
extern void XF_ViewFinish();        //�ͷ�����view��Դ���˳�

extern XF_VIEW_Unit *XF_ViewGetElementBySeq(uint8 seq);  //ͨ������layout�Ĵ����ȡunit,Ϊ�˼���unitȫ�ֱ�����ʹ��
extern XF_VIEW_Unit *XF_ViewGetElementById(char *id);   //ͨ��id��ȡҳ�沿��,Ϊ�˼���unitȫ�ֱ�����ʹ��,��δʵ��


//���¼�ʱ�Ĵ�����
extern void XF_ViewActionHandler(uint8 msg);

#endif

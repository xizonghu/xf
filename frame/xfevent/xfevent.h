#ifndef __XF_EVENT_H__
#define __XF_EVENT_H__

//EventHandler�¼������������ڴ����¼���
//Event�¼��������Handler,��Event����ʱ��ͨ��EventHandler�Ļص�����EventHandlerReceiver����EventInfoЯ������Ϣ�͵���ע�ᵽ��Event�ϵ�EventHandler
//EventContainer��Event����������ѯ����Event�Ƿ�����
//������ʵ��Event�����ķ�ʽ��һ�����������д���һ��Event���飬��һ�����������д���һ��Event����
//Ϊ�˽ṹ�򵥣�������malloc��������Event���ݽṹ�м�����next���ԣ�ʹ֮��Ϊ����ڵ㣬����ֻ����ͷ�ڵ㡣
//���ǵ���ʱ���¼��������ж�����ģ�����ĳ����������ģ��������EventPoller�¼���ѯ����������poll���ж�������������������򴥷�XF_EventNotify��poll������ʵ��

typedef enum XF_EVENT_STATE_E {
    XF_EVENT_STATE_LISTEN,
    XF_EVENT_STATE_NOTIFY,
    XF_EVENT_STATE_PROCESS,
} XF_EventState;

typedef struct XF_EVENT_INFO_S {
    uint8 type;
    void *arg;
} XF_EventInfo;

typedef struct XF_EVENT_HANDLER_S {
    void (*onEventReceiver)(XF_EventInfo *info);
    struct XF_EVENT_HANDLER_S *next;
} XF_EventHandler;

typedef struct XF_EVENT_POLLER_S {
    void (*poll)(void);
    struct XF_EVENT_POLLER_S *next;
} XF_EventPoller;

typedef struct XF_EVENT_S {
    uint8 state;
    XF_EventInfo info;
    XF_EventHandler *HeadHandler;
    struct XF_EVENT_S *next;
} XF_Event;

typedef struct {
    XF_Event *head;
} XF_EventList;


extern int8 XF_EventAddHandler(XF_Event *evt, XF_EventHandler *handler);

extern int8 XF_EventRemoveHandler(XF_Event *evt, XF_EventHandler *handler);

extern void XF_EventNotify(XF_Event *evt, XF_EventInfo *info);

extern uint8 XF_EventProcess(XF_Event *evt, XF_EventInfo *info);

extern void XF_EventPolling(XF_Event *evt);

void XF_EventPollerAdd(XF_EventPoller *head, XF_EventPoller *poller);
void XF_EventPollerPoll(XF_EventPoller *poller);

extern void XF_EventListAddEvent(XF_EventList *list, XF_Event *evt);
extern int8 XF_EventPollerRemove(XF_EventPoller *head, XF_EventPoller *poller);

extern void XF_EventListPolling(XF_EventList *list);    //���������ѭ����,һֱ��ѯEvent��״̬

//��֧��malloc�ſ�ʹ��
extern XF_Event *XF_EventNew(XF_EventHandler *h);
extern void XF_EventDelete(XF_Event *e);
#endif

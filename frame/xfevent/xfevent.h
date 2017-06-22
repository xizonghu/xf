#ifndef __XF_EVENT_H__
#define __XF_EVENT_H__

//EventHandler事件处理器，用于处理事件。
//Event事件包含多个Handler,当Event发送时，通过EventHandler的回调函数EventHandlerReceiver，将EventInfo携带的信息送到各注册到该Event上的EventHandler
//EventContainer是Event的容器，轮询检测各Event是否发生。
//有两种实现Event容器的方式，一种是在容器中创建一个Event数组，另一种是在容器中创建一个Event链表。
//为了结构简单，不引入malloc依赖，在Event数据结构中加入了next属性，使之成为链表节点，容器只保存头节点。
//考虑到有时候事件不是由中断引起的，而是某个条件引起的，因此引入EventPoller事件查询器，在它的poll中判断条件，如果条件发生则触发XF_EventNotify。poll需自行实现

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

extern void XF_EventListPolling(XF_EventList *list);    //必须放在主循环中,一直查询Event的状态

//需支持malloc才可使用
extern XF_Event *XF_EventNew(XF_EventHandler *h);
extern void XF_EventDelete(XF_Event *e);
#endif

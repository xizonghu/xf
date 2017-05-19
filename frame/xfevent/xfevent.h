#ifndef __XF_EVENT_H__
#define __XF_EVENT_H__

//EventHandler事件处理器，用于处理事件。
//Event事件包含多个Handler,当Event发送时，通过EventHandler的回调函数EventHandlerReceiver，将EventInfo携带的信息送到各注册到该Event上的EventHandler
//EventContainer是Event的容器，轮询检测各Event是否发生。

typedef enum XF_EVENT_STATE_E {
    XF_EVENT_STATE_LISTEN,
    XF_EVENT_STATE_NOTIFY,
    XF_EVENT_STATE_PROCESS,
} XF_EventState;

typedef struct XF_EVENT_INFO_S {
    uint8 type;
    void *arg;
} XF_EventInfo;

typedef void (*XF_EventHandlerReceiver)(XF_EventInfo *info);

typedef struct {
    const char *name;
    XF_EventHandlerReceiver onEventReceiver;
} XF_EventHandler;


typedef struct {
    uint8 state;
    XF_EventInfo info;
    XF_EventHandler **handlers;
    uint8 sizeHandler;
} XF_Event;

typedef struct {
    XF_Event **events;
    uint8 sizeEvent;
} XF_EventContainer;

extern XF_Event *XF_EventNew(uint8 sizeHandler);
extern void XF_EventDelete(XF_Event *event);

extern int8 XF_EventAddHandler(XF_Event *evt, XF_EventHandler *handler);

extern int8 XF_EventRemoveHandler(XF_Event *evt, XF_EventHandler *handler);

extern void XF_EventNotify(XF_Event *evt, XF_EventInfo *info);

extern uint8 XF_EventProcess(XF_Event *evt, XF_EventInfo *info);

extern void XF_EventContainerPolling(XF_EventContainer *container);  //必须放在主while(1)中,整个系统只有这一处不可跳出的循环

#endif

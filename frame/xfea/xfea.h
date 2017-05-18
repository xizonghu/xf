#ifndef __XF_EA_H__
#define __XF_EA_H__

//EA需要修改，EA中，携带的消息为event{id:uint8, arg: void*}，不用搞消息的队列存储，消息队列有专门的模块xffifo。
//
//typedef void *XF_Info;

typedef struct XF_EVENT_INFO_S{
    uint8 id;
    void *arg;
} XF_EventInfo;

typedef void (*XF_action_handler_callback)(XF_Info *info);

typedef struct {
    const char *name;
    XF_action_handler_callback handler;
} XF_EventHandler;

typedef enum {
    XF_EVENY_TYPE_INTERRUPT = (uint8)1,
    XF_EVENY_TYPE_QUERY,
} XF_EventType;

typedef void (*XF_event_query_callback)(void);

typedef struct {
    XF_EventType type;
    XF_event_query_callback query;
    XF_Action **actions;
    uint8 sizeActions;
    XF_Info *infos;
    uint8 sizeInfos;
    uint8 posInfos;
} XF_Event;

typedef struct {
    XF_Action *events;  //指向队列首地址
    void *dataBuf;  //指向数据首地址
    uint8 size;
} XF_EventQueue;

typedef struct {
    XF_Event **events;
    uint8 size;
} XF_EventPackage;

extern void XF_EventCreate(XF_Event *evt, XF_EventType type, XF_event_query_callback query, XF_Info infos[], XF_Memory dataInfos[], uint8 sizeInfos, XF_Action *actions[], uint8 sizeActions);

extern int8 XF_EventAddAct(XF_Event *evt, XF_Action *act);

extern int8 XF_EventRemoveAct(XF_Event *evt, XF_Action *act);

extern void XF_EventNotifyActSync(XF_Event *evt, XF_Info *info);

extern void XF_EventNotifyActAsyn(XF_Event *evt, XF_Info *info);

extern uint8 XF_EventExecuteAct(XF_Event *evt);

extern uint8 XF_EventPackageDispatch(XF_EventPackage evtPkg);

extern void XF_EventPackageQuery(XF_EventPackage evtPkg);

extern void XF_EventPackageLoopRun(XF_EventPackage evtPkg);

#endif

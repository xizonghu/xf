#ifndef __XF_EAF_H__
#define __XF_EAF_H__

//typedef void *XF_Info;

typedef struct {
    void *data;
    int size;
} XF_Info;

typedef void (*XF_action_handler_callback)(XF_Info *info);

typedef struct {
    const char *name;
    XF_action_handler_callback handler;
} XF_Action;

typedef enum {
    XF_EVENY_TYPE_INTERRUPT = (uint8_t)1,
    XF_EVENY_TYPE_QUERY,
} XF_EventType;

typedef void (*XF_event_query_callback)(void);

typedef struct {
    XF_EventType type;
    XF_event_query_callback query;
    XF_Action **actions;
    uint8_t sizeActions;
    XF_Info *infos;
    uint8_t sizeInfos;
    uint8_t posInfos;
} XF_Event;

typedef struct {
    XF_Action *events;  //指向队列首地址
    void *dataBuf;  //指向数据首地址
    uint8_t size;
} XF_EventQueue;

typedef struct {
    XF_Event **events;
    uint8_t size;
} XF_EventPackage;

extern void XF_EventCreate(XF_Event *evt, XF_EventType type, XF_event_query_callback query, XF_Info infos[], XF_Memory dataInfos[], uint8_t sizeInfos, XF_Action *actions[], uint8_t sizeActions);

extern int8_t XF_EventAddAct(XF_Event *evt, XF_Action *act);

extern int8_t XF_EventRemoveAct(XF_Event *evt, XF_Action *act);

extern void XF_EventNotifyActSync(XF_Event *evt, XF_Info *info);

extern void XF_EventNotifyActAsyn(XF_Event *evt, XF_Info *info);

extern uint8_t XF_EventExecuteAct(XF_Event *evt);

extern uint8_t XF_EventPackageDispatch(XF_EventPackage evtPkg);

extern void XF_EventPackageQuery(XF_EventPackage evtPkg);

extern void XF_EventPackageLoopRun(XF_EventPackage evtPkg);

#endif

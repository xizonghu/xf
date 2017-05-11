#include <string.h>

#include "xftypedef.h"
#include "xfevent.h"

static int8 indexOf(XF_Event *evt, XF_EventHandler *handler) {
    uint8 i = 0;
    for(i = 0; i < evt->sizeHandler; i++) {
        XF_EventHandler *p;
		p = evt->handlers[i];
		if(0 == p) continue;
        if(0 == strcmp(p->name, handler->name)) {
            return (int8)i;
        }
    }
    return -1;
}

int8 XF_EventAddHandler(XF_Event *evt, XF_EventHandler *handler) {
    uint8 i = 0;
    if(0 <= indexOf(evt, handler)) {
        return -1;
    }

    for(i = 0; i < evt->sizeHandler; i++) {
        if(0 == evt->handlers[i]) {
            evt->handlers[i] = handler;
            return 0;
        }
    }

    return -2;
}

int8 XF_EventRemoveHandler(XF_Event *evt, XF_EventHandler *handler) {
    int8 i = 0;
    if(0 > (i = indexOf(evt, handler))) return -1;
    evt->handlers[i] = 0;

    return 0;
}

void XF_EventNotify(XF_Event *evt, XF_EventInfo *info) {
    evt->info = *info;
    evt->state = XF_EVENT_STATE_NOTIFY;
}

uint8 XF_EventProcess(XF_Event *evt, XF_EventInfo *info) {
    uint8 i = 0;

    evt->state = XF_EVENT_STATE_PROCESS;
    for(i = 0; i < evt->sizeHandler; i++) {
        XF_EventHandler *handler;
        handler = evt->handlers[i];
        if(XF_NULL == handler) continue;
        if(XF_NULL == handler->onEventReceiver) continue;
        handler->onEventReceiver(info);
    }
    evt->state = XF_EVENT_STATE_LISTEN;
    return 0;
}

void XF_EventContainerPolling(XF_EventContainer *container) {
    uint8 pos = 0;

    for (pos = 0; pos < container->sizeEvent; pos++) {
        XF_Event *evt = container->events[pos];
        if (XF_EVENT_STATE_NOTIFY == evt->state) {
            XF_EventProcess(evt, &evt->info);
        }
    }
}

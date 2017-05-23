#include <string.h>

#include "xftypedef.h"
#include "xfmalloc.h"
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

XF_Event *XF_EventNew(uint8 sizeHandler) {
    XF_Event *evt = XF_NULL;
    XF_EventHandler **handlers = XF_NULL;
    if (XF_NULL == (evt = (XF_Event*)XF_malloc(sizeof(XF_Event)))) return XF_NULL;
    if (XF_NULL == (handlers = (XF_EventHandler**)XF_malloc(sizeof(XF_EventHandler) * sizeHandler))) {
        XF_free(evt);
        return XF_NULL;
    }

    evt->handlers = handlers;
    evt->state = XF_EVENT_STATE_LISTEN;
    return evt;
}

void XF_EventDelete(XF_Event *event) {
    XF_free(event->handlers);
    XF_free(event);
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
    evt->state = (uint8)XF_EVENT_STATE_NOTIFY;
}

uint8 XF_EventProcess(XF_Event *evt, XF_EventInfo *info) {
    uint8 i = 0;

    evt->state = (uint8)XF_EVENT_STATE_PROCESS;
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

void XF_EventPolling(XF_Event *evt) {
    if (XF_EVENT_STATE_NOTIFY == evt->state) {
        XF_EventProcess(evt, &evt->info);
    }
}

void XF_EventContainerPolling(XF_EventContainer *container) {
    uint8 pos = 0;

    for (pos = 0; pos < container->sizeEvent; pos++) {
        XF_EventPolling(container->events[pos]);
    }
}

#include "xftypedef.h"
#include "xfevent.h"

/*static int8 indexOf(XF_Event *evt, XF_EventHandler *handler) {
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
}*/

int8 XF_EventAddHandler(XF_Event *evt, XF_EventHandler *handler) {
    XF_EventHandler *pos = XF_NULL;

    if (XF_NULL == evt || XF_NULL == handler) return -1;

    if(XF_NULL == evt->HeadHandler) {
        evt->HeadHandler = handler;
        handler->next = XF_NULL;
        return 0;
    }

    for (pos = evt->HeadHandler; XF_NULL != pos->next; pos = pos->next);
    pos->next = handler;
    handler->next = XF_NULL;

    return 0;
}

int8 XF_EventRemoveHandler(XF_Event *evt, XF_EventHandler *handler) {
    XF_EventHandler *prev = XF_NULL;

    if (XF_NULL == evt || XF_NULL == handler) return -1;
    if (XF_NULL == evt->HeadHandler) return -2;
    if (evt->HeadHandler == handler) {
        evt->HeadHandler = evt->HeadHandler->next;
        handler->next = XF_NULL;
        return 0;
    }

    for (prev = evt->HeadHandler; prev->next != XF_NULL && prev->next != handler; prev = prev->next);
    if (XF_NULL == prev->next) return -3;

    if (handler == prev->next) {
        prev->next = prev->next->next;
        handler->next = XF_NULL;
        return 0;
    }

    return 0;
}

void XF_EventNotify(XF_Event *evt, XF_EventInfo *info) {
    evt->info = *info;
    evt->state = (uint8)XF_EVENT_STATE_NOTIFY;
}

uint8 XF_EventProcess(XF_Event *evt, XF_EventInfo *info) {
    XF_EventHandler *handler = XF_NULL;

    if (XF_NULL == evt) return -1;

    evt->state = (uint8)XF_EVENT_STATE_PROCESS;
    for(handler = evt->HeadHandler; XF_NULL != handler; handler = handler->next) {
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

void XF_EventListAddEvent(XF_EventList *list, XF_Event *evt) {
    XF_Event *head = XF_NULL;

    if (XF_NULL == list || XF_NULL == evt) return;
    if (evt == list->head) return;

    if (XF_NULL == list->head) {
        list->head = evt;
        evt->next = XF_NULL;
    }

    for (head = list->head; XF_NULL != head->next; head = head->next) if (head->next == evt) return;

    head->next = evt;
    evt->next = XF_NULL;
    return;
}

void XF_EventListPolling(XF_EventList *list) {
    XF_Event *evt = XF_NULL;

    if (XF_NULL == list) return;
    for (evt = list->head; XF_NULL != evt; evt = evt->next) XF_EventPolling(evt);
    return;
}

void XF_EventPollerAdd(XF_EventPoller *head, XF_EventPoller *poller) {
    XF_EventPoller *prev = XF_NULL;
    if (XF_NULL == head || XF_NULL == poller) return;
    if (poller == head) return;

    for (prev = head; XF_NULL != prev->next; prev = prev->next) if (prev->next == poller) return;
    prev->next = poller;
    poller->next = XF_NULL;
}

int8 XF_EventPollerRemove(XF_EventPoller *head, XF_EventPoller *poller) {
    XF_EventPoller *prev = XF_NULL;

    if (XF_NULL == head || XF_NULL == poller) return -1;

    if (head == poller) {
        head = head->next;
        poller->next = XF_NULL;
        return 0;
    }

    for (prev = head; prev->next != XF_NULL && prev->next != poller; prev = prev->next);
    if (XF_NULL == prev->next) return -2;

    if (poller == prev->next) {
        prev->next = prev->next->next;
        poller->next = XF_NULL;
        return 0;
    }

    return 0;
}

void XF_EventPollerPoll(XF_EventPoller *poller) {
    for (; XF_NULL != poller; poller = poller->next) {
        if (poller->poll) poller->poll();
    }
}

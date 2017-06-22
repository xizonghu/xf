#include "xftypedef.h"
#include "xfmalloc.h"
#include "xfevent.h"

XF_Event *XF_EventNew(XF_EventHandler *h) {
    XF_Event *event = XF_NULL;
    if (XF_NULL == (event = XF_malloc(sizeof(XF_Event)))) return XF_NULL;
    event->state = XF_EVENT_STATE_LISTEN;
    event->HeadHandler = h;
    event->next = XF_NULL;
}

void XF_EventDelete(XF_Event *e) {
    XF_free(e);
}


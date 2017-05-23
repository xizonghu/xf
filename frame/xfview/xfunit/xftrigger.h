#ifndef __XF_TRIGGER_H__
#define __XF_TRIGGER_H__

typedef struct XF_VIEW_TRIGGER_S {
    XF_VIEW_Unit super;
    void (*onTrigger)(void *arg);
} XF_VIEW_Trigger;

extern XF_VIEW_Trigger *XF_VIEW_TriggerNew(attr x, attr y, void (*onTrigger)(void *arg));
extern void XF_VIEW_TriggerDelete(XF_VIEW_Trigger *trigger);

#endif

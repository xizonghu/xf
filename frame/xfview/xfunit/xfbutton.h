#ifndef __XF_BUTTON_H__
#define __XF_BUTTON_H__

typedef struct XF_VIEW_BUTTON_S {
    XF_VIEW_Unit super;
    char *name;
    void (*click)(void *arg);
} XF_VIEW_Button;

extern void XF_VIEW_ButtonSetName(XF_VIEW_Button *button, char *name);
extern XF_VIEW_Button *XF_VIEW_ButtonNew(attr x, attr y, const char *name, void (*onClick)(void *arg));
extern void XF_VIEW_ButtonDelete(XF_VIEW_Button *button);

#endif

#ifndef __XF_INPUTKEY_H__
#define __XF_INPUTKEY_H__

typedef struct XF_VIEW_INPUTKEY_S {
    XF_VIEW_Unit super;
    void (*onPressKey)(char ch);
} XF_VIEW_InputKey;

extern XF_VIEW_InputKey *XF_VIEW_InputKeyNew(void (*onPressKey)(char ch));
extern void XF_VIEW_InputKeyDelete(XF_VIEW_InputKey* inputkey);

#endif

#ifndef __XF_TEXTEDIT_H__
#define __XF_TEXTEDIT_H__

typedef enum XF_VIEW_TEXTEDIT_TYPE_E {
    XF_VIEW_TEXTEDIT_TYPE_CHAR = (attr)0,
    XF_VIEW_TEXTEDIT_TYPE_PASSWD,
} XF_VIEW_TexteditType;

typedef enum XF_VIEW_TEXTEDIT_STATE_E {
    XF_VIEW_TEXTEDIT_STATE_INPUT = 1,
    XF_VIEW_TEXTEDIT_STATE_COMPLETE = 2,
    XF_VIEW_TEXTEDIT_STATE_BREAK = 3,
} XF_VIEW_TEXTEDIT_STATE_T;

typedef struct XF_VIEW_TEXTEDIT_S {
    XF_VIEW_Unit super;
    attr type;
    char *val;
    attr size;
    attr pos;
    void (*onStateChange)(uint8 state, char *val);
} XF_VIEW_TextEdit;

extern XF_VIEW_TextEdit *XF_VIEW_TextEditNew(attr x, attr y, attr type, uint8 size, void (*onStateChange)(uint8 state, char *val));
extern void XF_VIEW_TextEditDelete(XF_VIEW_TextEdit *text);

extern char *XF_VIEW_TextEditGetValue(XF_VIEW_TextEdit *text);
extern void XF_VIEW_TextEditSetValue(XF_VIEW_TextEdit *text, char *val);

#endif

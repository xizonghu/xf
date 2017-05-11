#ifndef __XF_TEXT_H__
#define __XF_TEXT_H__

typedef enum XF_VIEW_TEXT_TYPE_E {
    XF_VIEW_TEXT_TYPE_CHAR = (attr)0,
    XF_VIEW_TEXT_TYPE_PASSWD,
} XF_VIEW_TextType;

typedef struct XF_VIEW_TEXT_S {
    XF_VIEW_Unit super;
    XF_VIEW_TextType type;
    char *name;
    attr size;
    attr pos;
} XF_VIEW_Text;

extern XF_VIEW_Text *XF_VIEW_TextNew(attr x, attr y, attr type, uint8 size);
extern void XF_VIEW_TextDelete(XF_VIEW_Text *text);

#endif

#ifndef __XF_TEXTLIST_H__
#define __XF_TEXTLIST_H__

typedef enum XF_VIEW_TEXTLIST_EVENT_TYPE_E {
    XF_VIEW_TEXTLIST_EVENT_TYPE_SCROLL_UP = 1,
    XF_VIEW_TEXTLIST_EVENT_TYPE_SCROLL_DOWN = 2,
    XF_VIEW_TEXTLIST_EVENT_TYPE_PAGE_UP = 3,
    XF_VIEW_TEXTLIST_EVENT_TYPE_PAGE_DOWN = 4,
    XF_VIEW_TEXTLIST_EVENT_TYPE_SELECT = 5,
    XF_VIEW_TEXTLIST_EVENT_TYPE_UNSELECT = 6,
} XF_VIEW_TEXTLIST_EVENT_T;

typedef struct XF_VIEW_TEXTLIST_EVENT_S {
    attr type;
    void *arg;
} XF_VIEW_TextListEvent;

typedef struct XF_VIEW_TEXTLIST_UNIT_S {
    char *val;
    struct XF_VIEW_TEXTLIST_UNIT_S *next;
} XF_VIEW_TextListUnit;

typedef struct XF_VIEW_TEXTLIST_S {
    XF_VIEW_Unit super;
    char *values;
    attr sizeValue;
    attr countValue;
    attr posValue;
    void (*onEvent)(XF_VIEW_TextListEvent *evt);
} XF_VIEW_TextList;

extern XF_VIEW_TextList *XF_VIEW_TextListNew(attr x, attr y, attr sizeValue, attr countValue, void (*onEvent)(XF_VIEW_TextListEvent *evt));
extern void XF_VIEW_TextListDelete(XF_VIEW_TextList *dt);
extern int8 XF_VIEW_TextListSetVal(XF_VIEW_TextList * tl, uint8 pos, char *val);

#endif

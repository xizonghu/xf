#ifndef __XF_LIST_H__
#define __XF_LIST_H__

typedef enum {
    VIEW_LIST_TYPE_OPTION = (attr)0,
    VIEW_LIST_TYPE_SUMBIT,
} VIEW_ListType;

typedef struct XF_VIEW_LIST_UNIT_S {
    char *name;
    struct XF_VIEW_LIST_UNIT_S *parent;
    struct XF_VIEW_LIST_UNIT_S *child;
    struct XF_VIEW_LIST_UNIT_S *brother;
    attr pos;
    void (*onSelect)(void *arg);
} XF_VIEW_ListUnit;

typedef struct XF_VIEW_LIST_S {
    XF_VIEW_Unit super;
    XF_VIEW_ListUnit *root;
    XF_VIEW_ListUnit *head;
    attr sizeCursor;
    attr posCursor;
} XF_VIEW_List;

extern XF_VIEW_List *XF_VIEW_ListNew(attr x, attr y, XF_VIEW_ListUnit *root, attr sizeCursor);
extern void XF_VIEW_ListDelete(XF_VIEW_List *list);

extern XF_VIEW_ListUnit *XF_VIEW_ListUnitNew(const char *name, void (*onSelect)(void *arg));
extern void XF_VIEW_ListUnitDelete(XF_VIEW_ListUnit *listunit);

extern void XF_VIEW_ListUnitAddBrother(XF_VIEW_ListUnit *listunit, XF_VIEW_ListUnit *brother);
extern void XF_VIEW_ListUnitAddChild(XF_VIEW_ListUnit *listunit, XF_VIEW_ListUnit *child);

#endif

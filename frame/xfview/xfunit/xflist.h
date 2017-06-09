#ifndef __XF_LIST_H__
#define __XF_LIST_H__

typedef struct XF_VIEW_LIST_UNIT_S {
    char *val;
    struct XF_VIEW_LISTTREE_UNIT_S *next;
} XF_VIEW_ListUnit;

typedef struct XF_VIEW_LIST_S {
    XF_VIEW_Unit super;
    XF_VIEW_ListUnit *head;
    attr sizeCursor;
    attr posCursor;
    attr posCursorBase;
    void (*onSelect)(char *val);
} XF_VIEW_List;

extern XF_VIEW_List *XF_VIEW_ListNew(attr x, attr y, attr sizeCursor, void (*onSelect)(char *val));
extern void XF_VIEW_ListDelete(XF_VIEW_List *tt);

extern XF_VIEW_ListUnit *XF_VIEW_ListUnitNew(char *val);
extern void XF_VIEW_ListUnitDelete(XF_VIEW_ListUnit *ttunit);

extern int8 XF_VIEW_ListAddUnit(XF_VIEW_List *tt, XF_VIEW_ListUnit *ttunit);
extern int8 XF_VIEW_ListRemoveUnit(XF_VIEW_List *tt, XF_VIEW_ListUnit *ttunit);

#endif

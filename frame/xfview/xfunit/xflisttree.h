#ifndef __XF_LISTTREE_H__
#define __XF_LISTTREE_H__

typedef struct XF_VIEW_LISTTREE_UNIT_S {
    char *val;
    struct XF_VIEW_LISTTREE_UNIT_S *parent;
    struct XF_VIEW_LISTTREE_UNIT_S *child;
    struct XF_VIEW_LISTTREE_UNIT_S *brother;
    attr pos;
} XF_VIEW_ListTreeUnit;

typedef struct XF_VIEW_LISTTREE_S {
    XF_VIEW_Unit super;
    XF_VIEW_ListTreeUnit *root;
    XF_VIEW_ListTreeUnit *head;
    attr sizeCursor;
    attr posCursor;
    void (*onSelect)(char *val);
} XF_VIEW_ListTree;

extern XF_VIEW_ListTree *XF_VIEW_ListTreeNew(attr x, attr y, XF_VIEW_ListTreeUnit *root, attr sizeCursor, void (*onSelect)(char *val));
extern void XF_VIEW_ListTreeDelete(XF_VIEW_ListTree *list);

extern XF_VIEW_ListTreeUnit *XF_VIEW_ListTreeUnitNew(const char *val);
extern void XF_VIEW_ListTreeUnitDelete(XF_VIEW_ListTreeUnit *listunit);

extern void XF_VIEW_ListTreeUnitAddBrother(XF_VIEW_ListTreeUnit *listunit, XF_VIEW_ListTreeUnit *brother);
extern void XF_VIEW_ListTreeUnitAddChild(XF_VIEW_ListTreeUnit *listunit, XF_VIEW_ListTreeUnit *child);

#endif

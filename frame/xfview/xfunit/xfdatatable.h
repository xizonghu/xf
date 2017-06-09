#ifndef __XF_DATATABLE_H__
#define __XF_DATATABLE_H__

typedef enum XF_VIEW_DATATABLE_SCROLL_E {
    XF_VIEW_DATATABLE_SCROLL_UP = 1,
    XF_VIEW_DATATABLE_SCROLL_DOWN = 2,
    XF_VIEW_DATATABLE_SCROLL_PAGE_UP = 3,
    XF_VIEW_DATATABLE_SCROLL_PAGE_DOWN = 4,
} XF_VIEW_DATATABLE_SCROLL_T;

typedef struct XF_VIEW_DATATABLE_UNIT_S {
    char *val;
    struct XF_VIEW_DATATABLE_UNIT_S *next;
} XF_VIEW_DataTableUnit;

typedef struct XF_VIEW_DATATABLE_S {
    XF_VIEW_Unit super;
    XF_VIEW_DataTableUnit *listUnit;
    XF_VIEW_DataTableUnit *posUnit;
    attr sizeCursor;
    attr posCursor;
    void (*onSelect)(char *val);
    void (*onScroll)(uint8 scroll);
} XF_VIEW_DataTable;

extern XF_VIEW_DataTable *XF_VIEW_DataTableNew(attr x, attr y, XF_VIEW_DataTableUnit *listUnit, attr sizeCursor, void (*onSelect)(char *val), void (*onScroll)(uint8 scroll));
extern void XF_VIEW_DataTableDelete(XF_VIEW_DataTable *dt);

extern XF_VIEW_DataTableUnit *XF_VIEW_DataTableUnitNew(char *val);
extern void XF_VIEW_DataTableUnitDelete(XF_VIEW_DataTableUnit *dtunit);

extern int8 XF_VIEW_DataTableAddUnit(XF_VIEW_DataTable *dt, XF_VIEW_DataTableUnit *dtunit);
extern int8 XF_VIEW_DataTableRemoveUnit(XF_VIEW_DataTable *dt, XF_VIEW_DataTableUnit *dtunit);

#endif

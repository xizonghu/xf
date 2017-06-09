#include "xftypedef.h"
#include "xfbgraph.h"
#include "xftextout.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xfdatatable.h"

static XF_VIEW_DataTableUnit *dt_get_unit(XF_VIEW_DataTable *dt, attr pos) {
    XF_VIEW_DataTableUnit *posUnit = XF_NULL;
    uint8 posTemp = 0;

    if (XF_NULL == dt) return XF_NULL;

    for (posUnit = dt->listUnit, posTemp = 0; posUnit != XF_NULL && posTemp < pos; posUnit = posUnit->next, posTemp++);

    if (posTemp == pos) return posUnit;

    return XF_NULL;
}

static void dt_show(XF_VIEW_DataTable *dt) {
    char strNull[] = "                ";
    uint8 pos = 0;
    uint8 x = dt->super.point.x, y = dt->super.point.y;
    XF_VIEW_DataTableUnit *curr = XF_NULL;

    for(curr = dt->listUnit, pos = 0; XF_NULL != curr && pos < dt->sizeCursor; curr = curr->next, pos++) {
        XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, strNull, XF_BGRAPH_FILL_NORMAL);
        if(XF_NULL == curr) continue;

        if(pos == dt->posCursor) {
            XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, curr->val, XF_BGRAPH_FILL_REVERSE);
        } else {
            XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, curr->val, XF_BGRAPH_FILL_NORMAL);
        }
    }
    XF_BgraphFlush(&globalGraph);
}

/*static void list_delete(XF_VIEW_ListTree *list) {
}*/

static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_DataTable *dt = (XF_VIEW_DataTable*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            dt_show(dt);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            dt_show(dt);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_DataTableDelete(dt);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL: {
            switch (msg->val) {
                case XF_VIEW_UNIT_KEY_UP: {
                    if (0 == dt->posCursor) {
                        if (dt->onScroll) dt->onScroll(XF_VIEW_DATATABLE_SCROLL_UP);
                    }
                    else dt->posCursor--;
                    dt_show(dt);
                    break;
                }
                case XF_VIEW_UNIT_KEY_DOWN: {                    
                    //检查显示尾
                    if((dt->sizeCursor - 1) == dt->posCursor) {
                        if (dt->onScroll) dt->onScroll(XF_VIEW_DATATABLE_SCROLL_DOWN);
                    }
                    else dt->posCursor++;
                    dt_show(dt);
                    break;
                }
                case XF_VIEW_UNIT_KEY_ENTER: {
                    XF_VIEW_DataTableUnit *posUnit = dt_get_unit(dt, dt->posCursor);

                    if (XF_NULL == posUnit) return;
                    //检查是否有onSelect
                    if(XF_NULL != dt->onSelect) dt->onSelect(posUnit->val);
                    break;
                }
                case XF_VIEW_UNIT_KEY_BACK: {
                    if(XF_NULL != dt->onSelect) dt->onSelect(XF_NULL);
                    break;
                }
            }
            break;
        }
    }
}

XF_VIEW_DataTable *XF_VIEW_DataTableNew(attr x, attr y, XF_VIEW_DataTableUnit *listUnit, attr sizeCursor, void (*onSelect)(char *val), void (*onScroll)(uint8 scroll)) {
    XF_VIEW_DataTable *dt = (XF_VIEW_DataTable *)XF_malloc(sizeof(XF_VIEW_DataTable));

    if (XF_NULL == dt) return XF_NULL;

    dt->super.point.x = x;
    dt->super.point.y = y;
    dt->super.type = XF_VIEW_UNIT_TYPE_DATATABLE;
    dt->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    dt->super.onMessageReceiver = onMessageReceiver;
    dt->listUnit = listUnit;
    dt->posUnit = XF_NULL;
    dt->sizeCursor = sizeCursor;
    dt->posCursor = 0;
    dt->onSelect = onSelect;
    dt->onScroll = onScroll;

    return dt;
}

void XF_VIEW_DataTableDelete(XF_VIEW_DataTable *dt) {
    XF_free(dt);
}

XF_VIEW_DataTableUnit *XF_VIEW_DataTableUnitNew(char *val) {
    XF_VIEW_DataTableUnit *dtunit = (XF_VIEW_DataTableUnit *)XF_malloc(sizeof(XF_VIEW_DataTableUnit));

    if (XF_NULL == dtunit) return XF_NULL;
    dtunit->val = (char*)val;
    dtunit->next = XF_NULL;

    return dtunit;
}

void XF_VIEW_DataTableUnitDelete(XF_VIEW_DataTableUnit *dtunit) {
    XF_free(dtunit);
}

int8 XF_VIEW_DataTableAddUnit(XF_VIEW_DataTable *dt, XF_VIEW_DataTableUnit *dtunit) {
    XF_VIEW_DataTableUnit *posUnit = XF_NULL;

    if (XF_NULL == dt || XF_NULL == dtunit) return -1;
    if (XF_NULL == dt->listUnit) {
        dt->listUnit = dtunit;
        return 0;
    }

    for (posUnit = dt->listUnit; posUnit->next != XF_NULL; posUnit = posUnit->next);
    posUnit->next = dtunit;
    return 0;
}

int8 XF_VIEW_DataTableRemoveUnit(XF_VIEW_DataTable *dt, XF_VIEW_DataTableUnit *dtunit) {
    XF_VIEW_DataTableUnit *posUnit = XF_NULL;

    if (XF_NULL == dt || XF_NULL == dtunit) return -1;
    if (XF_NULL == dt->listUnit) {
        return -2;
    }

    for (posUnit = dt->listUnit; posUnit->next != XF_NULL; posUnit = posUnit->next) {
        if (posUnit->next == dtunit) {
            posUnit->next = dtunit->next;
            return 0;
        }
    }
    return -3;
}


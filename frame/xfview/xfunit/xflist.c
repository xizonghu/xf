#include "xftypedef.h"
#include "xfbgraph.h"
#include "xftextout.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xflist.h"

static uint8 tt_get_size(XF_VIEW_List *tt) {
    XF_VIEW_ListUnit *posUnit = XF_NULL;
    uint8 posTemp = 0;

    if (XF_NULL == tt || XF_NULL == tt->head) return XF_NULL;

    for (posUnit = tt->head, posTemp = 0; posUnit != XF_NULL; posUnit = posUnit->next, posTemp++);

    return posTemp;
}

static XF_VIEW_ListUnit *tt_get_unit(XF_VIEW_List *tt, attr pos) {
    XF_VIEW_ListUnit *posUnit = XF_NULL;
    uint8 posTemp = 0;

    if (0 > pos) return XF_NULL;

    if (XF_NULL == tt || XF_NULL == tt->head) return XF_NULL;

    for (posUnit = tt->head, posTemp = 0; posUnit != XF_NULL && posTemp < pos; posUnit = posUnit->next, posTemp++);

    if (posTemp == pos) return posUnit;

    return XF_NULL;
}

static XF_VIEW_ListUnit *tt_get_curr_unit(XF_VIEW_List *tt) {
    return tt_get_unit(tt, tt->posCursorBase + tt->posCursor);
}

/*static XF_VIEW_ListUnit *tt_get_prev_unit(XF_VIEW_List *tt) {
    XF_VIEW_ListUnit *uintPrev = XF_NULL;

    if (XF_NULL == tt || XF_NULL == tt->head) return XF_NULL;

    for (uintPrev = tt->head; uintPrev->next != XF_NULL; uintPrev = uintPrev->next) {
        if (uintPrev->next == tt->posCursor) break;
    }

    return uintPrev;
}*/

/*static XF_VIEW_ListUnit *tt_get_next_unit(XF_VIEW_List *tt) {
    if (XF_NULL == tt || XF_NULL == tt->posUnit) return XF_NULL;
    return tt->posUnit->next;
}*/

static void tt_show(XF_VIEW_List *tt) {
    char strNull[] = "                ";
    uint8 pos = 0;
    uint8 x = tt->super.point.x, y = tt->super.point.y;
    XF_VIEW_ListUnit *curr = XF_NULL;

    for(curr = tt_get_unit(tt, tt->posCursorBase), pos = 0; XF_NULL != curr && pos < tt->sizeCursor; curr = curr->next, pos++) {
        XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, strNull, XF_BGRAPH_FILL_NORMAL);
        if(XF_NULL == curr) continue;

        if(pos == tt->posCursor) {
            XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, curr->val, XF_BGRAPH_FILL_REVERSE);
        } else {
            XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, curr->val, XF_BGRAPH_FILL_NORMAL);
        }
    }
    XF_BgraphFlush(&globalGraph);
}

static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_List *tt = (XF_VIEW_List*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            tt_show(tt);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            tt_show(tt);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_ListDelete(tt);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL: {
            switch (msg->val) {
                case XF_VIEW_UNIT_KEY_UP: {
                    if (0 == tt->posCursor && 0 == tt->posCursorBase) break;
                    if (0 == tt->posCursor) tt->posCursorBase--;
                    else tt->posCursor--;
                    tt_show(tt);
                    break;
                }
                case XF_VIEW_UNIT_KEY_DOWN: {                    
                    if ((tt->sizeCursor - 1) <= tt->posCursor && (tt_get_size(tt) - 1) <= (tt->posCursorBase + tt->posCursor)) break;
                    if ((tt->sizeCursor - 1) == tt->posCursor) tt->posCursorBase++;
                    else tt->posCursor++;
                    tt_show(tt);
                    break;
                }
                case XF_VIEW_UNIT_KEY_ENTER: {
                    XF_VIEW_ListUnit *selected = tt_get_curr_unit(tt);
                    if (XF_NULL == selected) break;
                    if(XF_NULL != tt->onSelect) tt->onSelect(selected->val);
                    break;
                }
                case XF_VIEW_UNIT_KEY_BACK: {
                    if(XF_NULL != tt->onSelect) tt->onSelect(XF_NULL);
                    break;
                }
            }
            break;
        }
    }
}

XF_VIEW_List *XF_VIEW_ListNew(attr x, attr y, attr sizeCursor, void (*onSelect)(char *val)) {
    XF_VIEW_List *tt = (XF_VIEW_List *)XF_malloc(sizeof(XF_VIEW_List));

    if (XF_NULL == tt) return XF_NULL;

    tt->super.point.x = x;
    tt->super.point.y = y;
    //tt->super.type = XF_VIEW_UNIT_TYPE_LIST;
    tt->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    tt->super.onMessageReceiver = onMessageReceiver;
    tt->head = XF_NULL;
    tt->posCursorBase = 0;
    tt->sizeCursor = sizeCursor;
    tt->posCursor = 0;
    tt->onSelect = onSelect;

    return tt;
}

void XF_VIEW_ListDelete(XF_VIEW_List *tt) {
    XF_VIEW_ListUnit *nextUnit = XF_NULL;
    XF_VIEW_ListUnit *currUnit = XF_NULL;

    if (XF_NULL == tt) return;
    if (XF_NULL != tt->head) {
        currUnit = tt->head;
        nextUnit = tt->head->next;
        while (XF_NULL != currUnit) {
            XF_VIEW_ListUnitDelete(currUnit);
            currUnit = nextUnit;
            nextUnit = nextUnit->next;
        }
    }

    XF_free(tt);
}

XF_VIEW_ListUnit *XF_VIEW_ListUnitNew(char *val) {
    XF_VIEW_ListUnit *ttunit = (XF_VIEW_ListUnit *)XF_malloc(sizeof(XF_VIEW_ListUnit));

    if (XF_NULL == ttunit) return XF_NULL;
    ttunit->val = (char*)val;
    ttunit->next = XF_NULL;

    return ttunit;
}

void XF_VIEW_ListUnitDelete(XF_VIEW_ListUnit *ttunit) {
    XF_free(ttunit);
}

int8 XF_VIEW_ListAddUnit(XF_VIEW_List *tt, XF_VIEW_ListUnit *ttunit) {
    XF_VIEW_ListUnit *posUnit = XF_NULL;

    if (XF_NULL == tt || XF_NULL == ttunit) return -1;
    if (XF_NULL == tt->head) {
        tt->head = ttunit;
        return 0;
    }

    for (posUnit = tt->head; posUnit->next != XF_NULL; posUnit = posUnit->next);
    posUnit->next = ttunit;
    return 0;
}

int8 XF_VIEW_ListRemoveUnit(XF_VIEW_List *tt, XF_VIEW_ListUnit *ttunit) {
    XF_VIEW_ListUnit *posUnit = XF_NULL;

    if (XF_NULL == tt || XF_NULL == ttunit) return -1;
    if (XF_NULL == tt->head) {
        return -2;
    }

    for (posUnit = tt->head; posUnit->next != XF_NULL; posUnit = posUnit->next) {
        if (posUnit->next == ttunit) {
            posUnit->next = ttunit->next;
            return 0;
        }
    }
    return -3;
}


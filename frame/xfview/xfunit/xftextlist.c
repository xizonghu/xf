#include "string.h"

#include "xftypedef.h"
#include "xfbgraph.h"
#include "xftextout.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xftextlist.h"

static char *tl_get_value(XF_VIEW_TextList *tl, attr pos) {
    if (XF_NULL == tl) return XF_NULL;
    if (pos >= tl->countValue) return XF_NULL;

    return (tl->values + tl->sizeValue * pos);
}

static void tl_show(XF_VIEW_TextList *tl) {
    uint8 pos = 0;
    uint8 x = tl->super.point.x, y = tl->super.point.y;

    for (pos = 0; pos < tl->countValue; pos++) {
        char strNull[] = "                ";
        XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, strNull, XF_BGRAPH_FILL_NORMAL);
    }

    for (pos = tl->posValue; pos > 0; pos--, tl->posValue = pos) {
        char *p = tl_get_value(tl, pos);
        if ('\0' != *p) break;
    }

    for (pos = 0; pos < tl->countValue; pos++) {
        char *pstr = XF_NULL;

        pstr = tl_get_value(tl, pos);
        if ('\0' == *pstr) {
            //if (0 != pos) {
            //    pos--;
            //    tl->posValue = pos;
            //    XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, pstr = tl_get_value(tl, pos), XF_BGRAPH_FILL_REVERSE);
            //}
            break;
        }

        if (pos == tl->posValue) {
            XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, pstr, XF_BGRAPH_FILL_REVERSE);
        } else {
            XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, pstr, XF_BGRAPH_FILL_NORMAL);
        }
    }
    XF_BgraphFlush(&globalGraph);
}

static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_TextList *tl = (XF_VIEW_TextList*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            tl_show(tl);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            tl_show(tl);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_TextListDelete(tl);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL: {
            switch (msg->val) {
                case XF_VIEW_UNIT_KEY_PAGE_UP: {
                    if (XF_NULL != tl->onEvent) {
                        XF_VIEW_TextListEvent evt = {XF_VIEW_TEXTLIST_EVENT_TYPE_PAGE_UP};
                        tl->onEvent(&evt);
                    }
                    tl_show(tl);
                    break;
                }
                case XF_VIEW_UNIT_KEY_PAGE_DOWN: {
                    if (XF_NULL != tl->onEvent) {
                        XF_VIEW_TextListEvent evt = {XF_VIEW_TEXTLIST_EVENT_TYPE_PAGE_DOWN};
                        tl->onEvent(&evt);
                    }
                    tl_show(tl);
                    break;
                }
                case XF_VIEW_UNIT_KEY_UP: {
                    if (0 == tl->posValue) {
                        if (XF_NULL != tl->onEvent) {
                            XF_VIEW_TextListEvent evt = {XF_VIEW_TEXTLIST_EVENT_TYPE_SCROLL_UP};
                            tl->onEvent(&evt);
                        }
                    }
                    else tl->posValue--;

                    tl_show(tl);
                    break;
                }
                case XF_VIEW_UNIT_KEY_DOWN: {
                    if((tl->countValue - 1) == tl->posValue) {
                        if (XF_NULL != tl->onEvent) {
                            XF_VIEW_TextListEvent evt = {XF_VIEW_TEXTLIST_EVENT_TYPE_SCROLL_DOWN};
                            tl->onEvent(&evt);
                        }
                    }
                    else tl->posValue++;
                    tl_show(tl);
                    break;
                }

                case XF_VIEW_UNIT_KEY_ENTER: {
                    XF_VIEW_TextListEvent evt = {XF_VIEW_TEXTLIST_EVENT_TYPE_SELECT};
                    evt.pos = tl->posValue;
                    evt.arg = (void*)tl_get_value(tl, tl->posValue);
                    if (XF_NULL == tl->onEvent) break;
                    tl->onEvent(&evt);
                    break;
                }
                case XF_VIEW_UNIT_KEY_BACK: {
                    XF_VIEW_TextListEvent evt = {XF_VIEW_TEXTLIST_EVENT_TYPE_UNSELECT};
                    if (XF_NULL == tl->onEvent) break;
                    tl->onEvent(&evt);
                    break;
                }
            }
            break;
        }
    }
}

XF_VIEW_TextList *XF_VIEW_TextListNew(attr x, attr y, attr sizeValue, attr countValue, void (*onEvent)(XF_VIEW_TextListEvent *evt)) {
    XF_VIEW_TextList *tl = XF_NULL;
    char *values = XF_NULL;
    uint8 pos = 0;

    if (XF_NULL == (tl = (XF_VIEW_TextList *)XF_malloc(sizeof(XF_VIEW_TextList)))) return XF_NULL;
    if (XF_NULL == (values = (char *)XF_malloc(sizeValue * countValue))) {
        XF_free(tl);
        return XF_NULL;
    }

    tl->super.point.x = x;
    tl->super.point.y = y;
    //tl->super.type = XF_VIEW_UINT_TYPE_TEXTLIST;
    tl->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    tl->super.onMessageReceiver = onMessageReceiver;
    tl->values = values;
    tl->sizeValue = sizeValue;
    tl->countValue = countValue;
    tl->posValue = 0;
    tl->onEvent = onEvent;

    for (pos = 0; pos < tl->countValue; pos++) XF_VIEW_TextListSetVal(tl, pos, "");

    return tl;
}

void XF_VIEW_TextListDelete(XF_VIEW_TextList *tl) {
    XF_free(tl->values);
    XF_free(tl);
}

int8 XF_VIEW_TextListSetVal(XF_VIEW_TextList * tl, uint8 pos, char *val) {
    char *pCurr = XF_NULL;

    if (XF_NULL == tl) return -1;
    if (tl->sizeValue <= strlen(val)) return -2;
    pCurr = tl_get_value(tl, pos);
    if (XF_NULL == (pCurr = tl_get_value(tl, pos))) return -3;
    strcpy(pCurr, val);

    return 0;
}

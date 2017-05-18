#include "xftypedef.h"
#include "xfbgraph.h"
#include "xftextout.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xflist.h"

static void list_create(XF_VIEW_List *list) {
    //XF_BgraphSetText(&graphMain, list->super.point.x, list->super.point.y, list->super.buffer, XF_BGRAPH_COLOR_WHITE);
}

static void list_destroy(XF_VIEW_List *list) {
    //XF_BgraphSetText(&graphMain, list->super.point.x, list->super.point.y, list->super.buffer, XF_BGRAPH_COLOR_WHITE);
}

//static XF_VIEW_ListUnit *listunit_get_tail

static XF_VIEW_ListUnit *listunit_get_child_by_pos(XF_VIEW_ListUnit *listunit, attr pos) {
    XF_VIEW_ListUnit *curr = listunit->child;
    uint8 posTemp = 0;

    if (XF_NULL == curr) return XF_NULL;

    for(posTemp = 0; curr && posTemp < pos; posTemp++) {
        curr = curr->brother;
    }
    return curr;
}

static XF_VIEW_ListUnit *listunit_get_curr(XF_VIEW_ListUnit *listunit) {
    XF_VIEW_ListUnit *curr = listunit->child;
    uint8 pos = 0;

    if (XF_NULL == curr) return XF_NULL;

    //偏移到当前位置
    for(pos = 0; curr->brother && pos < listunit->pos; pos++) {
        curr = curr->brother;
    }

    //修正pos
    listunit->pos = pos;

    return curr;
}

static XF_VIEW_ListUnit *list_get_head(XF_VIEW_List *list) {
    return list->head;
}

static XF_VIEW_ListUnit *list_get_select(XF_VIEW_List *list) {
    XF_VIEW_ListUnit *curr = listunit_get_curr(list->head);
    uint8 pos = 0;

    //偏移到当前显示位置
    for(pos = 0; curr && pos < list->posCursor; pos++) {
        curr = curr->brother;
    }
    return curr;
}



static void list_show(XF_VIEW_List *list) {
    char strNull[] = "                ";
    uint8 pos = 0;
    uint8 x = list->super.point.x, y = list->super.point.y;
    XF_VIEW_ListUnit *curr = listunit_get_curr(list->head);
    XF_VIEW_ListUnit *temp = XF_NULL;

    //检测能否打印
    if (XF_NULL == list_get_select(list)) {
        return;
    }

    for(pos = 0; pos < list->sizeCursor; pos++) {
        XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, strNull, XF_BGRAPH_FILL_NORMAL);
        if(XF_NULL == curr) continue;

        if(pos == list->posCursor) {
            XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, curr->name, XF_BGRAPH_FILL_REVERSE);
        } else {
            XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, curr->name, XF_BGRAPH_FILL_NORMAL);
        }
        curr = curr->brother;
    }
    XF_BgraphFlush(&globalGraph);
}

static void list_delete(XF_VIEW_List *list) {
    
}

static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_List *list = (XF_VIEW_List*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            list_show(list);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            list_show(list);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_ListDelete(list);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL: {
            XF_VIEW_ListUnit *head = list_get_head(list);
            XF_VIEW_ListUnit *curr = list_get_select(list);
            switch (msg->val) {
                case XF_VIEW_UNIT_KEY_UP: {
                    //检查数据首
                    if(0 == head->pos && 0 == list->posCursor) break;
                    //检查显示首
                    if(0 == list->posCursor) head->pos--;
                    else list->posCursor--;
                    list_show(list);
                    break;
                }
                case XF_VIEW_UNIT_KEY_DOWN: {
                    //检查数据尾
                    if(XF_NULL == curr) break;
                    
                    //检查显示尾
                    if((list->sizeCursor - 1) == list->posCursor) {
                        if (XF_NULL == listunit_get_child_by_pos(head, head->pos + list->sizeCursor)) break;
                        head->pos++;
                    }
                    else list->posCursor++;
                    list_show(list);
                    break;
                }
                case XF_VIEW_UNIT_KEY_ENTER: {
                    if (XF_NULL == curr) break;
                    //检查是否有onSelect
                    if(XF_NULL != curr->onSelect) curr->onSelect(XF_NULL);

                    //检查是否有子list
                    if (XF_NULL == curr->child) break;
                    list->head = curr;
                    list->posCursor = 0;
                    list_show(list);
                    break;
                }
                case XF_VIEW_UNIT_KEY_BACK: {
                    if(XF_NULL == head->parent) {
                        *res = XF_VIEW_UNIT_MESSAGE_RES_QUIT;
                        break;
                    }
                    head->pos = 0;
                    list->posCursor = 0;
                    list->head = head->parent;
                    list_show(list);
                    break;
                }
            }
            break;
        }
    }
}

XF_VIEW_List *XF_VIEW_ListNew(attr x, attr y, XF_VIEW_ListUnit *root, attr sizeCursor) {
    XF_VIEW_List *list = (XF_VIEW_List *)XF_malloc(sizeof(XF_VIEW_List));

    if (XF_NULL == list) return XF_NULL;

    list->super.point.x = x;
    list->super.point.y = y;
    list->super.type = XF_VIEW_UNIT_TYPE_LIST;
    list->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    list->super.onMessageReceiver = onMessageReceiver;
    list->root = root;
    list->head = root;
    list->sizeCursor = sizeCursor;
    list->posCursor = 0;

    return list;
}

void XF_VIEW_ListDelete(XF_VIEW_List *list) {
    XF_VIEW_ListUnitDelete(list->root);
    XF_free(list);
}

XF_VIEW_ListUnit *XF_VIEW_ListUnitNew(const char *name, void (*onSelect)(void *arg)) {
    XF_VIEW_ListUnit *listunit = (XF_VIEW_ListUnit *)XF_malloc(sizeof(XF_VIEW_ListUnit));

    if (XF_NULL == listunit) return XF_NULL;
    listunit->name = (char*)name;
    listunit->onSelect = onSelect;
    listunit->parent = XF_NULL;
    listunit->brother = XF_NULL;
    listunit->child = XF_NULL;
    listunit->pos = 0;
    return listunit;
}

extern void XF_VIEW_ListUnitDelete(XF_VIEW_ListUnit *listunit) {
    if (listunit->brother) XF_VIEW_ListUnitDelete(listunit->brother);
    if (listunit->child) XF_VIEW_ListUnitDelete(listunit->child);
    XF_free(listunit);
}

void XF_VIEW_ListUnitAddBrother(XF_VIEW_ListUnit *listunit, XF_VIEW_ListUnit *brother) {
    XF_VIEW_ListUnit *last = listunit->brother;
    uint8 pos = 0;

    //兄弟节点为空
    if (XF_NULL == last) {
        listunit->brother = brother;
        return;
    }

    //兄弟节点不为空
    for (pos = 0; last && last->brother; pos++) last = last->brother;

    last->brother = brother;
}

void XF_VIEW_ListUnitAddChild(XF_VIEW_ListUnit *listunit, XF_VIEW_ListUnit *child) {
    XF_VIEW_ListUnit *last = listunit->child;
    uint8 pos = 0;

    //设置父节点
    child->parent = listunit;

    //孩子节点为空
    if (XF_NULL == last) {
        listunit->child = child;
        return;
    }

    //孩子节点不为空
    XF_VIEW_ListUnitAddBrother(last, child);
}

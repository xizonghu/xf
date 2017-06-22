#include "xftypedef.h"
#include "xfbgraph.h"
#include "xftextout.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xflisttree.h"

/*static void list_create(XF_VIEW_ListTree *list) {
    //XF_BgraphSetText(&graphMain, list->super.point.x, list->super.point.y, list->super.buffer, XF_BGRAPH_COLOR_WHITE);
}*/

/*static void list_destroy(XF_VIEW_ListTree *list) {
    //XF_BgraphSetText(&graphMain, list->super.point.x, list->super.point.y, list->super.buffer, XF_BGRAPH_COLOR_WHITE);
}*/

//static XF_VIEW_ListTreeUnit *listunit_get_tail

static XF_VIEW_ListTreeUnit *listunit_get_child_by_pos(XF_VIEW_ListTreeUnit *listunit, attr pos) {
    XF_VIEW_ListTreeUnit *curr = listunit->child;
    uint8 posTemp = 0;

    if (XF_NULL == curr) return XF_NULL;

    for(posTemp = 0; curr && posTemp < pos; posTemp++) {
        curr = curr->brother;
    }
    return curr;
}

static XF_VIEW_ListTreeUnit *listunit_get_curr(XF_VIEW_ListTreeUnit *listunit) {
    XF_VIEW_ListTreeUnit *curr = listunit->child;
    uint8 pos = 0;

    if (XF_NULL == curr) return XF_NULL;

    //ƫ�Ƶ���ǰλ�� 
    for(pos = 0; curr->brother && pos < listunit->pos; pos++) {
        curr = curr->brother;
    }

    //����pos 
    listunit->pos = pos;

    return curr;
}

static XF_VIEW_ListTreeUnit *list_get_head(XF_VIEW_ListTree *list) {
    return list->head;
}

static XF_VIEW_ListTreeUnit *list_get_select(XF_VIEW_ListTree *list) {
    XF_VIEW_ListTreeUnit *curr = listunit_get_curr(list->head);
    uint8 pos = 0;

    //ƫ�Ƶ���ǰ��ʾλ�� 
    for(pos = 0; curr && pos < list->posCursor; pos++) {
        curr = curr->brother;
    }
    return curr;
}



static void list_show(XF_VIEW_ListTree *list) {
    char strNull[] = "                ";
    uint8 pos = 0;
    uint8 x = list->super.point.x, y = list->super.point.y;
    XF_VIEW_ListTreeUnit *curr = listunit_get_curr(list->head);

    //����ܷ��ӡ 
    if (XF_NULL == list_get_select(list)) {
        return;
    }

    for(pos = 0; pos < list->sizeCursor; pos++) {
        XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, strNull, XF_BGRAPH_FILL_NORMAL);
        if(XF_NULL == curr) continue;

        if(pos == list->posCursor) {
            XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, curr->val, XF_BGRAPH_FILL_REVERSE);
        } else {
            XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, curr->val, XF_BGRAPH_FILL_NORMAL);
        }
        curr = curr->brother;
    }
    XF_BgraphFlush(&globalGraph);
}

/*static void list_delete(XF_VIEW_ListTree *list) {
}*/

static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_ListTree *list = (XF_VIEW_ListTree*)unit;
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
            XF_VIEW_ListTreeDelete(list);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL: {
            XF_VIEW_ListTreeUnit *head = list_get_head(list);
            XF_VIEW_ListTreeUnit *curr = list_get_select(list);
            switch (msg->val) {
                case XF_VIEW_UNIT_KEY_UP: {
                    //���������
                    if(0 == head->pos && 0 == list->posCursor) break;
                    //�����ʾ��
                    if(0 == list->posCursor) head->pos--;
                    else list->posCursor--;
                    list_show(list);
                    break;
                }
                case XF_VIEW_UNIT_KEY_DOWN: {
                    //�������β
                    if(XF_NULL == curr) break;
                    
                    //�����ʾβ
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
                    //����Ƿ���onSelect
                    if(XF_NULL != list->onSelect) list->onSelect(curr->val);

                    //����Ƿ�����list
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

XF_VIEW_ListTree *XF_VIEW_ListTreeNew(attr x, attr y, XF_VIEW_ListTreeUnit *root, attr sizeCursor, void (*onSelect)(char *val)) {
    XF_VIEW_ListTree *list = (XF_VIEW_ListTree *)XF_malloc(sizeof(XF_VIEW_ListTree));

    if (XF_NULL == list) return XF_NULL;

    list->super.point.x = x;
    list->super.point.y = y;
    //list->super.type = XF_VIEW_UNIT_TYPE_LISTTREE;
    list->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    list->super.onMessageReceiver = onMessageReceiver;
    list->root = root;
    list->head = root;
    list->sizeCursor = sizeCursor;
    list->posCursor = 0;
    list->onSelect = onSelect;

    return list;
}

void XF_VIEW_ListTreeDelete(XF_VIEW_ListTree *list) {
    XF_VIEW_ListTreeUnitDelete(list->root);
    XF_free(list);
}

XF_VIEW_ListTreeUnit *XF_VIEW_ListTreeUnitNew(const char *val) {
    XF_VIEW_ListTreeUnit *listunit = (XF_VIEW_ListTreeUnit *)XF_malloc(sizeof(XF_VIEW_ListTreeUnit));

    if (XF_NULL == listunit) return XF_NULL;
    listunit->val = (char*)val;
    listunit->parent = XF_NULL;
    listunit->brother = XF_NULL;
    listunit->child = XF_NULL;
    listunit->pos = 0;
    return listunit;
}

extern void XF_VIEW_ListTreeUnitDelete(XF_VIEW_ListTreeUnit *listunit) {
    if (listunit->brother) XF_VIEW_ListTreeUnitDelete(listunit->brother);
    if (listunit->child) XF_VIEW_ListTreeUnitDelete(listunit->child);
    XF_free(listunit);
}

void XF_VIEW_ListTreeUnitAddBrother(XF_VIEW_ListTreeUnit *listunit, XF_VIEW_ListTreeUnit *brother) {
    XF_VIEW_ListTreeUnit *last = listunit->brother;
    uint8 pos = 0;

    //�ֵܽڵ�Ϊ��
    if (XF_NULL == last) {
        listunit->brother = brother;
        return;
    }

    //�ֵܽڵ㲻Ϊ��
    for (pos = 0; last && last->brother; pos++) last = last->brother;

    last->brother = brother;
}

void XF_VIEW_ListTreeUnitAddChild(XF_VIEW_ListTreeUnit *listunit, XF_VIEW_ListTreeUnit *child) {
    XF_VIEW_ListTreeUnit *last = listunit->child;

    //���ø��ڵ�
    child->parent = listunit;

    //���ӽڵ�Ϊ��
    if (XF_NULL == last) {
        listunit->child = child;
        return;
    }

    //���ӽڵ㲻Ϊ��
    XF_VIEW_ListTreeUnitAddBrother(last, child);
}

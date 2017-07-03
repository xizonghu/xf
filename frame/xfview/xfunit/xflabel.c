#include "string.h"

#include "xftypedef.h"
#include "xfbgraph.h"
#include "xftextout.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xflabel.h"

/*static void label_create(XF_VIEW_Label *label) {
}*/

/*static void label_destroy(XF_VIEW_Label *label) {
}*/

static void label_show(XF_VIEW_Label *label) {
    XF_TextoutPrint(&globalTextout, label->super.point.x, label->super.point.y, label->val, XF_BGRAPH_FILL_NORMAL);
    XF_BgraphFlush(&globalGraph);
}

static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_Label *label = (XF_VIEW_Label*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            label_show(label);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            if (XF_VIEW_UNIT_KEY_UP == msg->val || XF_VIEW_UNIT_KEY_BACK == msg->val ) {
                *res = XF_VIEW_UNIT_MESSAGE_RES_PREV;
            }
            else {
                *res = XF_VIEW_UNIT_MESSAGE_RES_NEXT;
            }
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_LabelDelete(label);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL: {
            switch (msg->val) {
                case XF_VIEW_UNIT_KEY_BACK: {
                    *res = XF_VIEW_UNIT_MESSAGE_RES_QUIT;
                    break;
                }
            }
            break;
        }
    }
}

XF_VIEW_Label *XF_VIEW_LabelNew(attr x, attr y, const char *val) {
    XF_VIEW_Label *label = XF_malloc(sizeof(XF_VIEW_Label));

    if (XF_NULL == label) return XF_NULL;

    label->super.point.x = x;
    label->super.point.y = y;
    //label->super.type = XF_VIEW_UNIT_TYPE_LABEL;
    label->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    label->super.onMessageReceiver = onMessageReceiver;
    label->val = (char*)val;
    return label;
}

void XF_VIEW_LabelDelete(XF_VIEW_Label* label) {
    XF_free(label);
}

void XF_VIEW_LabelSetValue(XF_VIEW_Label *label, char *val) {
    char str[] = "                ";
    str[strlen(label->val)] = '\0';
    label->val = str;
    label_show(label);
    label->val = val;
    label_show(label);
}
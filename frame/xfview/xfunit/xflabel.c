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
    XF_TextoutPrint(&globalTextout, label->super.point.x, label->super.point.y, label->name, XF_BGRAPH_FILL_NORMAL);
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
    }
}

XF_VIEW_Label *XF_VIEW_LabelNew(attr x, attr y, const char *name) {
    XF_VIEW_Label *label = XF_malloc(sizeof(XF_VIEW_Label));

    if (XF_NULL == label) return XF_NULL;

    label->super.point.x = x;
    label->super.point.y = y;
    label->super.type = XF_VIEW_UNIT_TYPE_LABEL;
    label->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    label->super.onMessageReceiver = onMessageReceiver;
    label->name = (char*)name;
    return label;
}

void XF_VIEW_LabelDelete(XF_VIEW_Label* label) {
    XF_free(label);
}
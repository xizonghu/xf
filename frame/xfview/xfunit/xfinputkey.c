#include "xftypedef.h"
#include "xfbgraph.h"
#include "xftextout.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xfinputkey.h"


static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_InputKey *inputkey = (XF_VIEW_InputKey*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_InputKeyDelete(inputkey);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL: {
            if (inputkey->onPressKey) inputkey->onPressKey(msg->val);
            break;
        }
    }
}

XF_VIEW_InputKey *XF_VIEW_InputKeyNew(void (*onPressKey)(char ch)) {
    XF_VIEW_InputKey *inputkey = XF_malloc(sizeof(XF_VIEW_InputKey));

    if (XF_NULL == inputkey) return XF_NULL;

    inputkey->super.point.x = 0;
    inputkey->super.point.y = 0;
    inputkey->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    inputkey->super.onMessageReceiver = onMessageReceiver;
    inputkey->onPressKey = onPressKey;
    return inputkey;
}

void XF_VIEW_InputKeyDelete(XF_VIEW_InputKey* inputkey) {
    XF_free(inputkey);
}


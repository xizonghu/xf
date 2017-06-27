#include "xftypedef.h"
#include "xfbgraph.h"
#include "xftextout.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xfbattery.h"

static void bat_show(XF_VIEW_Battery *bat) {
    char strNull[] = "                ";
    uint8 pos = 0;
    uint8 x = bat->super.point.x, y = bat->super.point.y;

    XF_TextoutPrint(&globalTextout, x, y + pos * globalTextout.fontChar->fontHeight, strNull, XF_BGRAPH_FILL_NORMAL);
    XF_BgraphFlush(&globalGraph);
}

/*static void list_delete(XF_VIEW_ListTree *list) {
}*/

static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_Battery *bat = (XF_VIEW_Battery*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_BatteryDelete(bat);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL: {
            *res = XF_VIEW_UNIT_MESSAGE_RES_QUIT;
            break;
        }
    }
}

XF_VIEW_Battery *XF_VIEW_BatteryNew(attr x, attr y, void (*show)(uint8 val)) {
    XF_VIEW_Battery *bat = (XF_VIEW_Battery*)XF_malloc(sizeof(XF_VIEW_Battery));

    if (XF_NULL == bat) return XF_NULL;

    bat->super.point.x = x;
    bat->super.point.y = y;
    bat->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    bat->super.onMessageReceiver = onMessageReceiver;
    bat->super.next = XF_NULL;

    bat->show = show;

    return bat;
}

void XF_VIEW_BatteryDelete(XF_VIEW_Battery *bat) {
    XF_free(bat);
}

void XF_VIEW_BatterySetVal(XF_VIEW_Battery *bat, uint8 val) {
    
}

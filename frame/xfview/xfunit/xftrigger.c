#include "xftypedef.h"
#include "xfbgraph.h"
#include "xftextout.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xfbutton.h"

#define BUTTON_MSG_KEY_UP           '2'
#define BUTTON_MSG_KEY_DOWN         '8'
#define BUTTON_MSG_KEY_ENTER        '#'
#define BUTTON_MSG_KEY_BACK         '*'

/*static void button_create(XF_VIEW_Button *button) {
}*/

/*static void button_destroy(XF_VIEW_Button *button) {
}*/

static void button_show(XF_VIEW_Button *button) {
    XF_TextoutPrint(&globalTextout, button->super.point.x, button->super.point.y, button->name, XF_BGRAPH_FILL_NORMAL);
    XF_BgraphFlush(&globalGraph);
}

static void button_focus(XF_VIEW_Button *button) {
    XF_TextoutPrint(&globalTextout, button->super.point.x, button->super.point.y, button->name, XF_BGRAPH_FILL_REVERSE);
    XF_BgraphFlush(&globalGraph);
}

static void button_unfocus(XF_VIEW_Button *button) {
    button_show(button);
}


static void button_click(XF_VIEW_Button *button) {
    if(0 == button->click) return;
    button->click(0);
}

static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_Trigger *trigger = (XF_VIEW_Trigger*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            if (XF_VIEW_UNIT_KEY_UP == msg->val || XF_VIEW_UNIT_KEY_BACK == msg->val ) {
                *res = XF_VIEW_UNIT_MESSAGE_RES_PREV;
            }
            else {
                if (trigger->onTrigger) trigger->onTrigger();
                *res = XF_VIEW_UNIT_MESSAGE_RES_NEXT;
            }
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_TriggerDelete(trigger);
            break;
        }
    }
}

XF_VIEW_Trigger *XF_VIEW_TriggerNew(attr x, attr y, void (*onTrigger)(void *arg)) {
    XF_VIEW_Trigger *trigger = (XF_VIEW_Trigger*)XF_malloc(sizeof(XF_VIEW_Trigger));

    if (XF_NULL == trigger) return XF_NULL;

    trigger->super.point.x = x;
    trigger->super.point.y = y;
    trigger->super.type = XF_VIEW_UNIT_TYPE_TRIGGER;
    trigger->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    trigger->super.onMessageReceiver = onMessageReceiver;
    trigger->onTrigger = onTrigger;
    return trigger;
}

void XF_VIEW_TriggerDelete(XF_VIEW_Trigger *trigger) {
    XF_free(trigger);
}

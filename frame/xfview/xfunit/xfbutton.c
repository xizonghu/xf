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

static void button_create(XF_VIEW_Button *button) {

}

static void button_destroy(XF_VIEW_Button *button) {
}

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
    XF_VIEW_Button *button = (XF_VIEW_Button*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            button_show(button);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            button_focus(button);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_ButtonDelete(button);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL: {
            switch (msg->val) {
                case BUTTON_MSG_KEY_UP: {
                    button_unfocus(button);
                    *res = XF_VIEW_UNIT_MESSAGE_RES_PREV;
                    break;
                }
                case BUTTON_MSG_KEY_DOWN: {
                    button_unfocus(button);
                    *res = XF_VIEW_UNIT_MESSAGE_RES_NEXT;
                    break;
                }
                case BUTTON_MSG_KEY_ENTER: {
                    button_click(button);
                    break;
                }
                case BUTTON_MSG_KEY_BACK: {
                    *res = XF_VIEW_UNIT_MESSAGE_RES_QUIT;
                    break;
                }
            }
            break;
        }
    }
}

XF_VIEW_Button *XF_VIEW_ButtonNew(attr x, attr y, const char *name, void (*onClick)(void *arg)) {
    XF_VIEW_Button *button = (XF_VIEW_Button*)XF_malloc(sizeof(XF_VIEW_Button));

    if (XF_NULL == button) return XF_NULL;

    button->super.point.x = x;
    button->super.point.y = y;
    button->super.type = XF_VIEW_UNIT_TYPE_BUTTON;
    button->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    button->super.onMessageReceiver = onMessageReceiver;
    button->name = name;
    button->click = onClick;
    return button;
}

void XF_VIEW_ButtonDelete(XF_VIEW_Button *button) {
    XF_free(button);
}

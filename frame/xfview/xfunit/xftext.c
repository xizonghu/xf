#include <string.h>

#include "xftypedef.h"
#include "xfbgraph.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xftext.h"


#define TEXT_MSG_KEY_ENTER        '#'
#define TEXT_MSG_KEY_BACK         '*'

static XF_VIEW_UnitMessageRes text_backward(XF_VIEW_Text *text) {
    uint8 x = text->super.point.x, y = text->super.point.y, len = strlen(text->name);
    char str[2] = {'_', 0};

	if(len <= 0) return XF_VIEW_UNIT_MESSAGE_RES_PREV;
    //更新text
    len--;
    *(text->name + len) = '\0';

    //更新界面

    XF_BgraphSetText(&graphMain, x + len * graphMain.pixelOfCharX, y, str, XF_BGRAPH_COLOR_WHITE);
    XF_BgraphFlush(&graphMain);

    return XF_VIEW_UNIT_MESSAGE_RES_OK;
}

static XF_VIEW_UnitMessageRes text_forward(XF_VIEW_Text *text, char ch) {
    uint8 x = text->super.point.x, y = text->super.point.y, len = strlen(text->name);
    char str[2] = {0, 0};

	if(len >= text->size) len--;

	//更新text
    *(text->name + len) = ch;
    len++;
    *(text->name + len) = '\0';

    //更新界面
    if(XF_VIEW_TEXT_TYPE_PASSWD == text->type) {
        str[0] = '*';
    } else {
        str[0] = ch;
    }

    XF_BgraphSetText(&graphMain, x + (len - 1)*graphMain.pixelOfCharX, y, str, XF_BGRAPH_COLOR_WHITE);
    XF_BgraphFlush(&graphMain);

	//if(len >= text->size) return VIEW_RET_NEXT;

	return XF_VIEW_UNIT_MESSAGE_RES_OK;
}

static void text_create(XF_VIEW_Text *text) {
}

static void text_destroy(XF_VIEW_Text *text) {
}


static void text_show(XF_VIEW_Text *text) {
    char strNull[] = "________________";
    *(text->name + 0) = '\0';
    strNull[text->size] = '\0';
    XF_BgraphSetText(&graphMain, text->super.point.x, text->super.point.y, strNull, XF_BGRAPH_COLOR_WHITE);
}

static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_Text *text = (XF_VIEW_Text*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            text_show(text);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_TextDelete(text);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL: {
            switch (msg->val) {
                case TEXT_MSG_KEY_ENTER: {
                    *res = XF_VIEW_UNIT_MESSAGE_RES_NEXT;
                    break;
                }
                case TEXT_MSG_KEY_BACK: {
                    *res = text_backward(text);
                    break;
                }
                default: {
                    *res = text_forward(text, msg->val);
                }
            }
            break;
        }
    }
}

XF_VIEW_Text *XF_VIEW_TextNew(attr x, attr y, attr type, uint8 size) {
    XF_VIEW_Text *text = (XF_VIEW_Text*)XF_malloc(sizeof(XF_VIEW_Text));
    char *name = (char*)XF_malloc(size + 1);

    if (XF_NULL == text || XF_NULL == name) {
        XF_free(text);
        XF_free(name);
        return XF_NULL;
    }

    text->super.point.x = x;
    text->super.point.y = y;
    text->super.type = XF_VIEW_UNIT_TYPE_TEXT;
    text->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    text->super.onMessageReceiver = onMessageReceiver;
    text->name = name;
    text->pos = 0;
    text->size = size;
    return text;
}

void XF_VIEW_TextDelete(XF_VIEW_Text *text) {
    XF_free(text->name);
    XF_free(text);
}

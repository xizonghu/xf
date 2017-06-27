#include <string.h>

#include "xftypedef.h"
#include "xfbgraph.h"
#include "xftextout.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xftextedit.h"


#define TEXT_MSG_KEY_ENTER        '#'
#define TEXT_MSG_KEY_BACK         '*'

static XF_VIEW_UnitMessageRes text_backward(XF_VIEW_TextEdit *text) {
    uint8 x = text->super.point.x, y = text->super.point.y, len = strlen(text->val);
    char str[2] = {'_', 0};

	if(len <= 0) return XF_VIEW_UNIT_MESSAGE_RES_PREV;
    //更新text
    len--;
    *(text->val + len) = '\0';

    //更新界面
    XF_TextoutPrint(&globalTextout, x + len * globalTextout.fontChar->fontWidth, y, str, XF_BGRAPH_FILL_NORMAL);
    XF_BgraphFlush(&globalGraph);

    return XF_VIEW_UNIT_MESSAGE_RES_OK;
}

static XF_VIEW_UnitMessageRes text_forward(XF_VIEW_TextEdit *text, char ch) {
    uint8 x = text->super.point.x, y = text->super.point.y, len = strlen(text->val);
    char str[2] = {0, 0};

	if(len >= text->size) len--;

	//更新text
    *(text->val + len) = ch;
    len++;
    *(text->val + len) = '\0';

    //更新界面
    if(XF_VIEW_TEXTEDIT_TYPE_PASSWD == text->type) {
        str[0] = '*';
    } else {
        str[0] = ch;
    }

    XF_TextoutPrint(&globalTextout, x + (len - 1)*globalTextout.fontChar->fontWidth, y, str, XF_BGRAPH_FILL_NORMAL);
    XF_BgraphFlush(&globalGraph);

	if(len >= text->size) return XF_VIEW_UNIT_MESSAGE_RES_NEXT;

	return XF_VIEW_UNIT_MESSAGE_RES_OK;
}

/*static void text_create(XF_VIEW_TextEdit *text) {
}*/

/*static void text_destroy(XF_VIEW_TextEdit *text) {
}*/

static void text_clear(XF_VIEW_TextEdit *text) {
    char strNull[] = "                ";
    strNull[text->size] = '\0';
    XF_TextoutPrint(&globalTextout, text->super.point.x, text->super.point.y, strNull, XF_BGRAPH_FILL_NORMAL);
}

static void text_show(XF_VIEW_TextEdit *text) {
    char strNull[] = "________________";
    *(text->val + 0) = '\0';
    strNull[text->size] = '\0';
    XF_TextoutPrint(&globalTextout, text->super.point.x, text->super.point.y, strNull, XF_BGRAPH_FILL_NORMAL);
    XF_BgraphFlush(&globalGraph);
}

static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_TextEdit *text = (XF_VIEW_TextEdit*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            text_show(text);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            text_show(text);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_TextEditDelete(text);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_VISIABLE: {
            if (XF_VIEW_UNIT_VISIBALE_FALSE ==  msg->val) text_clear(text);
            else text_show(text);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL: {
            switch (msg->val) {
                case TEXT_MSG_KEY_ENTER: {
                    if (text->onStateChange) text->onStateChange(XF_VIEW_TEXTEDIT_STATE_COMPLETE, text->val);  //有回调必须在onMessageReceiver中返回XF_VIEW_UNIT_MESSAGE_RES_OK 
                    else *res = XF_VIEW_UNIT_MESSAGE_RES_NEXT;
                    break;
                }
                case TEXT_MSG_KEY_BACK: {
                    *res = text_backward(text);
                    if (XF_VIEW_UNIT_MESSAGE_RES_PREV == *res && text->onStateChange) {
                        text->onStateChange(XF_VIEW_TEXTEDIT_STATE_BREAK, text->val);
                        *res = XF_VIEW_UNIT_MESSAGE_RES_OK;
                    }
                    break;
                }
                default: {
                    *res = text_forward(text, msg->val);
                    if (XF_VIEW_UNIT_MESSAGE_RES_NEXT == *res) if (text->onStateChange) text->onStateChange(XF_VIEW_TEXTEDIT_STATE_COMPLETE, text->val);
                }
            }
            break;
        }
    }
}

XF_VIEW_TextEdit *XF_VIEW_TextEditNew(attr x, attr y, attr type, uint8 size, void (*onStateChange)(uint8 state, char *val)) {
    XF_VIEW_TextEdit *text = (XF_VIEW_TextEdit*)XF_malloc(sizeof(XF_VIEW_TextEdit));
    char *val = (char*)XF_malloc(size + 1);

    if (XF_NULL == text || XF_NULL == val) {
        XF_free(text);
        XF_free(val);
        return XF_NULL;
    }

    text->super.point.x = x;
    text->super.point.y = y;
    //text->super.type = XF_VIEW_UNIT_TYPE_TEXTEDIT;
    text->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    text->super.onMessageReceiver = onMessageReceiver;
    text->type = type;
    text->val = val;
    text->pos = 0;
    text->size = size;
    text->onStateChange = onStateChange;
    return text;
}

void XF_VIEW_TextEditDelete(XF_VIEW_TextEdit *text) {
    XF_free(text->val);
    XF_free(text);
}

char *XF_VIEW_TextEditGetValue(XF_VIEW_TextEdit *text) {
    return text->val;
}

void XF_VIEW_TextEditSetValue(XF_VIEW_TextEdit *text, char *val) {
    uint8 size = (text->size < strlen(val)) ? text->size : strlen(val);

    memcpy(text->val, val, size);
    text->val[size] = '\0';
    XF_TextoutPrint(&globalTextout, text->super.point.x, text->super.point.y, text->val, XF_BGRAPH_FILL_NORMAL);
    XF_BgraphFlush(&globalGraph);
}

#include "xfconf.h"
#include "xfea.h"
#include "xfstate.h"

#include "view.h"
#include "bgraph.h"


#define VIEW_TEX_RET_OK         0
#define VIEW_TEXT_RET_QUIT      1
#define VIEW_TEXT_RET_FINISH    2

#define VIEW_RET_OK             0
#define VIEW_RET_QUIT           1
#define VIEW_RET_FINISH         2
#define VIEW_RET_INPUT          3
#define VIEW_RET_TIMEOUT        4
#define VIEW_RET_PREV           5
#define VIEW_RET_NEXT           6

#define VIEW_MSG_KEY_DOWN       '8'
#define VIEW_MSG_KEY_UP         '2'
#define VIEW_MSG_KEY_LEFT       '4'
#define VIEW_MSG_KEY_RIGHT      '6'
#define VIEW_MSG_KEY_BACK       '*'
#define VIEW_MSG_KEY_ENTER      '#'

#define VIEW_MSG_TIMEOUT        0x80
#define VIEW_MSG_FINISH         0x81
#define VIEW_MSG_FOCUS          0x82
#define VIEW_MSG_PLAY           0x83
#define VIEW_MSG_FOCUS_PREV     0x84
#define VIEW_MSG_FOCUS_NEXT     0x85
#define VIEW_MSG_QUIT           0x86
#define VIEW_MSG_UNFOCUS        0x87
#define VIEW_MSG_NONE           0x00
#define VIEW_MSG_INIT           0x88

extern BGRAPH graphMain;

void list_show(VIEW_List *list);
void button_click(VIEW_Button *button);

void view_click_handler(XF_Info *info);

int ProcessMsg(XF_Message *msg);
void SendMessage(XF_Message *msg);

void list_focus(VIEW_List *list, char ch);


static VIEW_Layout *mView = 0;

XF_Action ViewAction = {
    "view click",
    view_click_handler,
};

/////////////////////label////////////////////
static void label_create(VIEW_Label *label) {
    bgraph_set_text(&graphMain, label->super.point.x, label->super.point.y, label->super.buffer, BGRAPH_COLOR_WHITE);
}

static void label_destroy(VIEW_Label *label) {
}

static uint8_t label_process_msg(VIEW_Label *label, XF_Message *msg) {
    return VIEW_RET_NEXT;
}

/////////////////////label////////////////////
static uint8_t text_backward(VIEW_Text *text) {
    uint8_t x = text->super.point.x, y = text->super.point.y, len = strlen(text->super.buffer);
    char str[2] = {'_', 0};

	if(len <= 0) return VIEW_RET_PREV;
    //����text
    len--;
    *(text->super.buffer + len) = '\0';

    //���½���

    bgraph_set_text(&graphMain, x + len * graphMain.pixelOfCharX, y, str, BGRAPH_COLOR_WHITE);

    return VIEW_RET_OK;
}

static uint8_t text_forward(VIEW_Text *text, char ch) {
    uint8_t x = text->super.point.x, y = text->super.point.y, len = strlen(text->super.buffer);
    char str[2] = {0, 0};

	if(len >= text->size) len--;

	//����text
    *(text->super.buffer + len) = ch;
    len++;
    *(text->super.buffer + len) = '\0';

    //���½���
    if(VIEW_TEXT_TYPE_PWD == text->type) {
        str[0] = '*';
    } else {
        str[0] = ch;
    }

    bgraph_set_text(&graphMain, x + (len - 1)*graphMain.pixelOfCharX, y, str, BGRAPH_COLOR_WHITE);

	//if(len >= text->size) return VIEW_RET_NEXT;

	return VIEW_RET_OK;
}

static void text_create(VIEW_Text *text) {
    char strNull[] = "________________";
    *(text->super.buffer + 0) = '\0';
    strNull[text->size] = '\0';
    bgraph_set_text(&graphMain, text->super.point.x, text->super.point.y, strNull, BGRAPH_COLOR_WHITE);
}

static void text_destroy(VIEW_Text *text) {
}

static int text_process_msg(VIEW_Text *text, XF_Message *msg) {
    switch(msg->what) {
        case VIEW_MSG_PLAY: {
            char str[] = "_";
            bgraph_set_text(&graphMain, text->super.point.x, text->super.point.y, str, BGRAPH_COLOR_BLACK);
            break;
        }
        case VIEW_MSG_KEY_BACK: {
            return text_backward(text);
        }
        case VIEW_MSG_KEY_ENTER: {
            return VIEW_RET_NEXT;
        }
        default: {
            return text_forward(text, msg->what);
        }
    }

    return VIEW_RET_OK;
}

/////////////////////label////////////////////

static void button_create(VIEW_Button *button) {
    bgraph_set_text(&graphMain, button->super.point.x, button->super.point.y, button->super.buffer, BGRAPH_COLOR_WHITE);
}

static void button_destroy(VIEW_Button *button) {
}

static uint8_t button_process_msg(VIEW_Button *button, XF_Message *msg) {
    switch(msg->what) {
        case VIEW_MSG_PLAY: {
            bgraph_set_text(&graphMain, button->super.point.x, button->super.point.y, button->super.buffer, BGRAPH_COLOR_BLACK);
            break;
        }
        case VIEW_MSG_KEY_DOWN: {
            bgraph_set_text(&graphMain, button->super.point.x, button->super.point.y, button->super.buffer, BGRAPH_COLOR_WHITE);
            return VIEW_RET_NEXT;
        }
        case VIEW_MSG_KEY_BACK:
        case VIEW_MSG_KEY_UP: {
            bgraph_set_text(&graphMain, button->super.point.x, button->super.point.y, button->super.buffer, BGRAPH_COLOR_WHITE);
            return VIEW_RET_PREV;
        }
        case VIEW_MSG_KEY_ENTER: {
            button->click(mView);
            break;
        }

    }
    return VIEW_RET_OK;
}

/////////////////////label////////////////////
static void list_create(VIEW_List *list) {
    //bgraph_set_text(&graphMain, list->super.point.x, list->super.point.y, list->super.buffer, BGRAPH_COLOR_WHITE);
}

static void list_destroy(VIEW_List *list) {
    bgraph_set_text(&graphMain, list->super.point.x, list->super.point.y, list->super.buffer, BGRAPH_COLOR_WHITE);
}

static uint8_t list_process_msg(VIEW_List *list, XF_Message *msg) {
    VIEW_ListOption *currOpt = (VIEW_ListOption *)list->listUnit;

    if(VIEW_LIST_TYPE_OPTION != currOpt->super.type) return 0;

    switch(msg->what) {
        case VIEW_MSG_PLAY: {
            break;
        }
        case VIEW_MSG_KEY_DOWN: {
            VIEW_ListUnit *headUnit = 0;
            uint8_t pos = 0;

            //�������β
            headUnit = currOpt->child;
            for(pos = 0; headUnit && pos < currOpt->pos; pos++) {
                headUnit = headUnit->next;
            }
            for(pos = 0; headUnit && pos <= list->posCursor; pos++) {
                headUnit = headUnit->next;
            }
            if(0 == headUnit) break;

            //�����ʾβ
            if((list->sizeCursor - 1) == list->posCursor) currOpt->pos++;
            else list->posCursor++;
            break;
        }
        case VIEW_MSG_KEY_UP: {
            //���������
            if(0 == currOpt->pos && 0 == list->posCursor) break;

            //�����ʾ��
            if(0 == list->posCursor) currOpt->pos--;
            else list->posCursor--;
            break;
        }
        case VIEW_MSG_KEY_BACK: {
            if(0 == list->listUnit->parent) return VIEW_RET_NEXT;
            currOpt->pos = 0;
            list->posCursor = 0;
            list->listUnit = list->listUnit->parent;
            break;
        }
        case VIEW_MSG_KEY_ENTER: {
            VIEW_ListUnit *headUnit = 0;
            uint8_t pos = 0;

            headUnit = currOpt->child;
            for(pos = 0; headUnit && pos < currOpt->pos; pos++) {
                headUnit = headUnit->next;
            }
            for(pos = 0; headUnit && pos < list->posCursor; pos++) {
                headUnit = headUnit->next;
            }
            if(0 == headUnit) break;
            if(VIEW_LIST_TYPE_OPTION == headUnit->type) {
                list->listUnit = headUnit;
                list->posCursor = 0;
            } else if(VIEW_LIST_TYPE_SUMBIT == headUnit->type) {
                ((VIEW_ListSubmit *)headUnit)->click(mView);
                return 0;
            }
            break;
        }
        /*case VIEW_MSG_KEY_DOWN: {
            if((currlist->sizeChildren - 1) == currlist->posChild) break;
            currlist->posChild++;
            if((currlist->sizeCursor - 1) == currlist->posCursor) {
                currlist->posCursor = 0;
                list_show(currlist);
            } else {
				currlist->posCursor++;
                list_focus(currlist, '+');
            }
            break;
        }
        case VIEW_MSG_KEY_UP: {
            if(0 == currlist->posChild) break;
            currlist->posChild--;
            if(0 == currlist->posCursor) {
                currlist->posCursor = (currlist->sizeCursor - 1);
                list_show(currlist);
            } else {
				currlist->posCursor--;
                list_focus(currlist, '-');
            }            
            break;
        }
        case VIEW_MSG_KEY_BACK: {
			currlist->posChild = 0;
			currlist->posCursor = 0;
            currlist = currlist->parent;
            if(0 == currlist) return VIEW_RET_NEXT;
            list_show(currlist);
            break;
        }
        case VIEW_MSG_KEY_ENTER: {
            currlist = (VIEW_List *)currlist->children[currlist->posChild];
            if(currlist->click) {
                currlist->click(mView);
            } else {
                list_show(currlist);
            }
            break;
        }*/
    }
    list_show(list);
    return VIEW_RET_OK;
}

/////////////////////label////////////////////

static void layout_create(VIEW_Layout *layout) {
    uint8_t pos = 0;

    if(layout->init) layout->init(layout);

    layout->posChild = 0;

    while(pos < layout->sizeChildren) {
        VIEW_Unit *uint = layout->children[pos++];
        if(VIEW_VISIBALE_FALSE == uint->visible) continue;
        switch(uint->type) {
            case VIEW_TYPE_LABEL: {
                label_create((VIEW_Label *)uint);
                break;
            }
            case VIEW_TYPE_LIST: {
                list_create((VIEW_List *)uint);
                break;
            }
            case VIEW_TYPE_BUTTON: {
                button_create((VIEW_Button *)uint);
                break;
            }
            case VIEW_TYPE_TEXT: {
                text_create((VIEW_Text *)uint);
                break;
            }
        }
    }
}

static void layout_destroy(VIEW_Layout *layout) {
    if(layout->exit) layout->exit(layout);
}

static uint8_t view_focus(VIEW_Layout *layout, VIEW_Unit *focus) {
    uint8_t pos = 0;
    uint8_t size = layout->sizeChildren;

    while(pos < size) {
        VIEW_Unit *uint = layout->children[pos];
        if(focus == uint) {
            layout->posChild = pos;
            break;
        }
		pos++;
    }

    return VIEW_RET_OK;
}

static uint8_t view_focus_prev(VIEW_Layout *layout) {
    VIEW_Unit *focus = 0;
    uint8_t x = 0, y = 0;
    uint8_t i = 0;
    uint8_t page = 0;
    if(0 >= layout->posChild) return VIEW_RET_QUIT;  //����Ҫ����

    layout->posChild--;

    return VIEW_RET_OK;
}

static uint8_t view_focus_next(VIEW_Layout *layout) {
    VIEW_Unit *focus = layout->children[layout->posChild];
    uint8_t x = 0, y = 0;
    uint8_t i = 0;
    if((layout->sizeChildren - 1) <= layout->posChild) return VIEW_RET_QUIT;  //����Ҫ����

    layout->posChild++;

    return VIEW_RET_OK;
}

static void view_click_handler(XF_Info *info) {
    char ch = 0;
    XF_Message msg = {0};
	ch = *(char *)(info->data);
    msg.what = ch;
    SendMessage(&msg);
}

static void SendMessage(XF_Message *msg) {
    ProcessMsg(msg);
}

static int ProcessMsg(XF_Message *msg) {
    uint8_t ret = 0;
    VIEW_Unit *uint;
    XF_Message m = {0};

    //��������
    switch(msg->what) {
        case VIEW_MSG_INIT: {
            bgraph_clear(&graphMain);
            layout_create(mView);
            return 0;
        }
        case VIEW_MSG_QUIT: {
            bgraph_clear(&graphMain);
            layout_destroy(mView);
            return 0;
        }
        case VIEW_MSG_TIMEOUT:
        case VIEW_MSG_FINISH: {
            VIEW_Layout *layout = mView->parent;
            bgraph_clear(&graphMain);
            layout_destroy(mView);
            if(layout) {
                m.what = msg->what;
                break;
            }
            return 0;
        }
        case VIEW_MSG_FOCUS: {
            view_focus(mView, (VIEW_Unit *)msg->data);
            break;
        }
        case VIEW_MSG_FOCUS_PREV: {
            if(VIEW_RET_QUIT == view_focus_prev(mView)) {
                m.what = VIEW_MSG_QUIT;
            } else {
                m.what = VIEW_MSG_PLAY;
            }
            break;
        }
        case VIEW_MSG_FOCUS_NEXT: {
            if(VIEW_RET_QUIT == view_focus_next(mView)) {
                m.what = VIEW_MSG_QUIT;
            } else {
                m.what = VIEW_MSG_PLAY;
            }
            break;
        }
    }

    if(m.what) {
        SendMessage(&m);
        return 0;
    }

    //�����ؼ�
    uint = mView->children[mView->posChild];
    switch(uint->type) {
        case VIEW_TYPE_LABEL: {
            ret = label_process_msg((VIEW_Label *)uint, msg);
            break;
        }
        case VIEW_TYPE_LIST: {
            ret = list_process_msg((VIEW_List *)uint, msg);
            break;
        }
        case VIEW_TYPE_BUTTON: {
            ret = button_process_msg((VIEW_Button *)uint, msg);
            break;
        }
        case VIEW_TYPE_TEXT: {
            ret = text_process_msg((VIEW_Text *)uint, msg);
            break;
        }
    }

    //ˢ����ʾ
    bgraph_refresh(&graphMain);

    //���ؽ���
    switch(ret) {
        case VIEW_RET_PREV: {
            m.what = VIEW_MSG_FOCUS_PREV;
            SendMessage(&m);
            break;
        }
        case VIEW_RET_NEXT: {
            m.what = VIEW_MSG_FOCUS_NEXT;
            SendMessage(&m);
            break;
        }
    }
    return 0;
}

void ViewShow(VIEW_Layout *layout) {
	XF_Message msg = {VIEW_MSG_INIT};

	mView = layout;
    SendMessage(&msg);
    ViewFocus(mView, mView->children[mView->posChild]);
}

void ViewCreate(VIEW_Layout * parent,VIEW_Layout * layout) {
    layout->parent = parent;
    layout->posChild = 0;
    ViewShow(layout);
}

void ViewFocus(VIEW_Layout *layout, VIEW_Unit *unit) {
    XF_Message msg = {VIEW_MSG_FOCUS, (void*)unit, sizeof(unit)};
    SendMessage(&msg);
}

void ViewBindEvent(XF_Event *evt) {
    XF_EventAddAct(evt, &ViewAction);
}

void ViewQuit() {
    VIEW_Layout *layout = mView->parent;
    XF_Message msg = {VIEW_MSG_QUIT};
    SendMessage(&msg);
    if(layout) ViewShow(layout);
}

void ViewFinish() {
    VIEW_Layout *layout = mView->parent;
    XF_Message msg = {VIEW_MSG_FINISH};
    SendMessage(&msg);
}

static void list_show(VIEW_List *list) {
    char strNull[] = "                ";
    uint8_t pos = 0;
    uint8_t x = list->super.point.x, y = list->super.point.y;
    VIEW_ListOption *currOpt = (VIEW_ListOption *)list->listUnit;
    VIEW_ListUnit *headUnit = 0;

    headUnit = currOpt->child;
    for(pos = 0; pos < currOpt->pos; pos++) {
        headUnit = headUnit->next;
    }

    for(pos = 0; pos < list->sizeCursor; pos++) {
        bgraph_set_text(&graphMain, x, y + pos * graphMain.pixelOfCharY, strNull, BGRAPH_COLOR_WHITE);
        if(0 == headUnit) continue;

        if(pos == list->posCursor) {
            bgraph_set_text(&graphMain, x, y + pos * graphMain.pixelOfCharY, headUnit->buffer, BGRAPH_COLOR_BLACK);
        } else {
            bgraph_set_text(&graphMain, x, y + pos * graphMain.pixelOfCharY, headUnit->buffer, BGRAPH_COLOR_WHITE);
        }
        headUnit = headUnit->next;
    }
}

/*static void list_focus(VIEW_List *list, char ch) {
    uint8_t x = list->super.point.x, y = list->super.point.y;
    uint8_t page = list->posChild / list->sizeCursor;
    uint8_t pos = list->posChild % list->sizeCursor;
    VIEW_Unit *uint = list->children[list->posChild];
    bgraph_set_text(&graphMain, x, y + pos * graphMain.pixelOfCharY, uint->buffer, BGRAPH_COLOR_BLACK);
    if('+' == ch) {
        uint = list->children[list->posChild - 1];
        pos = pos - 1;
    } else if('-' == ch) {
        uint = list->children[list->posChild + 1];
        pos = pos + 1;
    }
    bgraph_set_text(&graphMain, x, y + pos * graphMain.pixelOfCharY, uint->buffer, BGRAPH_COLOR_WHITE);
}*/

static void button_click(VIEW_Button *button) {
    if(0 == button->click) return;
    button->click(0);
}
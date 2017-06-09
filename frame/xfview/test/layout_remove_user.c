#include "xftypedef.h"

#include "language.h"
#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xftextlist.h"

#include "layout_add_user.h"

#define TLIST_COUNT     3

static const char *strs[] = {
    "1",
    "2",
    "3","4","5","6","7","8"
};
static const uint8 countStr = 8;
static uint8 posStrs = 0;

static XF_VIEW_Label *mLabelTopBar;
static XF_VIEW_TextList *mTList;

static void page_update(uint8 start) {
    uint8 pos = 0;
    for (pos = 0; pos < TLIST_COUNT; pos++) {
        if (start + pos < countStr) XF_VIEW_TextListSetVal(mTList, pos, strs[start + pos]);
        else XF_VIEW_TextListSetVal(mTList, pos, "");
    }
}

static void page_init() {
    posStrs = 0;
    page_update(posStrs);
}

static void onTListEvent(XF_VIEW_TextListEvent *evt) {
    switch (evt->type) {
        case XF_VIEW_TEXTLIST_EVENT_TYPE_SCROLL_UP: {
            if (posStrs <= 0) break;
            posStrs --;
            page_update(posStrs);
            break;
        }
        case XF_VIEW_TEXTLIST_EVENT_TYPE_SCROLL_DOWN: {
            if (posStrs >= (countStr - TLIST_COUNT)) break;
            posStrs ++;
            page_update(posStrs);
            break;
        }
        case XF_VIEW_TEXTLIST_EVENT_TYPE_SELECT: {
            break;
        }
        case XF_VIEW_TEXTLIST_EVENT_TYPE_UNSELECT: {
            XF_ViewQuit();
            break;
        }
    }
}

static void onCreate(XF_VIEW_Layout *layout) {
    mLabelTopBar = XF_VIEW_LabelNew(0, 0, STRING_REMOVE_USER);
    mTList = XF_VIEW_TextListNew(0, 16, 17, TLIST_COUNT, onTListEvent);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mTList);

    page_init();

    XF_ViewFocusUnit(mTList);
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LabelDelete(mLabelTopBar);
    XF_VIEW_TextListDelete(mTList);
}

const XF_VIEW_Layout gLayoutRemoveUser = XF_VIEW_LAYOUT_INIT(2, onCreate, onShow, onHide, onDestroy, STRING_REMOVE_USER);

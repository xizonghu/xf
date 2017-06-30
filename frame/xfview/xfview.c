#include "xftypedef.h"

#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfview.h"

static XF_VIEW_Layout *mViewLayout = XF_NULL;
static void view_process_msg(XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg);

static void XF_ViewShowLayout(XF_VIEW_Layout *layout) {
    XF_VIEW_Unit *unit = XF_NULL;

    if (XF_NULL == layout) return;

    XF_VIEW_LayoutShowClear(layout);

    for (unit = XF_VIEW_LayoutGetHeadUnit(layout); XF_NULL != unit; unit = XF_VIEW_LayoutGetNextUnit(layout, unit)) {
        XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_SHOW, 0};
        view_process_msg(unit, &msg);
    }
}

static void XF_ViewFocusLayout(XF_VIEW_Layout *layout) {
    XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS, 0};

    if (XF_NULL == layout || XF_NULL == layout->focusUnit) return;
    view_process_msg(layout->focusUnit, &msg);
}

static void XF_ViewShow(XF_VIEW_Layout *layout) {
    XF_ViewShowLayout(layout);
    XF_VIEW_LayoutShow(layout);
    //XF_ViewFocusLayout(layout);
}

static void view_process_msg(XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    uint8 res = XF_VIEW_UNIT_MESSAGE_RES_SIZE;

    if (XF_NULL == unit || XF_NULL == unit->onMessageReceiver) return;
    unit->onMessageReceiver(&res, unit, msg);
    
    switch (res) {
        case XF_VIEW_UNIT_MESSAGE_RES_UNDEFINE: {
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_RES_NEXT: {
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_RES_PREV: {
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_RES_QUIT: {
            XF_ViewQuit();
            return;
        }
    }
}


/*static void view_process_msg_key(XF_VIEW_Layout *layout, uint8 key) {

    switch (key) {
        case XF_VIEW_UNIT_KEY_ENTER: {
            break;
        }
        case XF_VIEW_UNIT_KEY_BACK: {
            break;
        }
        case XF_VIEW_UNIT_KEY_UP: {
            if (XF_NULL == XF_VIEW_LayoutFocusPrevUnit(layout)) {
                XF_ViewStop(layout);
                return;
            }
            break;
        }
        case XF_VIEW_UNIT_KEY_DOWN: {
            if (XF_NULL == XF_VIEW_LayoutFocusNextUnit(layout)) {
                XF_ViewStop(layout);
                return;
            }
            break;
        }
        default: {
            break;
        }
    }

}*/

/*static void view_process_msg(XF_VIEW_Layout *layout, XF_VIEW_UnitMessage *msg) {
    uint8 res = XF_VIEW_UNIT_MESSAGE_RES_SIZE;

    if (XF_NULL == layout) return;

    do {
        XF_VIEW_Unit *unitCurr = XF_VIEW_LayoutFocusCurrUnit(layout);
        if (XF_NULL == unitCurr || XF_NULL == unitCurr->onMessageReceiver) return;
        unitCurr->onMessageReceiver(&res, unitCurr, msg);
        switch (res) {
            case XF_VIEW_UNIT_MESSAGE_RES_UNDEFINE: {
                if (XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL == msg->type) {
                    view_process_msg_key(layout, msg->val);
                }
                break;
            }
            case XF_VIEW_UNIT_MESSAGE_RES_NEXT: {
                if (XF_NULL == XF_VIEW_LayoutFocusNextUnit(layout)) {
                    XF_ViewStop(layout);
                    return;
                }
                break;
            }
            case XF_VIEW_UNIT_MESSAGE_RES_PREV: {
                if (XF_NULL == XF_VIEW_LayoutFocusPrevUnit(layout)) {
                    XF_ViewStop(layout);
                    return;
                }
                break;
            }
            case XF_VIEW_UNIT_MESSAGE_RES_QUIT: {
                XF_ViewStop(layout);
                return;
            }
        }
        msg->type = XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS;
    } while (XF_VIEW_UNIT_MESSAGE_RES_OK != res);
}*/

static void XF_ViewDestroy() {
    XF_VIEW_Layout *parent = mViewLayout->parent;

    XF_VIEW_LayoutHide(mViewLayout);
    XF_VIEW_LayoutDestroy(mViewLayout);
    mViewLayout = parent;
}

void XF_ViewStart(XF_VIEW_Layout *layout) {
    XF_VIEW_LayoutHide(mViewLayout);

    if (XF_NULL == (layout = XF_VIEW_LayoutCreate(layout))) return;

    if (XF_NULL == mViewLayout) mViewLayout = layout;
    else {
        layout->parent = mViewLayout;
        mViewLayout = layout;
    }
    XF_ViewShow(mViewLayout);
}

void XF_ViewGoto(XF_VIEW_Layout *layout) {
    XF_ViewDestroy();
    XF_ViewStart(layout);
}

void XF_ViewMain(XF_VIEW_Layout *layout) {
    XF_ViewStart(layout);

    //XF_ViewCreate(layout);

    //XF_ViewShowLayout(mViewLayout);
    //XF_ViewFocusLayout(mViewLayout);
}

void XF_ViewFocusUnit(XF_VIEW_Unit *unit) {
    if (XF_NULL == unit) return;
    if (XF_VIEW_UNIT_VISIBALE_FALSE == unit->visible) return;

    XF_VIEW_LayoutFocusUnit(mViewLayout, unit);
    XF_ViewFocusLayout(mViewLayout);
}

void XF_ViewSetVisiable(XF_VIEW_Unit *unit, uint8 visiable) {
    uint8 res = XF_VIEW_UNIT_MESSAGE_RES_SIZE;
    XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_VISIABLE, 0};
    if (XF_NULL == unit) return;

    msg.val = visiable;
    unit->visible = visiable;
    if (unit->onMessageReceiver) unit->onMessageReceiver(&res, unit, &msg);
}

void XF_ViewQuit() {
    XF_ViewDestroy();
    XF_ViewShow(mViewLayout);
}

void XF_ViewHide() {
    XF_VIEW_LayoutHide(mViewLayout);
}

void XF_ViewFinish() {
    while (mViewLayout) {
        XF_ViewDestroy();
    }
}

void XF_ViewActionHandler(uint8 event) {
    XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL, event};
    view_process_msg(mViewLayout->focusUnit, &msg);
}

#include "xftypedef.h"

#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfview.h"

static XF_VIEW_Layout *mViewLayout = XF_NULL;
static void view_process_msg(XF_VIEW_Layout *layout, XF_VIEW_UnitMessage *msg);

static void XF_ViewCreateLayout(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout) return;

    if (layout->onCreate) layout->onCreate(layout);
}

static void XF_ViewDestroyLayout(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout) return;
    //XF_VIEW_LayoutDeleteUnits(layout);
    layout->page = 0;
    layout->posUnit = 0;
    layout->sizeUnit = 0;
    if (layout->onDestroy) layout->onDestroy(layout);
}

static void XF_ViewShowLayout(XF_VIEW_Layout *layout) {
    XF_VIEW_Unit *unit = XF_NULL;

    if (XF_NULL == layout) return;

    XF_VIEW_LayoutShowClear(layout);

    for (unit = XF_VIEW_LayoutFocusHeadUnit(layout); XF_NULL != unit; unit = XF_VIEW_LayoutFocusNextUnit(layout)) {
        XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_SHOW, 0};
        view_process_msg(layout, &msg);
    }
    if (layout->onShow) layout->onShow(layout);
    XF_VIEW_LayoutFocusHeadUnit(layout);
}

static void XF_ViewFocusLayout(XF_VIEW_Layout *layout) {
    XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS, 0};

    if (XF_NULL == layout) return;
    view_process_msg(layout, &msg);
}

static void view_process_msg_unuse(XF_VIEW_Layout *layout, XF_VIEW_UnitMessage *msg) {
    uint8 res = XF_VIEW_UNIT_MESSAGE_RES_SIZE;
    XF_VIEW_Unit *unit = XF_NULL;

    if (XF_NULL == layout) return;

    unit = XF_VIEW_LayoutFocusCurrUnit(layout);
    if (XF_NULL == unit || XF_NULL == unit->onMessageReceiver) return;
    unit->onMessageReceiver(&res, unit, msg);
}

static void view_process_msg_key(XF_VIEW_Layout *layout, uint8 key) {

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

}

static void view_process_msg(XF_VIEW_Layout *layout, XF_VIEW_UnitMessage *msg) {
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
}

void XF_ViewStart(XF_VIEW_Layout *layout) {

    layout = XF_VIEW_LayoutNew(layout);

    if (XF_NULL == layout) return;

    if (XF_NULL == mViewLayout) mViewLayout = layout;
    else {
        if (mViewLayout->onHide) mViewLayout->onHide(mViewLayout);
        layout->parent = mViewLayout;
        mViewLayout = layout;
    }

    XF_ViewCreateLayout(mViewLayout);
    XF_ViewShowLayout(mViewLayout);
    XF_ViewFocusLayout(mViewLayout);
}

void XF_ViewStop(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout) return;

    mViewLayout = layout->parent;

    XF_ViewDestroyLayout(layout);
    XF_VIEW_LayoutDelete(layout);
    XF_ViewShowLayout(mViewLayout);
    XF_ViewFocusLayout(mViewLayout);
}

void XF_ViewFocusUnit(XF_VIEW_Unit *unit) {
    if (XF_NULL == unit) return;
    if (XF_VIEW_UNIT_VISIBALE_FALSE == unit->visible) return;

    XF_VIEW_LayoutFocusUnit(mViewLayout, unit);
    XF_ViewFocusLayout(mViewLayout);
}

void XF_ViewSetVisiable(XF_VIEW_Unit *unit, uint8 visiable) {
    uint8 res = XF_VIEW_UNIT_MESSAGE_RES_SIZE;
    XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_SHOW, 0};
    if (XF_NULL == unit) return;

    unit->visible = visiable;
    if (unit->onMessageReceiver) unit->onMessageReceiver(&res, unit, &msg);
}

void XF_ViewQuit() {
    XF_ViewStop(mViewLayout);
}

void XF_ViewFinish() {
    while (mViewLayout) {
        XF_VIEW_Layout *parent = mViewLayout->parent;
        XF_ViewDestroyLayout(mViewLayout);
        XF_VIEW_LayoutDelete(mViewLayout);
        mViewLayout = parent;
    }
}

void XF_ViewActionHandler(uint8 event) {
    XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL, event};
    view_process_msg(mViewLayout, &msg);
}

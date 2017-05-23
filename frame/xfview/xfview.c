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
    if (XF_NULL == layout) return;

    //mViewLayout = layout;
    XF_VIEW_LayoutShow(layout);
    if (layout->onShow) layout->onShow(layout);
}

static void XF_ViewFocusLayout(XF_VIEW_Layout *layout) {
    XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS, 0};

    if (XF_NULL == layout) return;
    view_process_msg(layout, &msg);
}

static void view_process_msg(XF_VIEW_Layout *layout, XF_VIEW_UnitMessage *msg) {
    uint8 res = XF_VIEW_UNIT_MESSAGE_RES_SIZE;

    if (XF_NULL == layout) return;

    do {
        XF_VIEW_Unit *unitCurr = XF_VIEW_LayoutFocusCurrUnit(layout);
        if (XF_NULL == unitCurr->onMessageReceiver) return;
        unitCurr->onMessageReceiver(&res, unitCurr, msg);
        switch (res) {
            case XF_VIEW_UNIT_MESSAGE_RES_NEXT: {
                XF_VIEW_LayoutFocusNextUnit(layout);
                break;
            }
            case XF_VIEW_UNIT_MESSAGE_RES_PREV: {
                if (layout->posUnit > 0) {
                    XF_VIEW_LayoutFocusPrevUnit(layout);
                    break;
                }
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
    if (XF_NULL == layout | XF_NULL == layout->parent) return;

    mViewLayout = layout->parent;

    XF_ViewDestroyLayout(layout);
    XF_ViewShowLayout(mViewLayout);
    XF_ViewFocusLayout(mViewLayout);
}

void XF_ViewActionHandler(uint8 event) {
    XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL, event};
    view_process_msg(mViewLayout, &msg);
}

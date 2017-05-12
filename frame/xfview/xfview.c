#include "xftypedef.h"

#include "xfunit.h"
#include "xflayout.h"
#include "xfview.h"



static XF_VIEW_Layout *mViewLayout;

static void XF_ViewCreateLayout(XF_VIEW_Layout *layout) {
    if (layout->onCreate) layout->onCreate(layout);
}

static void XF_ViewDestroyLayout(XF_VIEW_Layout *layout) {
    //XF_VIEW_LayoutDeleteUnits(layout);
    if (layout->onDestroy) layout->onDestroy(layout);
}

static void XF_ViewShowLayout(XF_VIEW_Layout *layout) {
    XF_VIEW_LayoutShow(layout);
    if (layout->onShow) layout->onShow(layout);
}

/*static void view_process_msg(uint8 resPrev, uint8 resCurr, XF_VIEW_UnitMessage *msg) {
    uint8 res = 0;
    XF_VIEW_Unit *unitCurr = 0;

    switch (resCurr) {
        case XF_VIEW_UNIT_MESSAGE_RES_OK: {
            return;
        }
        case XF_VIEW_UNIT_MESSAGE_RES_NEXT: {
            XF_VIEW_LayoutFocusNextUnit(mViewLayout);
            msg.type = XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS;
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_RES_PREV: {
            XF_VIEW_LayoutFocusPrevUnit(mViewLayout);
            msg.type = XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS;
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_RES_UNFOCUS: {
            view_update_msg(XF_VIEW_UNIT_MESSAGE_RES_QUIT, resPrev, msg);
            return;
        }
        case XF_VIEW_UNIT_MESSAGE_RES_QUIT: {
            XF_ViewDestroyLayout(mViewLayout);
            mViewLayout = XF_VIEW_LayoutFocusParent(mViewLayout);
            XF_ViewCreateLayout(mViewLayout);
            XF_ViewShowLayout(mViewLayout);
            msg.type = XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS;
            break;
        }
    }
    
    unitCurr = XF_VIEW_LayoutFocusCurrUnit(mViewLayout);
    unitCurr->onMessageReceiver(&res, unitCurr, msg);
    view_update_msg(resCurr, res, msg);
}*/

static void view_process_msg(XF_VIEW_UnitMessage *msg) {
    uint8 res = XF_VIEW_UNIT_MESSAGE_RES_SIZE;

    do {
        XF_VIEW_Unit *unitCurr = XF_VIEW_LayoutFocusCurrUnit(mViewLayout);
        unitCurr->onMessageReceiver(&res, unitCurr, msg);
        switch (res) {
            case XF_VIEW_UNIT_MESSAGE_RES_NEXT: {
                XF_VIEW_LayoutFocusNextUnit(mViewLayout);
                break;
            }
            case XF_VIEW_UNIT_MESSAGE_RES_PREV: {
                if (mViewLayout->posUnit > 0) {
                    XF_VIEW_LayoutFocusPrevUnit(mViewLayout);
                    break;
                }
            }
            case XF_VIEW_UNIT_MESSAGE_RES_QUIT: {
                XF_ViewDestroyLayout(mViewLayout);
                mViewLayout = XF_VIEW_LayoutFocusParent(mViewLayout);
                XF_ViewStart(mViewLayout);
                return;
            }
        }
        msg->type = XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS;
    } while (XF_VIEW_UNIT_MESSAGE_RES_OK != res);
}

void XF_ViewStart(XF_VIEW_Layout *layout) {
    XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS, 0};
    mViewLayout = layout;

    XF_ViewCreateLayout(mViewLayout);
    XF_ViewShowLayout(mViewLayout);

    view_process_msg(&msg);
}

void XF_ViewActionHandler(uint8 event) {
    XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL, event};

    view_process_msg(&msg);
}

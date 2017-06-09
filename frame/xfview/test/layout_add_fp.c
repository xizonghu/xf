#include "xftypedef.h"

#include "language.h"
#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"

#include "layout_add_fp.h"

static XF_VIEW_Label *mLabelTopBar;
static XF_VIEW_Label *mLabelInfo;
static XF_VIEW_Label *mLabelTip;

static void onCreate(XF_VIEW_Layout *layout) {
    mLabelTopBar = XF_VIEW_LabelNew(0, 0, STRING_ADD_USER);
    mLabelInfo = XF_VIEW_LabelNew(0, 16, STRING_INPUT_PASSWD);
    mLabelTip = XF_VIEW_LabelNew(0, 48, "");

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelInfo);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTip);

    XF_ViewFocusUnit(mLabelTip);
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LabelDelete(mLabelTopBar);
    XF_VIEW_LabelDelete(mLabelInfo);
    XF_VIEW_LabelDelete(mLabelTip);
}

const XF_VIEW_Layout gLayoutAddFP = XF_VIEW_LAYOUT_INIT(5, onCreate, onShow, onHide, onDestroy, "add user");

#include "xftypedef.h"

#include "language.h"
#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"

#include "layout_reset_factory.h"

static XF_VIEW_Label *mLabelTopBar;

static void onCreate(XF_VIEW_Layout *layout) {
    mLabelTopBar = XF_VIEW_LabelNew(0, 0, STRING_RESET_SYSTEM);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);

    XF_ViewFocusUnit(mLabelTopBar);
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LabelDelete(mLabelTopBar);
}

const XF_VIEW_Layout gLayoutResetFactory = XF_VIEW_LAYOUT_INIT(8, onCreate, onShow, onHide, onDestroy, STRING_RESET_SYSTEM);

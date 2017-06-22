#include "xftypedef.h"

#include "language.h"
#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xftextedit.h"
#include "xfview.h"

#include "layout_query_trace.h"

static XF_VIEW_Label *mLabelTopBar;

static void onCreate(XF_VIEW_Layout *layout) {
    mLabelTopBar = XF_VIEW_LabelNew(0, 0, "undefined");

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);

    XF_ViewFocusUnit((XF_VIEW_Unit*)mLabelTopBar);
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LabelDelete(mLabelTopBar);
}

const XF_VIEW_Layout gLayoutQueryTrace = XF_VIEW_LAYOUT_INIT(8, onCreate, onShow, onHide, onDestroy, STRING_QUERY_TRACE);

#include "xftypedef.h"

#include "language.h"
#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xfbutton.h"
#include "xfview.h"

#include "layout_sys_version.h"

static XF_VIEW_Label *mLabelTopBar;
static XF_VIEW_Button *mButton;

static void onButtonClick(void *arg) {
    XF_ViewQuit();
}

static void onCreate(XF_VIEW_Layout *layout) {
    mLabelTopBar = XF_VIEW_LabelNew(0, 0, STRING_SYS_VERSION);
    mButton = XF_VIEW_ButtonNew(0, 16, "Ver.20170607", onButtonClick);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mButton);

    XF_ViewFocusUnit(mButton);
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LabelDelete(mLabelTopBar);
    XF_VIEW_ButtonDelete(mButton);
}

const XF_VIEW_Layout gLayoutSysVersion = XF_VIEW_LAYOUT_INIT(8, onCreate, onShow, onHide, onDestroy, STRING_SYS_VERSION);

#include "xftypedef.h"

#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xfinputkey.h"
#include "xfview.h"

#include "layout_unlock.h"
#include "layout_welcome.h"
#include "layout_manage.h"

static XF_VIEW_Label *mLabelTopBar;
static XF_VIEW_Label *mLabelInfo;
static XF_VIEW_InputKey *mInputKey;

static void onPressKey(char ch) {
    XF_ViewStart((XF_VIEW_Layout*)&gLayoutUnlock);
}

static void onCreate(XF_VIEW_Layout *layout) {
    mLabelTopBar = XF_VIEW_LabelNew(0, 0, "07-01 12:34");
    mLabelInfo = XF_VIEW_LabelNew(0, 16, "«Î ‰»Î:");
    mInputKey = XF_VIEW_InputKeyNew(onPressKey);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelInfo);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mInputKey);
}

static void onShow(XF_VIEW_Layout *layout) {
    XF_ViewFocusUnit((XF_VIEW_Unit*)mInputKey);
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)mLabelInfo);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)mInputKey);

    XF_VIEW_LabelDelete(mLabelTopBar);
    XF_VIEW_LabelDelete(mLabelInfo);
    XF_VIEW_InputKeyDelete(mInputKey);
}

const XF_VIEW_Layout gLayoutWelcome = XF_VIEW_LAYOUT_STATIC_INIT(onCreate, onShow, onHide, onDestroy, "root");

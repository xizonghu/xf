#include "xftypedef.h"

#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xftextedit.h"
#include "xfunit/xftrigger.h"

#include "layout_unlock.h"

static XF_VIEW_Label *mLabelTopBar;
static XF_VIEW_Label *mLabelInfo;
static XF_VIEW_Label *mLabelMessage;
static XF_VIEW_TextEdit *mTextPasswd;
static XF_VIEW_Trigger *mTriggerProcess;

static void onTriggerProcess(void *arg) {
}

static void onCreate(XF_VIEW_Layout *layout) {
    mLabelTopBar = XF_VIEW_LabelNew(0, 0, "07-01 12:34");
    mLabelInfo = XF_VIEW_LabelNew(0, 16, "«Î ‰»Î:");
    mLabelMessage = XF_VIEW_LabelNew(0, 32, "#########");
    mTextPasswd = XF_VIEW_TextEditNew(0, 48, XF_VIEW_TEXTEDIT_TYPE_CHAR, 16, XF_NULL);
    mTriggerProcess = XF_VIEW_TriggerNew(0, 48, onTriggerProcess);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelInfo);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelMessage);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mTextPasswd);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mTriggerProcess);

    XF_ViewFocusUnit(mLabelTopBar);
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)mLabelInfo);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)mLabelMessage);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)mTextPasswd);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)mTriggerProcess);


    XF_VIEW_LabelDelete(mLabelTopBar);
    XF_VIEW_LabelDelete(mLabelInfo);
    XF_VIEW_LabelDelete(mLabelMessage);
    XF_VIEW_TextEditDelete(mTextPasswd);
    XF_VIEW_TriggerDelete(mTriggerProcess);
}

const XF_VIEW_Layout gLayoutUnlock = XF_VIEW_LAYOUT_INIT(5, onCreate, onShow, onHide, onDestroy, "unlock");

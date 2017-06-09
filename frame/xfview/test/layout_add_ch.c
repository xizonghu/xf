#include "xftypedef.h"

#include "language.h"
#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xftextedit.h"
#include "xfview.h"

#include "layout_add_ch.h"

static XF_VIEW_Label *mLabelTopBar;
static XF_VIEW_Label *mLabelInfo;
static XF_VIEW_Label *mLabelTip;
static XF_VIEW_TextEdit *mTextPasswd;
static XF_VIEW_TextEdit *mTextPasswd2;

static void onTextPasswdStateChange(uint8 state, char *val) {
    if (XF_VIEW_TEXTEDIT_STATE_COMPLETE == state) {
        //更新界面
        XF_VIEW_TextEditSetValue(mTextPasswd, STRING_NULL);
        XF_VIEW_LabelSetValue(mLabelInfo, STRING_INPUT_AGAIN);
        XF_ViewSetVisiable(mTextPasswd, XF_VIEW_UNIT_VISIBALE_FALSE);
        XF_ViewSetVisiable(mTextPasswd2, XF_VIEW_UNIT_VISIBALE_TRUE);
        XF_ViewFocusUnit(mTextPasswd2);
    }
    else if (XF_VIEW_TEXTEDIT_STATE_BREAK == state) {
        XF_ViewQuit();
    }
}

static void onTextPasswd2StateChange(uint8 state, char *val) {
    if (XF_VIEW_TEXTEDIT_STATE_COMPLETE == state) {
    }
    else if (XF_VIEW_TEXTEDIT_STATE_BREAK == state) {
        XF_VIEW_LabelSetValue(mLabelInfo, STRING_ADD_USER);
        XF_ViewSetVisiable(mTextPasswd, XF_VIEW_UNIT_VISIBALE_TRUE);
        XF_ViewSetVisiable(mTextPasswd2, XF_VIEW_UNIT_VISIBALE_FALSE);
        XF_ViewFocusUnit(mTextPasswd);
    }
}

static void onCreate(XF_VIEW_Layout *layout) {
    mLabelTopBar = XF_VIEW_LabelNew(0, 0, STRING_ADD_PWD);
    mLabelInfo = XF_VIEW_LabelNew(0, 16, STRING_INPUT_PASSWD);
    mTextPasswd = XF_VIEW_TextEditNew(0, 32, XF_VIEW_TEXTEDIT_TYPE_CHAR, 6, onTextPasswdStateChange);
    mTextPasswd2 = XF_VIEW_TextEditNew(0, 32, XF_VIEW_TEXTEDIT_TYPE_CHAR, 6, onTextPasswd2StateChange);
    mLabelTip = XF_VIEW_LabelNew(0, 48, "");

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelInfo);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTip);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mTextPasswd);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mTextPasswd2);

    XF_ViewSetVisiable(mTextPasswd2, XF_VIEW_UNIT_VISIBALE_FALSE);
    XF_ViewFocusUnit(mTextPasswd);
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LabelDelete(mLabelTopBar);
    XF_VIEW_LabelDelete(mLabelInfo);
    XF_VIEW_LabelDelete(mLabelTip);
    XF_VIEW_TextEditDelete(mTextPasswd);
    XF_VIEW_TextEditDelete(mTextPasswd2);
}

const XF_VIEW_Layout gLayoutAddCH = XF_VIEW_LAYOUT_INIT(5, onCreate, onShow, onHide, onDestroy, STRING_ADD_PWD);

#include "string.h"
#include "xftypedef.h"

#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xftextedit.h"
#include "xfview.h"

#include "layout_manage.h"
#include "layout_unlock.h"

static XF_VIEW_Layout *mLayoutJump = XF_NULL;

static XF_VIEW_Label *mLabelTopBar;
static XF_VIEW_TextEdit *mTextPasswd;

static void onTextPasswdStateChange(uint8 state, char *val) {
    switch (state) {
        case XF_VIEW_TEXTEDIT_STATE_COMPLETE: {
            if (!strcmp("2", val)) {
                mLayoutJump = (XF_VIEW_Layout*)&gLayoutManage;
                XF_ViewQuit();
            }
            break;
        }
        case XF_VIEW_TEXTEDIT_STATE_BREAK: {
            XF_ViewQuit();
            break;
        }
    }

    if (mLayoutJump) XF_ViewStart(mLayoutJump);
}

static void onCreate(XF_VIEW_Layout *layout) {
    mLabelTopBar = XF_VIEW_LabelNew(0, 0, " ‰»Î");
    mTextPasswd = XF_VIEW_TextEditNew(0, 48, XF_VIEW_TEXTEDIT_TYPE_CHAR, 16, onTextPasswdStateChange);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mTextPasswd);

    mLayoutJump = XF_NULL;

    XF_ViewFocusUnit((XF_VIEW_Unit*)mTextPasswd);
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)mTextPasswd);

    XF_VIEW_LabelDelete(mLabelTopBar);
    XF_VIEW_TextEditDelete(mTextPasswd);
}

const XF_VIEW_Layout gLayoutUnlock = XF_VIEW_LAYOUT_STATIC_INIT(onCreate, onShow, onHide, onDestroy, "unlock");

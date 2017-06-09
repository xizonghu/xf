#include "xftypedef.h"

#include "language.h"
#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xftextedit.h"
#include "xfunit/xflisttree.h"
#include "xfview.h"

#include "layout_set_time.h"

static XF_VIEW_Label *mLabelTopBar;
static XF_VIEW_Label *mLabelDate;
static XF_VIEW_Label *mLabelDayTime;
static XF_VIEW_TextEdit *mTextYear;
static XF_VIEW_TextEdit *mTextMonth;
static XF_VIEW_TextEdit *mTextDay;
static XF_VIEW_TextEdit *mTextHour;
static XF_VIEW_TextEdit *mTextMinute;

static void onTextYearStateChange(uint8 state, char *val) {
    if (XF_VIEW_TEXTEDIT_STATE_COMPLETE == state) {
        XF_ViewFocusUnit(mTextMonth);
    }
    else if (XF_VIEW_TEXTEDIT_STATE_BREAK == state) {
        XF_ViewQuit();
    }
}

static void onTextMonthStateChange(uint8 state, char *val) {
    if (XF_VIEW_TEXTEDIT_STATE_COMPLETE == state) {
        XF_ViewFocusUnit(mTextDay);
    }
    else if (XF_VIEW_TEXTEDIT_STATE_BREAK == state) {
        XF_ViewFocusUnit(mTextYear);
    }
}

static void onTextDayStateChange(uint8 state, char *val) {
    if (XF_VIEW_TEXTEDIT_STATE_COMPLETE == state) {
        XF_ViewFocusUnit(mTextHour);
    }
    else if (XF_VIEW_TEXTEDIT_STATE_BREAK == state) {
        XF_ViewFocusUnit(mTextMonth);
    }
}

static void onTextHourStateChange(uint8 state, char *val) {
    if (XF_VIEW_TEXTEDIT_STATE_COMPLETE == state) {
        XF_ViewFocusUnit(mTextMinute);
    }
    else if (XF_VIEW_TEXTEDIT_STATE_BREAK == state) {
        XF_ViewFocusUnit(mTextDay);
    }
}

static void onTextMinuteStateChange(uint8 state, char *val) {
    if (XF_VIEW_TEXTEDIT_STATE_COMPLETE == state) {
        XF_ViewQuit();
    }
    else if (XF_VIEW_TEXTEDIT_STATE_BREAK == state) {
        XF_ViewFocusUnit(mTextHour);
    }
}

static void onCreate(XF_VIEW_Layout *layout) {
    mLabelTopBar = XF_VIEW_LabelNew(0, 0, STRING_SET_TIME);
    mLabelDate = XF_VIEW_LabelNew(0, 16, "2017Äê05ÔÂ27ÈÕ");
    mLabelDayTime = XF_VIEW_LabelNew(0, 32, "16:16");
    mTextYear = XF_VIEW_TextEditNew(16, 16, XF_VIEW_TEXTEDIT_TYPE_CHAR, 2, onTextYearStateChange);
    mTextMonth = XF_VIEW_TextEditNew(48, 16, XF_VIEW_TEXTEDIT_TYPE_CHAR, 2, onTextMonthStateChange);
    mTextDay = XF_VIEW_TextEditNew(80, 16, XF_VIEW_TEXTEDIT_TYPE_CHAR, 2, onTextDayStateChange);
    mTextHour = XF_VIEW_TextEditNew(0, 32, XF_VIEW_TEXTEDIT_TYPE_CHAR, 2, onTextHourStateChange);
    mTextMinute = XF_VIEW_TextEditNew(24, 32, XF_VIEW_TEXTEDIT_TYPE_CHAR, 2, onTextMinuteStateChange);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelDate);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelDayTime);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mTextYear);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mTextMonth);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mTextDay);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mTextHour);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mTextMinute);

    XF_ViewFocusUnit(mTextYear);
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LabelDelete(mLabelTopBar);
    XF_VIEW_LabelDelete(mLabelDate);
    XF_VIEW_LabelDelete(mLabelDayTime);
    XF_VIEW_TextEditDelete(mTextYear);
    XF_VIEW_TextEditDelete(mTextMonth);
    XF_VIEW_TextEditDelete(mTextDay);
    XF_VIEW_TextEditDelete(mTextHour);
    XF_VIEW_TextEditDelete(mTextMinute);
}

const XF_VIEW_Layout gLayoutSetTime = XF_VIEW_LAYOUT_INIT(8, onCreate, onShow, onHide, onDestroy, STRING_SET_TIME);

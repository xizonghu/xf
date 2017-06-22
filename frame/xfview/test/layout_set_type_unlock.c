#include "string.h"
#include "xftypedef.h"

#include "language.h"
#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xflist.h"
#include "xfview.h"

#include "layout_set_type_unlock.h"

static XF_VIEW_Label *mLabelTopBar;
static XF_VIEW_List *mListType;

static void onListTypeSelect(char *val) {
    if (!strcmp(val, STRING_TYPE_UNLOCK_ANY)) {
    }
    else if (!strcmp(val, STRING_TYPE_UNLOCK_FP_FP)) {
    }
    else if (!strcmp(val, STRING_TYPE_UNLOCK_FP_CH)) {
    }
    else if (!strcmp(val, STRING_TYPE_UNLOCK_CH_CH)) {
    }

    XF_ViewQuit();
}

static void onCreate(XF_VIEW_Layout *layout) {
    XF_VIEW_ListUnit *luANY = XF_VIEW_ListUnitNew(STRING_TYPE_UNLOCK_ANY);
    XF_VIEW_ListUnit *luFPFP = XF_VIEW_ListUnitNew(STRING_TYPE_UNLOCK_FP_FP);
    XF_VIEW_ListUnit *luFPCH = XF_VIEW_ListUnitNew(STRING_TYPE_UNLOCK_FP_CH);
    XF_VIEW_ListUnit *luCHCH = XF_VIEW_ListUnitNew(STRING_TYPE_UNLOCK_CH_CH);

    mLabelTopBar = XF_VIEW_LabelNew(0, 0, STRING_SET_TYPE_UNLOCK);
    mListType = XF_VIEW_ListNew(0, 16, 3, onListTypeSelect);

    XF_VIEW_ListAddUnit(mListType, luANY);
    XF_VIEW_ListAddUnit(mListType, luFPFP);
    XF_VIEW_ListAddUnit(mListType, luFPCH);
    XF_VIEW_ListAddUnit(mListType, luCHCH);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mLabelTopBar);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)mListType);

    XF_ViewFocusUnit((XF_VIEW_Unit*)mListType);
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LabelDelete(mLabelTopBar);
    XF_VIEW_ListDelete(mListType);
}

const XF_VIEW_Layout gLayoutSetTypeUnlock = XF_VIEW_LAYOUT_INIT(2, onCreate, onShow, onHide, onDestroy, STRING_SET_TYPE_UNLOCK);

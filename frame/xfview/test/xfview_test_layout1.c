#include "xftypedef.h"

#include "xfunit.h"
#include "xflayout.h"
#include "xflabel.h"
#include "xftext.h"
#include "xfbutton.h"
#include "xfview_test_layout1.h"

static void onBbuttonStorage(void *arg) {
    ;
}

static void onLoad(XF_VIEW_Layout *layout) {
    XF_VIEW_Label *labelStorage1 = XF_VIEW_LabelNew(0, 0, "Storage");
    XF_VIEW_Label *labelStorage3 = XF_VIEW_LabelNew(0, 32, "IC: 000/300");
    XF_VIEW_Text *textStorage1 = XF_VIEW_TextNew(40, 16, XF_VIEW_TEXT_TYPE_CHAR, 2);
    XF_VIEW_Label *labelStorage2 = XF_VIEW_LabelNew(0, 16, "PWD:   /50");
    XF_VIEW_Text *textStorage2 = XF_VIEW_TextNew(32, 32, XF_VIEW_TEXT_TYPE_PASSWD, 3);
    XF_VIEW_Button *buttonStorage1 = XF_VIEW_ButtonNew(0, 48, "button", onBbuttonStorage);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)labelStorage1);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)labelStorage2);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)labelStorage3);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)textStorage1);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)textStorage2);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)buttonStorage1);    
}

static void onUnload(XF_VIEW_Layout *layout) {
    ;
}

static XF_VIEW_Unit *units[7] = {0};
static XF_VIEW_Layout layout = {
    0,
    units,
    sizeof(units) / sizeof(units[0]),
    0,
    0,
    0,
    onLoad,
    onUnload,
};

XF_VIEW_Layout *layoutTest1 = &layout;  //XF_VIEW_LayoutNew(7, onLoad, onUnload);

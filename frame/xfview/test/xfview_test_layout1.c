#include "xftypedef.h"

#include "xfunit.h"
#include "xflayout.h"
#include "xflabel.h"
#include "xftext.h"
#include "xfbutton.h"
#include "xfview_test_layout1.h"

static XF_VIEW_Label *labelStorage1;
static XF_VIEW_Label *labelStorage2;
static XF_VIEW_Label *labelStorage3;
static XF_VIEW_Text *textStorage1;
static XF_VIEW_Text *textStorage2;
static XF_VIEW_Button *buttonStorage1;

static int onBbuttonStorage(void *arg) {
    return 0;
}

static void onCreate(XF_VIEW_Layout *layout) {
    labelStorage1 = XF_VIEW_LabelNew(0, 0, "Storage");  //一个界面可以智能一个label来显示静态文�?
    labelStorage2 = XF_VIEW_LabelNew(0, 16, "PWD:   /50");
    labelStorage3 = XF_VIEW_LabelNew(0, 32, "IC: 000/300");
    textStorage1 = XF_VIEW_TextNew(40, 16, XF_VIEW_TEXT_TYPE_CHAR, 2);
    textStorage2 = XF_VIEW_TextNew(32, 32, XF_VIEW_TEXT_TYPE_PASSWD, 3);
    buttonStorage1 = XF_VIEW_ButtonNew(0, 48, "button", onBbuttonStorage);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)labelStorage1);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)labelStorage2);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)textStorage1);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)labelStorage3);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)textStorage2);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)buttonStorage1);    
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)labelStorage1);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)labelStorage2);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)textStorage1);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)labelStorage3);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)textStorage2);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)buttonStorage1);  

    XF_VIEW_LabelDelete(labelStorage1);
    XF_VIEW_LabelDelete(labelStorage2);
    XF_VIEW_LabelDelete(labelStorage3);
    XF_VIEW_TextDelete(textStorage1);
    XF_VIEW_TextDelete(textStorage2);
    XF_VIEW_ButtonDelete(buttonStorage1);
}

static XF_VIEW_Unit *units[7] = {0};
static XF_VIEW_Layout layout = {
    0,
    units,
    sizeof(units) / sizeof(units[0]),
    0,
    0,
    0,
    onCreate,
    onShow,
    onHide,
    onDestroy,
    "storage"
};

XF_VIEW_Layout *layoutTest1 = &layout;  //XF_VIEW_LayoutNew(7, onLoad, onUnload);

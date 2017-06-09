#include "xftypedef.h"

#include "language.h"

#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xfbutton.h"
#include "xfview.h"

#include "layout_storage.h"

static XF_VIEW_Label *labelStorage1;
static XF_VIEW_Label *labelStorage2;
static XF_VIEW_Label *labelStorage3;
static XF_VIEW_Button *buttonStorage1;

static void onBbuttonStorage(void *arg) {
}

static void onCreate(XF_VIEW_Layout *layout) {
    labelStorage1 = XF_VIEW_LabelNew(0, 0, "Storage");  //
    labelStorage2 = XF_VIEW_LabelNew(0, 16, "PWD:   /50");
    labelStorage3 = XF_VIEW_LabelNew(0, 32, "IC: 000/300");

    buttonStorage1 = XF_VIEW_ButtonNew(0, 48, "button", onBbuttonStorage);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)labelStorage1);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)labelStorage2);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)labelStorage3);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)buttonStorage1);    
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)labelStorage1);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)labelStorage2);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)labelStorage3);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)buttonStorage1);  

    XF_VIEW_LabelDelete(labelStorage1);
    XF_VIEW_LabelDelete(labelStorage2);
    XF_VIEW_LabelDelete(labelStorage3);
    XF_VIEW_ButtonDelete(buttonStorage1);
}

const XF_VIEW_Layout gLayoutStorage = XF_VIEW_LAYOUT_INIT(7, onCreate, onShow, onHide, onDestroy, "storage");


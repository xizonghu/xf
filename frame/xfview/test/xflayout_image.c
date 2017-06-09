#include "xftypedef.h"

#include "xfimg/img_32x32_VH.h"
#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xfimage.h"
#include "xfunit/xfbutton.h"
#include "xfview.h"

#include "xflayout_image.h"

XF_VIEW_Label *labelLayout = XF_NULL;
XF_VIEW_Image *imgSmile = XF_NULL;
XF_VIEW_Button *buttonOK = XF_NULL;

static void onButtonOK(void *arg) {
    XF_ViewQuit();
}

static void onCreate(XF_VIEW_Layout *layout) {
    labelLayout = XF_VIEW_LabelNew(0, 0, "MENU");
    imgSmile = XF_VIEW_ImageNew(64, 16, (uint8*)&img32x32VH, 32, 32);
    buttonOK = XF_VIEW_ButtonNew(0, 48, "button", onButtonOK);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)labelLayout);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)imgSmile);
    //XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)buttonOK);
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LabelDelete(labelLayout);
    XF_VIEW_ImageDelete(imgSmile);
    XF_VIEW_ButtonDelete(buttonOK);
}

const XF_VIEW_Layout gLayoutImage = XF_VIEW_LAYOUT_INIT(3, onCreate, onShow, onHide, onDestroy, "image");
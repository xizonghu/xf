#include "xftypedef.h"

#include "language.h"
#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xftrigger.h"
#include "xfview.h"

#include "layout_add_user.h"

static XF_VIEW_Label *mLabelTopBar;

static void onCreate(XF_VIEW_Layout *layout) {

}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {

}

const XF_VIEW_Layout gLayoutAddUser = XF_VIEW_LAYOUT_INIT(5, onCreate, onShow, onHide, onDestroy, "add user");

#include "xftypedef.h"

#include "xfunit.h"
#include "xflayout.h"
#include "xflabel.h"
#include "xflist.h"
#include "xfview.h"
#include "xfview_test_layout1.h"
#include "xfview_test_layout2.h"

static XF_VIEW_Label *labelLayout = XF_NULL;
static XF_VIEW_List *listMenu = XF_NULL;

static void onStorageSelect(void *arg);

static void onCreate(XF_VIEW_Layout *layout) {

    XF_VIEW_ListUnit *luRoot = XF_VIEW_ListUnitNew("root", XF_NULL);
    XF_VIEW_ListUnit *luAddUser = XF_VIEW_ListUnitNew("add user", XF_NULL);
    XF_VIEW_ListUnit *luRemoveUser = XF_VIEW_ListUnitNew("remove user", XF_NULL);
    XF_VIEW_ListUnit *luSettings = XF_VIEW_ListUnitNew("settings", XF_NULL);
    XF_VIEW_ListUnit *luStorage = XF_VIEW_ListUnitNew("storage", onStorageSelect);

    XF_VIEW_ListUnit *luAddAdmin = XF_VIEW_ListUnitNew("add admin", XF_NULL);
    XF_VIEW_ListUnit *luAddGuest = XF_VIEW_ListUnitNew("add guest", XF_NULL);
    XF_VIEW_ListUnit *luAdminAddTEXT = XF_VIEW_ListUnitNew("admin passwd", XF_NULL);
    XF_VIEW_ListUnit *luAdminAddFP = XF_VIEW_ListUnitNew("admin finger", XF_NULL);
    XF_VIEW_ListUnit *luGuestAddTEXT = XF_VIEW_ListUnitNew("guest passwd", XF_NULL);
    XF_VIEW_ListUnit *luGuestAddFP = XF_VIEW_ListUnitNew("guest finger", XF_NULL);

    XF_VIEW_ListUnitAddChild(luRoot, luAddUser);
    XF_VIEW_ListUnitAddChild(luRoot, luRemoveUser);
    XF_VIEW_ListUnitAddChild(luRoot, luSettings);
    XF_VIEW_ListUnitAddChild(luRoot, luStorage);

    XF_VIEW_ListUnitAddChild(luAddUser, luAddAdmin);
    XF_VIEW_ListUnitAddChild(luAddUser, luAddGuest);

    XF_VIEW_ListUnitAddChild(luAddAdmin, luAdminAddTEXT);
    XF_VIEW_ListUnitAddChild(luAddAdmin, luAdminAddFP);

    XF_VIEW_ListUnitAddChild(luAddGuest, luGuestAddTEXT);
    XF_VIEW_ListUnitAddChild(luAddGuest, luGuestAddFP);

    labelLayout = XF_VIEW_LabelNew(0, 0, "MENU");
    listMenu = XF_VIEW_ListNew(0, 16, luRoot, 3);

    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)listMenu);
    XF_VIEW_LayoutAddUnit(layout, (XF_VIEW_Unit*)labelLayout);   
}

static void onShow(XF_VIEW_Layout *layout) {
}

static void onHide(XF_VIEW_Layout *layout) {
}

static void onDestroy(XF_VIEW_Layout *layout) {
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)listMenu);
    XF_VIEW_LayoutRemoveUnit(layout, (XF_VIEW_Unit*)labelLayout); 

    XF_VIEW_ListDelete(listMenu);
    XF_VIEW_LabelDelete(labelLayout);
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
    "menu"
};

XF_VIEW_Layout *layoutTest2 = &layout;  //XF_VIEW_LayoutNew(7, onLoad, onUnload);

static void onStorageSelect(void *arg) {
    XF_ViewStart(layoutTest1);
}
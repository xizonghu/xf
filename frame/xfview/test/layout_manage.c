#include <string.h>
#include "xftypedef.h"
#include "language.h"

#include "xfunit/xfunit.h"
#include "xfunit/xflayout.h"
#include "xfunit/xflabel.h"
#include "xfunit/xflisttree.h"
#include "xfview.h"

#include "layout_storage.h"
#include "layout_add_user.h"
#include "layout_add_ch.h"
#include "layout_set_time.h"
#include "layout_query_trace.h"
#include "layout_set_type_unlock.h"
#include "layout_remove_user.h"
#include "layout_sys_version.h"
#include "layout_reset_factory.h"

#include "layout_manage.h"

static XF_VIEW_Label *labelLayout = XF_NULL;
static XF_VIEW_ListTree *listMenu = XF_NULL;

static void onListSelect(char *val);

static void onCreate(XF_VIEW_Layout *layout) {

    XF_VIEW_ListTreeUnit *luRoot = XF_VIEW_ListTreeUnitNew("root");
    XF_VIEW_ListTreeUnit *luAddUser = XF_VIEW_ListTreeUnitNew(STRING_ADD_USER);
    XF_VIEW_ListTreeUnit *luRemoveUser = XF_VIEW_ListTreeUnitNew(STRING_REMOVE_USER);
    XF_VIEW_ListTreeUnit *luSettings = XF_VIEW_ListTreeUnitNew(STRING_SETTINGS);
    XF_VIEW_ListTreeUnit *luStorage = XF_VIEW_ListTreeUnitNew(STRING_STORAGE);

    XF_VIEW_ListTreeUnit *luAddAdmin = XF_VIEW_ListTreeUnitNew(STRING_ADD_ADMIN);
    XF_VIEW_ListTreeUnit *luAddGuest = XF_VIEW_ListTreeUnitNew(STRING_ADD_GUEST);
    XF_VIEW_ListTreeUnit *luAdminAddTEXT = XF_VIEW_ListTreeUnitNew(STRING_ADD_ADMIN_PASSWD);
    XF_VIEW_ListTreeUnit *luAdminAddFP = XF_VIEW_ListTreeUnitNew(STRING_ADD_ADMIN_FP);
    XF_VIEW_ListTreeUnit *luGuestAddTEXT = XF_VIEW_ListTreeUnitNew(STRING_ADD_GUEST_PASSWD);
    XF_VIEW_ListTreeUnit *luGuestAddFP = XF_VIEW_ListTreeUnitNew(STRING_ADD_GUEST_FP);

    //XF_VIEW_ListTreeUnit *luRemoveAdmin = XF_VIEW_ListTreeUnitNew(STRING_REMOVE_ADMIN);
    //XF_VIEW_ListTreeUnit *luRemoveGuest = XF_VIEW_ListTreeUnitNew(STRING_REMOVE_GUEST);

    XF_VIEW_ListTreeUnit *luSetTime = XF_VIEW_ListTreeUnitNew(STRING_SET_TIME);
    XF_VIEW_ListTreeUnit *luQueryTrace = XF_VIEW_ListTreeUnitNew(STRING_QUERY_TRACE);
    XF_VIEW_ListTreeUnit *luSetTypeUnlock = XF_VIEW_ListTreeUnitNew(STRING_SET_TYPE_UNLOCK);
    XF_VIEW_ListTreeUnit *luSysVersion = XF_VIEW_ListTreeUnitNew(STRING_SYS_VERSION);
    XF_VIEW_ListTreeUnit *luResetFactory = XF_VIEW_ListTreeUnitNew(STRING_RESET_FACTORY);


    XF_VIEW_ListTreeUnitAddChild(luRoot, luAddUser);
    XF_VIEW_ListTreeUnitAddChild(luRoot, luRemoveUser);
    XF_VIEW_ListTreeUnitAddChild(luRoot, luSettings);
    XF_VIEW_ListTreeUnitAddChild(luRoot, luStorage);

    XF_VIEW_ListTreeUnitAddChild(luAddUser, luAddAdmin);
    XF_VIEW_ListTreeUnitAddChild(luAddUser, luAddGuest);
    XF_VIEW_ListTreeUnitAddChild(luAddAdmin, luAdminAddTEXT);
    XF_VIEW_ListTreeUnitAddChild(luAddAdmin, luAdminAddFP);
    XF_VIEW_ListTreeUnitAddChild(luAddGuest, luGuestAddTEXT);
    XF_VIEW_ListTreeUnitAddChild(luAddGuest, luGuestAddFP);

    //XF_VIEW_ListTreeUnitAddChild(luRemoveUser, luRemoveAdmin);
    //XF_VIEW_ListTreeUnitAddChild(luRemoveUser, luRemoveGuest);

    XF_VIEW_ListTreeUnitAddChild(luSettings, luSetTime);
    XF_VIEW_ListTreeUnitAddChild(luSettings, luQueryTrace);
    XF_VIEW_ListTreeUnitAddChild(luSettings, luSetTypeUnlock);
    XF_VIEW_ListTreeUnitAddChild(luSettings, luSysVersion);
    XF_VIEW_ListTreeUnitAddChild(luSettings, luResetFactory);

    labelLayout = XF_VIEW_LabelNew(0, 0, STRING_MANAGE);
    listMenu = XF_VIEW_ListTreeNew(0, 16, luRoot, 3, onListSelect);

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

    XF_VIEW_ListTreeDelete(listMenu);
    XF_VIEW_LabelDelete(labelLayout);
}

static void onListSelect(char *val) {
    //可写一个匹配函数来优化性能
    if (!strcmp(val, STRING_STORAGE)) {
        XF_ViewStart((XF_VIEW_Layout*)&gLayoutStorage);
    }
    else if (!strcmp(val, STRING_ADD_ADMIN)) {
        //gCtrlManageAttrs.groupUser = SDB_USER_GROUP_ADMIN;
    }
    else if (!strcmp(val, STRING_ADD_GUEST)) {
        //gCtrlManageAttrs.groupUser = SDB_USER_GROUP_GUEST;
    }
    else if (!strcmp(val, STRING_ADD_ADMIN_PASSWD) || !strcmp(val, STRING_ADD_GUEST_PASSWD)) {
        //gCtrlManageAttrs.typePwd = SDB_USER_TYPE_PWD_CH;
        XF_ViewStart((XF_VIEW_Layout*)&gLayoutAddCH);
    }
    else if (!strcmp(val, STRING_ADD_ADMIN_FP) || !strcmp(val, STRING_ADD_GUEST_FP)) {
        //gCtrlManageAttrs.typePwd = SDB_USER_TYPE_PWD_FP;
        XF_ViewStart((XF_VIEW_Layout*)&gLayoutAddUser);
    }
    else if (!strcmp(val, STRING_SET_TIME)) {
        XF_ViewStart((XF_VIEW_Layout*)&gLayoutSetTime);
    }
    else if (!strcmp(val, STRING_SET_TYPE_UNLOCK)) {
        XF_ViewStart((XF_VIEW_Layout*)&gLayoutSetTypeUnlock);
    }
    else if (!strcmp(val, STRING_SYS_VERSION)) {
        XF_ViewStart((XF_VIEW_Layout*)&gLayoutSysVersion);
    }
    else if (!strcmp(val, STRING_QUERY_TRACE)) {
        XF_ViewStart((XF_VIEW_Layout*)&gLayoutQueryTrace);
    }

    else if (!strcmp(val, STRING_RESET_FACTORY)) {
        XF_ViewStart((XF_VIEW_Layout*)&gLayoutResetFactory);
    }

    else if (!strcmp(val, STRING_REMOVE_USER)) {
        XF_ViewStart((XF_VIEW_Layout*)&gLayoutRemoveUser);
    }

}

const XF_VIEW_Layout gLayoutManage = XF_VIEW_LAYOUT_INIT(3, onCreate, onShow, onHide, onDestroy, "menu");

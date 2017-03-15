#include "xfconf.h"
#include "xfea.h"
#include "view.h"
#include "viewinit.h"
#include "xfmalloc.h"
#include "mvcMain.h"

#define LIST_STATIC_UINT(name)                                     {{0, 16}, VIEW_TYPE_LIST, name, VIEW_VISIBALE_TRUE}
#define LIST_INIT_VALUE_4(name, parent, children, func)            {LIST_STATIC_UINT(name), parent, children, sizeof(children)/sizeof(children[0]), 0, 3, 0, func}
#define LIST_INIT_VALUE_3(name, parent, func)                      {LIST_STATIC_UINT(name), parent, 0, 0, 0, 3, 0, func}
#define LIST_INIT_VALUE_2(name, children)                          LIST_INIT_VALUE_3(name, children, 0)
#define LIST_INIT_VALUE_2_2(name, func)                            {LIST_STATIC_UINT(name), 0, 0, 0, 0, 3, 0, func}

#define CHILREN_SIZE_ADD_ADMIN                                        2
#define CHILREN_SIZE_ADD_GUEST                                        2
#define CHILREN_SIZE_ADD_USER                                         2
#define CHILREN_SIZE_SETTINGS                                         5
#define CHILREN_SIZE_REMOVE_USER                                      2
#define CHILREN_SIZE_MAIN                                             4
#define CHILREN_SIZE_LAYOUT                                           2

extern VIEW_Layout vStorage;


void onListAdminAddTEXT(void *arg);
void onListAdminAddFP(void *arg);
void onListGuestAddFP(void *arg);
void onListGuestAddTEXT(void *arg);
void onListStorage(void *arg);

void vManage_init(VIEW_Layout *layout);
void vManage_exit(VIEW_Layout *layout);

VIEW_Layout vManage = {
    {{0, 0}, VIEW_TYPE_LAYOUT, "manage", VIEW_VISIBALE_TRUE},
    {128,64},
    0,
    0,
    0,
    0,
    0,
    vManage_init,
    vManage_exit,
};

void vManage_init(VIEW_Layout *layout) {
    VIEW_ListSubmit *submitAdminAddTEXT = (VIEW_ListSubmit *)XF_malloc(sizeof(VIEW_ListSubmit));
    VIEW_ListSubmit *submitAdminAddFP = (VIEW_ListSubmit *)XF_malloc(sizeof(VIEW_ListSubmit));
    VIEW_ListSubmit *submitGuestAddFP = (VIEW_ListSubmit *)XF_malloc(sizeof(VIEW_ListSubmit));
    VIEW_ListSubmit *submitGuestAddTEXT = (VIEW_ListSubmit *)XF_malloc(sizeof(VIEW_ListSubmit));
    VIEW_ListSubmit *submitStorage = (VIEW_ListSubmit *)XF_malloc(sizeof(VIEW_ListSubmit));
    VIEW_ListSubmit *submitSettings = (VIEW_ListSubmit *)XF_malloc(sizeof(VIEW_ListSubmit));
    VIEW_ListSubmit *submitRemoveUser = (VIEW_ListSubmit *)XF_malloc(sizeof(VIEW_ListSubmit));
    VIEW_ListOption *optionAddAdmin = (VIEW_ListOption *)XF_malloc(sizeof(VIEW_ListOption));
    VIEW_ListOption *optionAddGuest = (VIEW_ListOption *)XF_malloc(sizeof(VIEW_ListOption));
    VIEW_ListOption *optionAddUser = (VIEW_ListOption *)XF_malloc(sizeof(VIEW_ListOption));
    VIEW_ListOption *optionSettings = (VIEW_ListOption *)XF_malloc(sizeof(VIEW_ListOption));
    VIEW_ListOption *optionRemoveUser = (VIEW_ListOption *)XF_malloc(sizeof(VIEW_ListOption));
    VIEW_ListOption *optionMain = (VIEW_ListOption *)XF_malloc(sizeof(VIEW_ListOption));
    VIEW_ListOption *listMain = (VIEW_List *)XF_malloc(sizeof(VIEW_List));
    VIEW_Label *labelMain = (VIEW_Label *)XF_malloc(sizeof(VIEW_List));

    VIEW_Unit **units = (VIEW_Unit **)XF_malloc(sizeof(VIEW_Unit *) * CHILREN_SIZE_LAYOUT);

    units[0] = (VIEW_Unit *)labelMain;
    units[1] = (VIEW_Unit *)listMain;

    view_listsubmit_init(submitAdminAddTEXT, "admin passwd", optionAddAdmin, 0, onListAdminAddTEXT);
    view_listsubmit_init(submitAdminAddFP, "admin finger", optionAddAdmin, submitAdminAddTEXT, onListAdminAddFP);
    view_listsubmit_init(submitGuestAddFP, "guest finger", optionAddGuest, submitGuestAddTEXT, onListGuestAddFP);
    view_listsubmit_init(submitGuestAddTEXT, "guest passwd", optionAddGuest, 0, onListGuestAddTEXT);
    view_listsubmit_init(submitRemoveUser, "submitRemoveUser", optionRemoveUser, 0, 0);
    view_listsubmit_init(submitSettings, "guest submitSettings", optionSettings, 0, 0);

    view_listoption_init(optionAddAdmin, "add admin", optionAddUser, submitAdminAddFP, optionAddGuest);
    view_listoption_init(optionAddGuest, "add guest", optionAddUser, submitGuestAddFP, 0);
    view_listoption_init(optionAddUser, "add user", optionMain, optionAddAdmin, optionRemoveUser);
    view_listoption_init(optionRemoveUser, "remove user", optionMain, submitRemoveUser, optionSettings);
	view_listoption_init(optionSettings, "settings", optionMain, submitSettings, submitStorage);
    view_listsubmit_init(submitStorage, "storage", optionMain, 0, onListStorage);
    view_listoption_init(optionMain, "option", 0, optionAddUser, 0);
    view_list_init(listMain, 0, 16, "list", optionMain, 3);
    view_label_init(labelMain, 0, 0, "Manage Menu");

    view_layout_init(layout, 0, units, CHILREN_SIZE_LAYOUT);
}

void vManage_exit(VIEW_Layout *layout) {
    view_layout_exit(layout);
}

static void onListAdminAddTEXT(void *arg) {
}
static void onListAdminAddFP(void *arg) {
}
static void onListGuestAddFP(void *arg) {
}
static void onListGuestAddTEXT(void *arg) {
}
static void onListStorage(void *arg) {
    ViewCreate(&vManage, &vStorage);
}


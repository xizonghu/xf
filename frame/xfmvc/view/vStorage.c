#include "xfconf.h"
#include "xfea.h"
#include "view.h"
#include "mvcMain.h"

void onBbuttonStorage(void *arg);

static char str1[3] = {0}, str2[4] = {0};

static VIEW_Label labelStorage = LABEL_NEW(0, 0, "Storage");
static VIEW_Label labelStorage1 = LABEL_NEW(0, 16, "FP: 23/100");
static VIEW_Label labelStorage2 = LABEL_NEW(0, 32, "PWD: 32/50");
static VIEW_Label labelStorage3 = LABEL_NEW(0, 48, "IC: 000/300");
static VIEW_Text textStorage1 = TEXT_NEW(40, 32, VIEW_TEXT_TYPE_TEXT, str1);
static VIEW_Text textStorage2 = TEXT_NEW(32, 48, VIEW_TEXT_TYPE_PWD, str2);

static VIEW_Button buttonStorage = BUTTON_NEW(0, 48, "", onBbuttonStorage);

static VIEW_Unit *units[] = {&labelStorage, &labelStorage1, &labelStorage2, &labelStorage3, &textStorage1, &textStorage2, &buttonStorage};
VIEW_Layout vStorage = {
    {{0, 0}, VIEW_TYPE_LAYOUT, "vStorage", VIEW_VISIBALE_TRUE},
    {128,64},
    0,
    units,
    sizeof(units)/sizeof(units[0]),
    0,
    0,
    0,
};

static void onBbuttonStorage(void *arg) {
    ViewQuit();
}

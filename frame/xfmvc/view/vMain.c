#include "view.h"

typedef struct {
    
} MAIN_MEMORY;

static MAIN_MEMORY = {
    
};

static int textComplete(void *arg) {
    //cUnlock.unlock(FP_Pwd * pwd);
}


static VIEW_Lable viewLine1 = {{{0, 1}, VIEW_TYPE_LABLE, "«Î ‰»Î:", VIEW_VISIBALE_TRUE}};
static VIEW_Lable viewLine2 = {{{0, 2}, VIEW_TYPE_LABLE, 0, VIEW_VISIBALE_FALSE}};
static VIEW_Text viewLine3 = {{{0, 3}, VIEW_TYPE_TEXT, 0, VIEW_VISIBALE_FALSE}, textComplete};
static VIEW_Loop viewLoop = {{{0, 0}, VIEW_TYPE_LOOP, 0, VIEW_VISIBALE_TRUE}, cUnlock.scan};
static VIEW_Unit *viewMain[] = {&viewLine1, &viewLine2, &viewLine3};

static VIEW_Layout layoutMain = {
    viewMain,
};


int vMain() {
    ViewShow(&layoutMain);
    
}

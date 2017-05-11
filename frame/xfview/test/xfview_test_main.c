#include "xftypedef.h"
#include "xfevent.h"

#include "xfunit.h"
#include "xflayout.h"
#include "xfview.h"
#include "xfview_test_layout1.h"
#include "xfview_test_main.h"

#define EVENTKB_INFO_SIZE          2
#define EVENTKB_ACTION_SIZE        3

#define EVENTFP_INFO_SIZE          1
#define EVENTFP_ACTION_SIZE        1

#define EVENTTR_INFO_SIZE          1
#define EVENTTR_ACTION_SIZE        5

static void view_click_handler(XF_EventInfo *info);

XF_EventHandler *HandlerKB[3] = {0};
XF_Event EventKB = {
    XF_EVENT_STATE_LISTEN,
    {0},
    HandlerKB,
    sizeof(HandlerKB) / sizeof(HandlerKB[0]),
};
XF_EventHandler ViewHandler = {
    "view click",
    view_click_handler,
};
XF_Event *events[1] = {&EventKB};
XF_EventContainer eventContainer = {
    events,
    1,
};

void xfview_test_main() {
    XF_EventAddHandler(&EventKB, &ViewHandler);

    XF_ViewStart(layoutTest1);  //显示界面
    while (1) XF_EventContainerPolling(&eventContainer);
}

static void view_click_handler(XF_EventInfo *info) {
    char ch = info->type;
    XF_ViewActionHandler(ch);  //界面事件处理函数
}
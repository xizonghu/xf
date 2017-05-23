#include "xftypedef.h"
#include "xfevent.h"

#include "xfbgraph.h"
#include "xffont.h"
#include "xffont/font_8x16_VH.h"
#include "xffont/font_8x16_H.h"
#include "xftextout.h"
#include "xfunit.h"
#include "xflayout.h"
#include "xfview.h"
#include "xfview_test_layout2.h"
#include "xfview_test_main.h"

#define EVENTKB_INFO_SIZE          2
#define EVENTKB_ACTION_SIZE        3

#define EVENTFP_INFO_SIZE          1
#define EVENTFP_ACTION_SIZE        1

#define EVENTTR_INFO_SIZE          1
#define EVENTTR_ACTION_SIZE        5

static void view_click_handler(XF_EventInfo *info);

//static uint8 gfbVH[64/8][128] = {0};
static uint8 gfbVH[64][128/8] = {0};

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

void xfview_test_main() {

    XF_BgraphInit(&globalGraph, (uint8*)gfbVH, 128, 64);
    XF_TextoutInit(&globalTextout, &globalGraph, &font8x16VH, &fontCN16x16VH);
    //XF_TextoutInit(&globalTextout, &globalGraph, &font8x16H, 0);
    //XF_TextoutPrint(&globalTextout, 0, 0, "hello world", XF_BGRAPH_FILL_NORMAL);
    //XF_TextoutPrint(&globalTextout, 13, 13, "hello world", XF_BGRAPH_FILL_NORMAL);
    XF_TextoutPrint(&globalTextout, 13, 13, "请输入密码.", XF_BGRAPH_FILL_NORMAL);
    XF_BgraphFlush(&globalGraph);

    XF_EventAddHandler(&EventKB, &ViewHandler);

    XF_ViewStart(layoutTest2);  //显示界面
    while (1) XF_EventPolling(&EventKB);
}

static void view_click_handler(XF_EventInfo *info) {
    char ch = info->type;
    XF_ViewActionHandler(ch);  //界面事件处理函数
}
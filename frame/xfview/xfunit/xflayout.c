#include "xftypedef.h"
#include "xfbgraph.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xflayout.h"

/*static int8 indexOf(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
    uint8 i = 0;
    return -1;
}*/

static void layout_clear() {
    XF_BgraphClear(&globalGraph);
    XF_BgraphFlush(&globalGraph);
}

/*static void layout_show(XF_VIEW_Layout *layout) {
}*/

void XF_VIEW_LayoutShow(XF_VIEW_Layout *layout) {
    layout_clear();
    XF_VIEW_LayoutShowUnits(layout);
}

XF_VIEW_Layout *XF_VIEW_LayoutNew(attr sizeChild, void (*onLoad)(struct XF_VIEW_LAYOUT_S *layout), void (*onUnload)(struct XF_VIEW_LAYOUT_S *layout)) {
    return XF_NULL;
}

void XF_VIEW_LayoutDelete(XF_VIEW_Layout *layout) {
}

void XF_VIEW_LayoutAddUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
    if (layout->sizeUnit >= layout->maxUnit - 1) return;
    layout->units[layout->sizeUnit++] = unit;
}

void XF_VIEW_LayoutRemoveUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
}

void XF_VIEW_LayoutShowUnits(XF_VIEW_Layout *layout) {
    uint8 pos = 0;
    for (pos = 0; pos < layout->sizeUnit; pos++) {
        XF_VIEW_Unit *unit = layout->units[pos];
        uint8 res = XF_VIEW_UNIT_MESSAGE_RES_SIZE;
        XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_SHOW, 0};
        unit->onMessageReceiver(&res, unit, &msg);
    }
}

void XF_VIEW_LayoutDeleteUnits(XF_VIEW_Layout *layout) {
    uint8 pos = 0;
    for (pos = 0; pos < layout->sizeUnit; pos++) {
        XF_VIEW_Unit *unit = layout->units[pos];
        uint8 res = XF_VIEW_UNIT_MESSAGE_RES_SIZE;
        XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_DELETE, 0};
        unit->onMessageReceiver(&res, unit, &msg);
    }
}

XF_VIEW_Unit *XF_VIEW_LayoutFocusPrevUnit(XF_VIEW_Layout *layout) {
    if (layout->posUnit <= 0) return layout->units[0];

    layout->posUnit--;
    return layout->units[layout->posUnit];
}

XF_VIEW_Unit *XF_VIEW_LayoutFocusCurrUnit(XF_VIEW_Layout *layout) {
    return layout->units[layout->posUnit];
}

XF_VIEW_Unit *XF_VIEW_LayoutFocusNextUnit(XF_VIEW_Layout *layout) {
    if (layout->posUnit >= (layout->sizeUnit - 1))  return layout->units[layout->sizeUnit - 1];

    layout->posUnit++;
    return layout->units[layout->posUnit];
}

XF_VIEW_Layout *XF_VIEW_LayoutFocusParent(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout->parent) return layout;

    XF_VIEW_LayoutDeleteUnits(layout);

    return layout->parent;
}

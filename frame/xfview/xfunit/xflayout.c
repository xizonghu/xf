#include <string.h>

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
    //XF_BgraphFlush(&globalGraph);
}

/*static void layout_show(XF_VIEW_Layout *layout) {
}*/

static XF_VIEW_Unit *layout_get_unit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
    XF_VIEW_Unit *posUnit = XF_NULL;
    if (XF_NULL == layout || XF_NULL == unit) return XF_NULL;
    for (posUnit = layout->units; XF_NULL != posUnit; posUnit = posUnit->next) {
        if (posUnit == unit) return posUnit;
    }
    return XF_NULL;
}

static XF_VIEW_Unit *layout_get_unit_prev(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
    XF_VIEW_Unit *prevUnit = XF_NULL;
    if (XF_NULL == layout || XF_NULL == unit) return XF_NULL;
    if (XF_NULL == layout->units) return XF_NULL;
    for (prevUnit = layout->units; XF_NULL != prevUnit->next; prevUnit = prevUnit->next) {
        if (prevUnit->next == unit) return prevUnit;
    }
    return XF_NULL;
}

void XF_VIEW_LayoutShowClear(XF_VIEW_Layout *layout) {
    layout_clear();
}

XF_VIEW_Layout *XF_VIEW_LayoutNew(XF_VIEW_Layout *base) {
    XF_VIEW_Layout *layout = XF_NULL;

    if (XF_NULL == (layout = (XF_VIEW_Layout *)XF_malloc(sizeof(XF_VIEW_Layout)))) return XF_NULL;

    memcpy(layout, base, sizeof(XF_VIEW_Layout));

    return layout;
}

XF_VIEW_Layout *XF_VIEW_LayoutDuplicate(XF_VIEW_Layout *layout) {
    XF_VIEW_Layout *layoutDuplicate = XF_NULL;

    if (XF_NULL == (layoutDuplicate = (XF_VIEW_Layout *)XF_malloc(sizeof(XF_VIEW_Layout)))) return XF_NULL;

    //layoutDuplicate->maxUnit = layout->maxUnit;
    //layoutDuplicate->name = layout->name;
    //layoutDuplicate->page = layout->page;
    //layoutDuplicate->parent = layout->parent;
    //layoutDuplicate->posUnit = layout->posUnit;
    //layoutDuplicate->sizeUnit = layout->sizeUnit;
    //layoutDuplicate->units = layout->units;
    *layoutDuplicate = *layout;

    return layoutDuplicate;
}

void XF_VIEW_LayoutDelete(XF_VIEW_Layout *layout) {
    XF_free(layout);
}

void XF_VIEW_LayoutAddUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
    XF_VIEW_Unit *posUnit = XF_NULL;

    if (XF_NULL == layout || XF_NULL == unit) return;
    if (XF_NULL == layout->units) {
        layout->units = unit;
        unit->next = XF_NULL;
        layout->focusUnit = layout->units;
        return;
    }

    for (posUnit = layout->units; XF_NULL != posUnit->next; posUnit = posUnit->next);
    posUnit->next = unit;
    unit->next = XF_NULL;
}

void XF_VIEW_LayoutRemoveUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
}

//不建议在除了xfview以外的地方使用unit的onMessageReceiver
/*void XF_VIEW_LayoutShowUnits(XF_VIEW_Layout *layout) {
    uint8 pos = 0;
    XF_VIEW_Unit *unit = layout->units[pos];

    while (XF_NULL != unit) {
        uint8 res = XF_VIEW_UNIT_MESSAGE_RES_SIZE;
        XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_SHOW, 0};
        unit->onMessageReceiver(&res, unit, &msg);
        unit = layout->units[++pos];
    }
}*/

/*void XF_VIEW_LayoutDeleteUnits(XF_VIEW_Layout *layout) {
    uint8 pos = 0;
    XF_VIEW_Unit *unit = layout->units[pos];

    while (XF_NULL != unit) {
        uint8 res = XF_VIEW_UNIT_MESSAGE_RES_SIZE;
        XF_VIEW_UnitMessage msg = {XF_VIEW_UNIT_MESSAGE_TYPE_DELETE, 0};
        unit->onMessageReceiver(&res, unit, &msg);
        unit = layout->units[++pos];
    }
}*/

XF_VIEW_Unit * XF_VIEW_LayoutFocusUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
    uint8 pos = 0;
    uint8 posUnitBak = 0;
    XF_VIEW_Unit *curr = XF_NULL;

    if (XF_NULL == layout || XF_NULL == unit) return XF_NULL;

    if (curr = layout_get_unit(layout, unit)) layout->focusUnit = curr;
    return curr;
}

XF_VIEW_Unit *XF_VIEW_LayoutGetHeadUnit(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout) return XF_NULL;

    return layout->units;
}

XF_VIEW_Unit *XF_VIEW_LayoutGetPrevUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
    if (XF_NULL == layout || XF_NULL == unit) return XF_NULL;
    return layout_get_unit_prev(layout, unit);
}

XF_VIEW_Unit *XF_VIEW_LayoutGetNextUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
    XF_VIEW_Unit *next = XF_NULL;
    if (XF_NULL == layout || XF_NULL == unit) return XF_NULL;

    if(XF_NULL == (next = layout_get_unit(layout, unit))) return XF_NULL;
    return next->next;
}

XF_VIEW_Layout *XF_VIEW_LayoutCreate(XF_VIEW_Layout *base) {
    XF_VIEW_Layout *layout = XF_NULL;
    if (XF_NULL == (layout = XF_VIEW_LayoutDuplicate(base))) return XF_NULL;
    if (layout->onCreate) layout->onCreate(layout);
    return layout;
}

void XF_VIEW_LayoutShow(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout) return;
    if (layout->onShow) layout->onShow(layout);
}

void XF_VIEW_LayoutHide(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout) return;
    if (layout->onHide) layout->onHide(layout);
}

void XF_VIEW_LayoutDestroy(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout) return;
    if (layout->onDestroy) layout->onDestroy(layout);

    XF_VIEW_LayoutDelete(layout);
}

//以下为废弃历史函数
/*XF_VIEW_Unit *XF_VIEW_LayoutFocusCurrUnit(XF_VIEW_Layout *layout) {
    return layout->focusUnit;
}*/

/*XF_VIEW_Unit *XF_VIEW_LayoutFocusHeadUnit(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout) return XF_NULL;
    return layout->units;
}*/

/*XF_VIEW_Unit *XF_VIEW_LayoutFocusPrevUnit(XF_VIEW_Layout *layout) {
    XF_VIEW_Unit *prev = XF_NULL;
    if (XF_NULL == layout) return XF_NULL;
    if (prev = layout_get_uint_prev(layout, layout->focusUnit)) {
        layout->focusUnit = prev;
        return layout->focusUnit;
    }

    return XF_NULL;
}*/

/*XF_VIEW_Unit *XF_VIEW_LayoutFocusNextUnit(XF_VIEW_Layout *layout) {
    XF_VIEW_Unit *next = XF_NULL;
    if (XF_NULL == layout || XF_NULL == layout->focusUnit) return XF_NULL;

    if (next = layout->focusUnit->next) {
        layout->focusUnit = next;
        return layout->focusUnit;
    }

    return XF_NULL;
}*/

/*XF_VIEW_Layout *XF_VIEW_LayoutFocusParent(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout->parent) return XF_NULL;

    XF_VIEW_LayoutDeleteUnits(layout);

    return layout->parent;
}*/

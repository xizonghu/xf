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

static uint8 indexOf(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
    uint8 pos = 0;
    for (pos = 0; pos < layout->sizeUnit; pos++) {
        XF_VIEW_Unit *unitTemp = layout->units[pos];
        if (unitTemp == unit) break;
    }

    return pos;
}

void XF_VIEW_LayoutShow(XF_VIEW_Layout *layout) {
    //layout_clear();
    //XF_VIEW_LayoutShowUnits(layout);
}

void XF_VIEW_LayoutShowClear(XF_VIEW_Layout *layout) {
    layout_clear();
}

XF_VIEW_Layout *XF_VIEW_LayoutNew(XF_VIEW_Layout *base) {
    XF_VIEW_Layout *layout = XF_NULL;
    XF_VIEW_Unit **units = XF_NULL;

    if (XF_NULL == (layout = (XF_VIEW_Layout *)XF_malloc(sizeof(XF_VIEW_Layout)))) return XF_NULL;

    if (XF_NULL == (units = (XF_VIEW_Unit**)XF_malloc(sizeof(XF_VIEW_Unit)*base->sizeUnit))) {
        XF_free(layout);
        return XF_NULL;
    }

    memcpy(layout, base, sizeof(XF_VIEW_Layout));
    memset(units, 0, sizeof(XF_VIEW_Unit)*base->sizeUnit);
    layout->units = units;
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
    memcpy(layoutDuplicate, layout, sizeof(XF_VIEW_Layout));

    return layoutDuplicate;
}

void XF_VIEW_LayoutDelete(XF_VIEW_Layout *layout) {
    XF_free(layout->units);
    XF_free(layout);
}

void XF_VIEW_LayoutAddUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
    uint8 pos = indexOf(layout, XF_NULL);

    if (layout->sizeUnit <= pos) return;
    layout->units[pos] = unit;
}

void XF_VIEW_LayoutRemoveUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit) {
}

//不建议在除了xfview意外的地方使用unit的onMessageReceiver
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

    posUnitBak = layout->posUnit;
    layout->posUnit = 0;
    curr = layout->units[layout->posUnit];

    while (XF_NULL != curr) {
        if (curr == unit) {
            layout->posUnit = pos;
            return curr;
        }
        curr = layout->units[++pos];
    }

    layout->posUnit = posUnitBak;
    return XF_NULL;
}

XF_VIEW_Unit *XF_VIEW_LayoutFocusHeadUnit(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout) return XF_NULL;
    layout->posUnit = 0;
    return layout->units[layout->posUnit];
}

XF_VIEW_Unit *XF_VIEW_LayoutFocusPrevUnit(XF_VIEW_Layout *layout) {
    if (layout->posUnit <= 0) return XF_NULL;  //layout->units[0];

    layout->posUnit--;
    return layout->units[layout->posUnit];
}

XF_VIEW_Unit *XF_VIEW_LayoutFocusCurrUnit(XF_VIEW_Layout *layout) {
    return layout->units[layout->posUnit];
}

XF_VIEW_Unit *XF_VIEW_LayoutFocusNextUnit(XF_VIEW_Layout *layout) {
    if (layout->posUnit >= (layout->sizeUnit - 1))  return XF_NULL;  //layout->units[layout->sizeUnit - 1];

    layout->posUnit++;
    return layout->units[layout->posUnit];
}

/*XF_VIEW_Layout *XF_VIEW_LayoutFocusParent(XF_VIEW_Layout *layout) {
    if (XF_NULL == layout->parent) return XF_NULL;

    XF_VIEW_LayoutDeleteUnits(layout);

    return layout->parent;
}*/

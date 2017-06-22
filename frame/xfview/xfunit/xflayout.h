#ifndef __XF_LAYOUT_H__
#define __XF_LAYOUT_H__

//layout的生命周期onCreate() -> onShow() <-> onHide() -> onDestroy()

#define XF_VIEW_LAYOUT_INIT(sizeUnit, onCreate, onShow, onHide, onDestroy, name)    {0,0,0,onCreate,onShow,onHide,onDestroy,name}
#define XF_VIEW_LAYOUT_STATIC_INIT(onCreate, onShow, onHide, onDestroy, name)    {0,0,0,onCreate,onShow,onHide,onDestroy,name}

typedef struct XF_VIEW_LAYOUT_S {
    //XF_VIEW_Unit super;
    struct XF_VIEW_LAYOUT_S *parent;
    XF_VIEW_Unit *units;
    XF_VIEW_Unit *focusUnit;
    //attr sizeUnit;
    //attr posUnit;
    //attr page;
    void (*onCreate)(struct XF_VIEW_LAYOUT_S *layout);  //创建完成时调用
    void (*onShow)(struct XF_VIEW_LAYOUT_S *layout);  //显示完成时调用
    void (*onHide)(struct XF_VIEW_LAYOUT_S *layout);  //隐藏完成时调用
    void (*onDestroy)(struct XF_VIEW_LAYOUT_S *layout);  //销毁完成时调用
    char *name; //标识,可以优化掉
} XF_VIEW_Layout;

extern XF_VIEW_Layout *XF_VIEW_LayoutNew(XF_VIEW_Layout *base);
extern XF_VIEW_Layout *XF_VIEW_LayoutDuplicate(XF_VIEW_Layout *layout);
extern void XF_VIEW_LayoutDelete(XF_VIEW_Layout *layout);

extern void XF_VIEW_LayoutAddUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit);
extern void XF_VIEW_LayoutRemoveUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit);
extern void XF_VIEW_LayoutShowUnits(XF_VIEW_Layout *layout);
extern void XF_VIEW_LayoutDeleteUnits(XF_VIEW_Layout *layout);

extern void XF_VIEW_LayoutShow(XF_VIEW_Layout *layout);
extern void XF_VIEW_LayoutShowClear(XF_VIEW_Layout *layout);

extern XF_VIEW_Unit *XF_VIEW_LayoutFocusUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit);
extern XF_VIEW_Unit *XF_VIEW_LayoutGetHeadUnit(XF_VIEW_Layout *layout);
extern XF_VIEW_Unit *XF_VIEW_LayoutGetPrevUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit);
extern XF_VIEW_Unit *XF_VIEW_LayoutGetNextUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit);

extern XF_VIEW_Layout *XF_VIEW_LayoutCreate(XF_VIEW_Layout *base);
extern void XF_VIEW_LayoutShow(XF_VIEW_Layout *layout);
extern void XF_VIEW_LayoutHide(XF_VIEW_Layout *layout);
extern void XF_VIEW_LayoutDestroy(XF_VIEW_Layout *layout);

//extern XF_VIEW_Unit *XF_VIEW_LayoutFocusHeadUnit(XF_VIEW_Layout *layout);
//extern XF_VIEW_Unit *XF_VIEW_LayoutFocusPrevUnit(XF_VIEW_Layout *layout);
//extern XF_VIEW_Unit *XF_VIEW_LayoutFocusCurrUnit(XF_VIEW_Layout *layout);
//extern XF_VIEW_Unit *XF_VIEW_LayoutFocusNextUnit(XF_VIEW_Layout *layout);
//extern XF_VIEW_Layout *XF_VIEW_LayoutFocusParent(XF_VIEW_Layout *layout);

#endif

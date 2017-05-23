#ifndef __XF_LAYOUT_H__
#define __XF_LAYOUT_H__

//layout的生命周期onCreate() -> onShow() <-> onHide() -> onDestroy()

typedef struct XF_VIEW_LAYOUT_S {
    //XF_VIEW_Unit super;
    struct XF_VIEW_LAYOUT_S *parent;
    XF_VIEW_Unit **units;
    attr maxUnit;  //可以优化掉
    attr sizeUnit;
    attr posUnit;
    attr page;
    void (*onCreate)(struct XF_VIEW_LAYOUT_S *layout);  //创建完成时调用
    void (*onShow)(struct XF_VIEW_LAYOUT_S *layout);  //显示完成时调用
    void (*onHide)(struct XF_VIEW_LAYOUT_S *layout);  //隐藏完成时调用
    void (*onDestroy)(struct XF_VIEW_LAYOUT_S *layout);  //销毁完成时调用
    char *name;
} XF_VIEW_Layout;

extern XF_VIEW_Layout *XF_VIEW_LayoutNew(attr sizeChild, void (*onLoad)(struct XF_VIEW_LAYOUT_S *layout), void (*onUnload)(struct XF_VIEW_LAYOUT_S *layout));
extern void XF_VIEW_LayoutDelete(XF_VIEW_Layout *layout);

extern void XF_VIEW_LayoutAddUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit);
extern void XF_VIEW_LayoutRemoveUnit(XF_VIEW_Layout *layout, XF_VIEW_Unit *unit);
extern void XF_VIEW_LayoutShowUnits(XF_VIEW_Layout *layout);
extern void XF_VIEW_LayoutDeleteUnits(XF_VIEW_Layout *layout);

extern void XF_VIEW_LayoutShow(XF_VIEW_Layout *layout);

extern XF_VIEW_Unit *XF_VIEW_LayoutFocusPrevUnit(XF_VIEW_Layout *layout);
extern XF_VIEW_Unit *XF_VIEW_LayoutFocusCurrUnit(XF_VIEW_Layout *layout);
extern XF_VIEW_Unit *XF_VIEW_LayoutFocusNextUnit(XF_VIEW_Layout *layout);
extern XF_VIEW_Layout *XF_VIEW_LayoutFocusParent(XF_VIEW_Layout *layout);

#endif

#ifndef __XF_LAYOUT_H__
#define __XF_LAYOUT_H__

//layout����������onCreate() -> onShow() <-> onHide() -> onDestroy()

typedef struct XF_VIEW_LAYOUT_S {
    //XF_VIEW_Unit super;
    struct XF_VIEW_LAYOUT_S *parent;
    XF_VIEW_Unit **units;
    attr maxUnit;  //�����Ż���
    attr sizeUnit;
    attr posUnit;
    attr page;
    void (*onCreate)(struct XF_VIEW_LAYOUT_S *layout);  //�������ʱ����
    void (*onShow)(struct XF_VIEW_LAYOUT_S *layout);  //��ʾ���ʱ����
    void (*onHide)(struct XF_VIEW_LAYOUT_S *layout);  //�������ʱ����
    void (*onDestroy)(struct XF_VIEW_LAYOUT_S *layout);  //�������ʱ����
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

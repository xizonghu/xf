#ifndef __XF_VIEW_H__
#define __XF_VIEW_H__

//基于xfbgraph, xfmalloc(可将与xfmalloc有关的函数放在另一个c文件中实现)的一套单色UI。
//建议与xfevent结合构成系统

typedef enum XF_VIEW_MESSAGE_TYPE_E {
    XF_VIEW_EVENT_FOCUS_NEXT = 1,
    XF_VIEW_EVENT_FOCUS_PREV,
    XF_VIEW_EVENT_SELECT,
    XF_VIEW_EVENT_QUIT,
} XF_ViewMessageType;

typedef struct XF_VIEW_MESSAGE_S {
    uint8 type;
    uint8 value;
} XF_ViewMessage;

//框架接口
extern void XF_ViewMain(XF_VIEW_Layout *layout);    //主窗口
extern void XF_ViewStart(XF_VIEW_Layout *layout);   //新打开一个窗口
extern void XF_ViewGoto(XF_VIEW_Layout *layout);    //退出当前layout,新打开一个窗口
extern void XF_ViewFocusUnit(XF_VIEW_Unit *unit);   //聚焦一个unit
extern void XF_ViewSetVisiable(XF_VIEW_Unit *unit, uint8 visiable); //设置一个unit是否可见

extern void XF_ViewRefesh();        //刷新
//extern void XF_ViewDestroy();  //销毁当前layout
extern void XF_ViewQuit();  //退出该当前layout，返回父layout
extern void XF_ViewFinish();        //释放所有view资源，退出

extern XF_VIEW_Unit *XF_ViewGetElementById(char *id);   //通过id获取页面部件,暂未实现


//有事件时的处理函数
extern void XF_ViewActionHandler(uint8 msg);

#endif

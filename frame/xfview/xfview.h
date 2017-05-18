﻿#ifndef __XF_VIEW_H__
#define __XF_VIEW_H__

//基于xfbgraph, xfmalloc的一套单色UI。
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

//框架主入口
extern void XF_ViewStart(XF_VIEW_Layout *layout);

//有事件时的处理函数
extern void XF_ViewActionHandler(uint8 msg);

//切换layout
extern void XF_ViewSwitch(XF_VIEW_Layout *parent, XF_VIEW_Layout *child);

#endif

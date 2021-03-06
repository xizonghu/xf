#ifndef __XF_UNIT_H__
#define __XF_UNIT_H__

//整个xfview的所有框架都是以XF_VIEW_Unit为基础定义的
#define UNIT_NEW(x, y, type, data)                       {{x, y}, type, data, VIEW_VISIBALE_TRUE}
#define LABEL_NEW(x, y, data)                            {UNIT_NEW(x, y, VIEW_TYPE_LABEL, data)}
#define BUTTON_NEW(x, y, data, func)                     {UNIT_NEW(x, y, VIEW_TYPE_BUTTON, data), func}
#define TEXT_NEW(x, y, type, data)                       {UNIT_NEW(x, y, VIEW_TYPE_TEXT, data), type, sizeof(data) - 1, 0}

#define XF_VIEW_UNIT_STATIC_INIT_PARM_3(x,y,onReceiver) {{x,y},XF_VIEW_UNIT_VISIBALE_TRUE,onReceiver,XF_NULL};

#define XF_VIEW_UNIT_KEY_UP           '2'   //KEY_PREV
#define XF_VIEW_UNIT_KEY_DOWN         '8'   //KEY_NEXT
#define XF_VIEW_UNIT_KEY_ENTER        '#'
#define XF_VIEW_UNIT_KEY_BACK         '*'
#define XF_VIEW_UNIT_KEY_PAGE_UP      '4'
#define XF_VIEW_UNIT_KEY_PAGE_DOWN    '6'

typedef uint8 attr;

typedef enum XF_VIEW_UNIT_TYPE_E {
    XF_VIEW_UNIT_TYPE_LABEL = (attr)1,
    XF_VIEW_UNIT_TYPE_TEXTEDIT = 2,
    XF_VIEW_UNIT_TYPE_OPTION = 3,
    XF_VIEW_UNIT_TYPE_LIST = 4,
    XF_VIEW_UNIT_TYPE_BUTTON = 5,
    XF_VIEW_UNIT_TYPE_LAYOUT = 6,
    XF_VIEW_UNIT_TYPE_TRIGGER = 7,
    XF_VIEW_UNIT_TYPE_IMAGE = 8,
    XF_VIEW_UNIT_TYPE_DATATABLE = 9,
    XF_VIEW_UNIT_TYPE_LISTTREE = 10,
    XF_VIEW_UINT_TYPE_DATALIST = 11,
    XF_VIEW_UINT_TYPE_TEXTLIST = 12,
} XF_VIEW_UnitType;

typedef enum XF_VIEW_UNIT_VISIBLE_E {
    XF_VIEW_UNIT_VISIBALE_FALSE = (attr)0,
    XF_VIEW_UNIT_VISIBALE_TRUE,
} XF_VIEW_UnitVisiable;

//1-127为系统统一使用,128以上为各控件使用
typedef enum XF_VIEW_UNIT_MESSAGE_TYPE_S {
    XF_VIEW_UNIT_MESSAGE_TYPE_LOAD = (attr)1,
    XF_VIEW_UNIT_MESSAGE_TYPE_UNLOAD,
    XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS,            //聚焦
    XF_VIEW_UNIT_MESSAGE_TYPE_SHOW,             //显示
    XF_VIEW_UNIT_MESSAGE_TYPE_DELETE,
    XF_VIEW_UNIT_MESSAGE_TYPE_CONTROL,          //按键
    XF_VIEW_UNIT_MESSAGE_TYPE_VISIABLE,
} XF_VIEW_UnitMessageType;

typedef enum XF_VIEW_UNIT_MESSAGE_RES_E {
    XF_VIEW_UNIT_MESSAGE_RES_OK = 0,
    XF_VIEW_UNIT_MESSAGE_RES_QUIT,
    XF_VIEW_UNIT_MESSAGE_RES_NEXT,
    XF_VIEW_UNIT_MESSAGE_RES_PREV,
    XF_VIEW_UNIT_MESSAGE_RES_UNFOCUS,  //返回该值说明部件不能被focus
    XF_VIEW_UNIT_MESSAGE_RES_UNDEFINE,  //返回该值说明部件不能处理message
    XF_VIEW_UNIT_MESSAGE_RES_TIMEOUT,

    XF_VIEW_UNIT_MESSAGE_RES_SIZE
} XF_VIEW_UnitMessageRes;

typedef struct XF_VIEW_UNIT_MESSAGE_S {
    uint8 type;
    uint8 val;
} XF_VIEW_UnitMessage;

//typedef void (*XF_VIEW_UnitCallback)(uint8 *res, struct XF_VIEW_UNIT_S *unit, XF_VIEW_UnitMessage *msg);

typedef struct XF_VIEW_POINT_S {
    attr x;
    attr y;
} XF_VIEW_Point;

typedef struct XF_VIEW_UNIT_S {
    XF_VIEW_Point point;
    attr visible;
    //attr type;
    void (*onMessageReceiver)(uint8 *res, struct XF_VIEW_UNIT_S *unit, XF_VIEW_UnitMessage *msg);
    struct XF_VIEW_UNIT_S *next;
} XF_VIEW_Unit;

#endif

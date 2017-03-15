#ifndef __VIEW_H__
#define __VIEW_H__

#define UNIT_NEW(x, y, type, data)                       {{x, y}, type, data, VIEW_VISIBALE_TRUE}
#define LABEL_NEW(x, y, data)                            {UNIT_NEW(x, y, VIEW_TYPE_LABEL, data)}
#define BUTTON_NEW(x, y, data, func)                     {UNIT_NEW(x, y, VIEW_TYPE_BUTTON, data), func}
#define TEXT_NEW(x, y, type, data)                       {UNIT_NEW(x, y, VIEW_TYPE_TEXT, data), type, sizeof(data) - 1, 0}

typedef unsigned char attr;

typedef enum {
    VIEW_TYPE_LABEL = (attr)1,
    VIEW_TYPE_TEXT,
    VIEW_TYPE_OPTION,
    VIEW_TYPE_LIST,
    VIEW_TYPE_BUTTON,
    VIEW_TYPE_LAYOUT,
} VIEW_UnitType;

typedef enum {
    VIEW_VISIBALE_FALSE = (attr)0,
    VIEW_VISIBALE_TRUE,
} VIEW_Visiable;

typedef struct {
    attr x;
    attr y;
} VIEW_Point;

typedef struct {
    VIEW_Point point;
    VIEW_UnitType type;
    char *buffer;
    VIEW_Visiable visible;
} VIEW_Unit;

typedef struct {
    VIEW_Unit super;
} VIEW_Label;

typedef enum {
    VIEW_TEXT_TYPE_TEXT = (attr)0,
    VIEW_TEXT_TYPE_PWD,
} VIEW_TextType;

typedef struct {
    VIEW_Unit super;
    VIEW_TextType type;
    attr size;
    attr pos;
} VIEW_Text;

typedef enum {
    VIEW_LIST_TYPE_OPTION = (attr)0,
    VIEW_LIST_TYPE_SUMBIT,
} VIEW_ListType;

typedef struct VIEW_LIST_UNIT {
    char *buffer;
    VIEW_ListType type;
    struct VIEW_LIST_UNIT *parent;
    struct VIEW_LIST_UNIT *next;
} VIEW_ListUnit;

typedef struct VIEW_LIST_OPTION {
    VIEW_ListUnit super;
    VIEW_ListUnit *child;
    attr pos;
} VIEW_ListOption;

typedef struct VIEW_LIST_SUBMIT {
    VIEW_ListOption super;
    void (*click)(void *arg);
} VIEW_ListSubmit;

typedef struct VIEW_LIST {
    VIEW_Unit super;
    VIEW_ListUnit *listUnit;
    attr sizeCursor;
    attr posCursor;
} VIEW_List;

typedef struct {
    VIEW_Unit super;
    int (*click)(void *arg);
} VIEW_Button;

typedef struct VIEW_LAYOUT {
    VIEW_Unit super;
    VIEW_Point size;
    struct VIEW_LAYOUT *parent;
    VIEW_Unit **children;
    attr sizeChildren;
    attr posChild;
    attr page;
    void (*init)(struct VIEW_LAYOUT *layout);
    void (*exit)(struct VIEW_LAYOUT *layout);
} VIEW_Layout;

extern XF_Action ViewAction;

extern void ViewBindEvent(XF_Event *evt);
extern void ViewShow(VIEW_Layout *layout);
extern void ViewCreate(VIEW_Layout *parent, VIEW_Layout *layout);
extern void ViewFocus(VIEW_Layout *layout, VIEW_Unit *unit);
extern void ViewQuit();
extern void ViewFinish();

#endif

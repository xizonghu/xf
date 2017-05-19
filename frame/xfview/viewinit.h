#ifndef __VIEW_INIT_H__
#define __VIEW_INIT_H__

#define UNIT_NEW(x, y, type, data)                       {{x, y}, type, data, VIEW_VISIBALE_TRUE}
#define LABEL_NEW(x, y, data)                            {UNIT_NEW(x, y, VIEW_TYPE_LABEL, data)}
#define BUTTON_NEW(x, y, data, func)                     {UNIT_NEW(x, y, VIEW_TYPE_BUTTON, data), func}
#define TEXT_NEW(x, y, type, data)                       {UNIT_NEW(x, y, VIEW_TYPE_TEXT, data), type, sizeof(data) - 1, 0}

#define VIEW_LIST_INIT(x, y, data, listUnit, sizeCursor)            x,  y, data, parent, children, size, 3, click
#define VIEW_LIST_OPTION_INIT(data, parent, children, size)         VIEW_LIST_INIT(x, y, data, parent, children, size, 0)
#define VIEW_LIST_INIT3(x, y, data, parent, click)                  VIEW_LIST_INIT(x, y, data, parent, 0, 0, click)
#define VIEW_LIST_INIT4(data, parent, children, size)               VIEW_LIST_INIT2(0, 16, data, parent, children, size)
#define VIEW_LIST_INIT5(data, parent, click)                        VIEW_LIST_INIT3(0, 16, data, parent, click)



extern void view_uint_init(VIEW_Unit *unit, uint8_t x, uint8_t y, VIEW_UnitType type, const char *data, VIEW_Visiable visible);
extern void view_label_init(VIEW_Label *label, uint8_t x, uint8_t y, const char *data);
extern void view_text_init(VIEW_Text *text, uint8_t x, uint8_t y, VIEW_TextType type, char *data, uint8_t size);
extern void view_button_init(VIEW_Button *button, uint8_t x, uint8_t y, const char *data, int (*click)(void *arg));

extern void view_listunit_init(VIEW_ListUnit *listUnit, char *data, VIEW_ListType type, VIEW_ListUnit *parent, VIEW_ListUnit *next);
extern void view_listoption_init(VIEW_ListOption *listOpt, char *data, VIEW_ListUnit *parent, VIEW_ListUnit *child, VIEW_ListUnit *next);
extern void view_listsubmit_init(VIEW_ListSubmit *listSub, char *data, VIEW_ListUnit *parent, VIEW_ListUnit *next, void (*click)(void *arg));
extern void view_list_init(VIEW_List *list, uint8_t x, uint8_t y, const char *data, VIEW_ListUnit *listUnit, uint8_t sizeCursor);
extern void view_layout_init(VIEW_Layout *layout, VIEW_Layout *parent, VIEW_Unit **children, uint8_t sizeChildren);

extern void view_uint_exit(VIEW_Unit *unit);
extern void view_label_exit(VIEW_Label *label);
extern void view_text_exit(VIEW_Text *text);
extern void view_button_exit(VIEW_Button *button);
extern void view_list_exit(VIEW_List *list);
extern void view_listunit_exit(VIEW_ListUnit *listUnit);
extern void view_layout_exit(VIEW_Layout *layout);

#endif

#include "xftype.h"
#include "xfea.h"
#include "xfstate.h"
#include "view.h"
#include "xfmalloc.h"

#include "viewinit.h"

void view_uint_init(VIEW_Unit *unit, uint8_t x, uint8_t y, VIEW_UnitType type, const char *data, VIEW_Visiable visible) {
    unit->point.x = x;
    unit->point.y = y;
    unit->type = type;
    unit->buffer = data;
    unit->visible = visible;
}

void view_label_init(VIEW_Label *label, uint8_t x, uint8_t y, const char *data) {
    view_uint_init((VIEW_Unit *)label,x, y, VIEW_TYPE_LABEL, data, VIEW_VISIBALE_TRUE);
}

void view_text_init(VIEW_Text *text, uint8_t x, uint8_t y, VIEW_TextType type, char *data, uint8_t size) {
    view_uint_init((VIEW_Unit *)text,x, y, VIEW_TYPE_TEXT, data, VIEW_VISIBALE_TRUE);
    text->type = type;
    text->pos = 0;
    text->size = size;
}

void view_button_init(VIEW_Button *button, uint8_t x, uint8_t y, const char *data, int (*click)(void *arg)) {
    view_uint_init((VIEW_Unit *)button,x, y, VIEW_TYPE_BUTTON, data, VIEW_VISIBALE_TRUE);
    button->click = click;
}

void view_listunit_init(VIEW_ListUnit *listUnit, char *data, VIEW_ListType type, VIEW_ListUnit *parent, VIEW_ListUnit *next) {
    listUnit->buffer = data;
    listUnit->type = type;
    listUnit->parent = parent;
    listUnit->next = next;
}

void view_listoption_init(VIEW_ListOption *listOpt, char *data, VIEW_ListUnit *parent, VIEW_ListUnit *child, VIEW_ListUnit *next) {
    view_listunit_init((VIEW_ListUnit *)listOpt, data, VIEW_LIST_TYPE_OPTION, parent, next);
    listOpt->child = child;
    listOpt->pos = 0;
}

void view_listsubmit_init(VIEW_ListSubmit *listSub, char *data, VIEW_ListUnit *parent, VIEW_ListUnit *next, void (*click)(void *arg)) {
    view_listunit_init((VIEW_ListUnit *)listSub, data, VIEW_LIST_TYPE_SUMBIT, parent, next);
    listSub->click = click;
}

void view_list_init(VIEW_List *list, uint8_t x, uint8_t y, const char *data, VIEW_ListUnit *listUnit, uint8_t sizeCursor) {
    view_uint_init((VIEW_Unit *)list, x, y, VIEW_TYPE_LIST, data, VIEW_VISIBALE_TRUE);
    list->listUnit = listUnit;
    list->sizeCursor = sizeCursor;
    list->posCursor = 0;
}

void view_layout_init(VIEW_Layout *layout, VIEW_Layout *parent, VIEW_Unit **children, uint8_t sizeChildren) {
    view_uint_init((VIEW_Unit *)layout, 0, 0, VIEW_TYPE_LAYOUT, "", VIEW_VISIBALE_TRUE);
    layout->size.x = 128;
    layout->size.y = 64;
    layout->parent = parent;
    layout->children = children;
    layout->sizeChildren = sizeChildren;
    layout->posChild = 0;
    layout->page = 0;
    layout->init = 0;
}

void view_uint_exit(VIEW_Unit *unit) {
    XF_free(unit);
}

void view_label_exit(VIEW_Label *label) {
    XF_free(label);
}

void view_text_exit(VIEW_Text *text) {
    XF_free(text->super.buffer);
    XF_free(text);
}

void view_button_exit(VIEW_Button *button) {
    XF_free(button);
}

void view_listunit_exit(VIEW_ListUnit *listUnit) {
    if(VIEW_LIST_TYPE_OPTION == listUnit->type) {
        view_listunit_exit(((VIEW_ListOption *)listUnit)->child);
    }

    if(listUnit->next) view_listunit_exit(listUnit->next);

    XF_free(listUnit);
    return;
}

void view_list_exit(VIEW_List *list) {
    view_listunit_exit(list->listUnit);
    XF_free(list);
}

void view_layout_exit(VIEW_Layout *layout) {
    uint8_t pos = 0;
    for(pos = 0; pos < layout->sizeChildren; pos++) {
        VIEW_Unit *unit = (VIEW_Unit *)layout->children[pos];
        switch(unit->type) {
            case VIEW_TYPE_LABEL: {
                view_label_exit((VIEW_Label *)unit);
                break;
            }
            case VIEW_TYPE_BUTTON: {
                view_button_exit((VIEW_Button *)unit);
                break;
            }
            case VIEW_TYPE_TEXT: {
                view_text_exit((VIEW_Text *)unit);
                break;
            }
            case VIEW_TYPE_LIST: {
                view_list_exit((VIEW_List *)unit);
                break;
            }
        }
    }
	XF_free(layout->children);
}

/////////////////////label////////////////////
static void list_create(VIEW_List *list) {
    //bgraph_set_text(&graphMain, list->super.point.x, list->super.point.y, list->super.buffer, BGRAPH_COLOR_WHITE);
}

static void list_destroy(VIEW_List *list) {
    bgraph_set_text(&graphMain, list->super.point.x, list->super.point.y, list->super.buffer, BGRAPH_COLOR_WHITE);
}

static uint8_t list_process_msg(VIEW_List *list, XF_Message *msg) {
    VIEW_ListOption *currOpt = (VIEW_ListOption *)list->listUnit;

    if(VIEW_LIST_TYPE_OPTION != currOpt->super.type) return 0;

    switch(msg->what) {
        case VIEW_MSG_PLAY: {
            break;
        }
        case VIEW_MSG_KEY_DOWN: {
            VIEW_ListUnit *headUnit = 0;
            uint8_t pos = 0;

            //检查数据尾
            headUnit = currOpt->child;
            for(pos = 0; headUnit && pos < currOpt->pos; pos++) {
                headUnit = headUnit->next;
            }
            for(pos = 0; headUnit && pos <= list->posCursor; pos++) {
                headUnit = headUnit->next;
            }
            if(0 == headUnit) break;

            //检查显示尾
            if((list->sizeCursor - 1) == list->posCursor) currOpt->pos++;
            else list->posCursor++;
            break;
        }
        case VIEW_MSG_KEY_UP: {
            //检查数据首
            if(0 == currOpt->pos && 0 == list->posCursor) break;

            //检查显示首
            if(0 == list->posCursor) currOpt->pos--;
            else list->posCursor--;
            break;
        }
        case VIEW_MSG_KEY_BACK: {
            if(0 == list->listUnit->parent) return VIEW_RET_NEXT;
            currOpt->pos = 0;
            list->posCursor = 0;
            list->listUnit = list->listUnit->parent;
            break;
        }
        case VIEW_MSG_KEY_ENTER: {
            VIEW_ListUnit *headUnit = 0;
            uint8_t pos = 0;

            headUnit = currOpt->child;
            for(pos = 0; headUnit && pos < currOpt->pos; pos++) {
                headUnit = headUnit->next;
            }
            for(pos = 0; headUnit && pos < list->posCursor; pos++) {
                headUnit = headUnit->next;
            }
            if(0 == headUnit) break;
            if(VIEW_LIST_TYPE_OPTION == headUnit->type) {
                list->listUnit = headUnit;
                list->posCursor = 0;
            } else if(VIEW_LIST_TYPE_SUMBIT == headUnit->type) {
                ((VIEW_ListSubmit *)headUnit)->click(mView);
                return 0;
            }
            break;
        }
        /*case VIEW_MSG_KEY_DOWN: {
            if((currlist->sizeChildren - 1) == currlist->posChild) break;
            currlist->posChild++;
            if((currlist->sizeCursor - 1) == currlist->posCursor) {
                currlist->posCursor = 0;
                list_show(currlist);
            } else {
				currlist->posCursor++;
                list_focus(currlist, '+');
            }
            break;
        }
        case VIEW_MSG_KEY_UP: {
            if(0 == currlist->posChild) break;
            currlist->posChild--;
            if(0 == currlist->posCursor) {
                currlist->posCursor = (currlist->sizeCursor - 1);
                list_show(currlist);
            } else {
				currlist->posCursor--;
                list_focus(currlist, '-');
            }            
            break;
        }
        case VIEW_MSG_KEY_BACK: {
			currlist->posChild = 0;
			currlist->posCursor = 0;
            currlist = currlist->parent;
            if(0 == currlist) return VIEW_RET_NEXT;
            list_show(currlist);
            break;
        }
        case VIEW_MSG_KEY_ENTER: {
            currlist = (VIEW_List *)currlist->children[currlist->posChild];
            if(currlist->click) {
                currlist->click(mView);
            } else {
                list_show(currlist);
            }
            break;
        }*/
    }
    list_show(list);
    return VIEW_RET_OK;
}

/////////////////////label////////////////////

static void layout_create(VIEW_Layout *layout) {
    uint8_t pos = 0;

    if(layout->init) layout->init(layout);

    layout->posChild = 0;

    while(pos < layout->sizeChildren) {
        VIEW_Unit *uint = layout->children[pos++];
        if(VIEW_VISIBALE_FALSE == uint->visible) continue;
        switch(uint->type) {
            case VIEW_TYPE_LABEL: {
                label_create((VIEW_Label *)uint);
                break;
            }
            case VIEW_TYPE_LIST: {
                list_create((VIEW_List *)uint);
                break;
            }
            case VIEW_TYPE_BUTTON: {
                button_create((VIEW_Button *)uint);
                break;
            }
            case VIEW_TYPE_TEXT: {
                text_create((VIEW_Text *)uint);
                break;
            }
        }
    }
}

static void layout_destroy(VIEW_Layout *layout) {
    if(layout->exit) layout->exit(layout);
}

static uint8_t view_focus(VIEW_Layout *layout, VIEW_Unit *focus) {
    uint8_t pos = 0;
    uint8_t size = layout->sizeChildren;

    while(pos < size) {
        VIEW_Unit *uint = layout->children[pos];
        if(focus == uint) {
            layout->posChild = pos;
            break;
        }
		pos++;
    }

    return VIEW_RET_OK;
}

static void list_show(VIEW_List *list) {
    char strNull[] = "                ";
    uint8_t pos = 0;
    uint8_t x = list->super.point.x, y = list->super.point.y;
    VIEW_ListOption *currOpt = (VIEW_ListOption *)list->listUnit;
    VIEW_ListUnit *headUnit = 0;

    headUnit = currOpt->child;
    for(pos = 0; pos < currOpt->pos; pos++) {
        headUnit = headUnit->next;
    }

    for(pos = 0; pos < list->sizeCursor; pos++) {
        bgraph_set_text(&graphMain, x, y + pos * graphMain.pixelOfCharY, strNull, BGRAPH_COLOR_WHITE);
        if(0 == headUnit) continue;

        if(pos == list->posCursor) {
            bgraph_set_text(&graphMain, x, y + pos * graphMain.pixelOfCharY, headUnit->buffer, BGRAPH_COLOR_BLACK);
        } else {
            bgraph_set_text(&graphMain, x, y + pos * graphMain.pixelOfCharY, headUnit->buffer, BGRAPH_COLOR_WHITE);
        }
        headUnit = headUnit->next;
    }
}


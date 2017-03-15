#ifndef __VIEW_H__
#define __VIEW_H__

typedef enum {
    VIEW_TYPE_LABLE = (char)1,
    VIEW_TYPE_TEXT,
    VIEW_TYPE_OPTION,
} VIEW_UnitType;

typedef struct {
    uint8_t x;
    uint8_t y;
} VIEW_Point;

typedef struct {
    VIEW_UnitType type;
    VIEW_Point point;
    char buffer;
} VIEW_Unit;

typedef struct {
    VIEW_UnitType type;
    VIEW_Point point;
    char buffer;
} VIEW_Table;

typedef struct {
    VIEW_Unit *uints[];
    
} VIEW_Window;

#endif

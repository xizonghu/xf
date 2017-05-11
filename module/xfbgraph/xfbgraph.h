#ifndef __XF_BGRAPH_H__
#define __XF_BGRAPH_H__

#define STRING_NULL                    "                "

//#define STRING_MENU


#define DISPLAY_PRINT_BUF_LENGTH       20  //
#define DISPLAY_CURSOR_POS_X		   120  //光标x位置
#define DISPLAY_PRINT_SIZE             16  //显示最大文本位�?
#define DISPLAY_LINE_SIZE              3  //显示最大行�?
#define DISPLAY_X_SIZE                 128  //显示最大x位置
#define DISPLAY_Y_SIZE                 8  //显示最大y位置
#define DISPLAY_CHAR_X_SIZE            8  //文本的x大小
#define DISPLAY_CHAR_Y_SIZE            2  //文本的y大小

#define BGRAPH_PIXEL_LENGHT            128
#define BGRAPH_PIXEL_HEIGHT            64
#define BGRAPH_PIXEL_CELL              32

#define BGRAPH_CELL_OFFSET             5  //log2(BGRAPH_PIXEL_CELL)
#define BGRAPH_CELL_SHIFT              0x1f  // 0xff << BGRAPH_CELL_OFFSET

//typedef uint32_t cell;

typedef enum {
    BGRAPH_COLOR_BLACK = (uint8)0,
    BGRAPH_COLOR_WHITE,
} BGRAPH_Color;

typedef struct {
    const char *name;  //字库名字
    char *encodeAddr;  //内码地址
    char *addr;  //字库地址
    int size;  //字数
    uint8 fontWidth;  //字体�?
    uint8 fontHeight;  //字体�?
    uint8 fontSize;  //单个字体所占存储空间，单位字节
} BGRAPH_Font;

typedef struct {
    void **fb;  //framebuffer
    void **fontEN;
    BGRAPH_Font *fontCN;
    uint8 pixelLenght;
    uint8 pixelHeight;
    uint8 pixelOfCharX;
    uint8 pixelOfCharY;
    uint8 charLenght;
    uint8 charHeight;
    uint8 posX;
    uint8 posY;
} BGRAPH;

extern BGRAPH graphMain;

extern int bgraph_set_pixel(BGRAPH *bg, uint8 x, uint8 y, BGRAPH_Color color);
extern int bgraph_set_text(BGRAPH *bg, uint8 x, uint8 y, char *str, BGRAPH_Color color);
extern int bgraph_refresh(BGRAPH *bg);
extern int bgraph_refresh_area(BGRAPH *bg, uint8 x, uint8 y, uint8 lenght, uint8 height, BGRAPH_Color color);
extern int bgraph_clear(BGRAPH *bg);

extern int bgraph_set_pos(BGRAPH *bg, uint8 x, uint8 y);
extern int bgraph_get_pos(BGRAPH *bg, uint8 *x, uint8 *y);
#endif

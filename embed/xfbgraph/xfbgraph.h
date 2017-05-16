#ifndef __XF_BGRAPH_H__
#define __XF_BGRAPH_H__


#define XF_BGRAPH_PIXEL_LENGHT            128U
#define XF_BGRAPH_PIXEL_HEIGHT            64

//typedef uint32_t cell;

typedef enum XF_BGRAPH_COLOR_E {
    XF_BGRAPH_COLOR_BLACK = (uint8)0,
    XF_BGRAPH_COLOR_WHITE,
} XF_BgraphColor;

typedef struct XF_BGRAPH_FONT_S {
    const char *name;  //字库名字
    char *encodeAddr;  //内码地址
    char *addr;  //字库地址
    int size;  //字数
    uint8 fontWidth;
    uint8 fontHeight;
    uint8 fontSize;  //单个字体所占存储空间，单位字节
} XF_BgraphFont;

typedef struct XF_BGRAPH_S {
    void **fb;  //framebuffer
    XF_BgraphFont *fontChar;
    XF_BgraphFont *fontOther;
    uint8 pixelLenght;
    uint8 pixelHeight;
    uint8 pixelOfCharX;
    uint8 pixelOfCharY;
    uint8 charLenght;
    uint8 charHeight;
    uint8 posX;
    uint8 posY;
} XF_Bgraph;

extern XF_Bgraph graphMain;

//基础接口，已提供，也可自己实现
extern int XF_BgraphSetText(XF_Bgraph *bg, uint8 x, uint8 y, char *str, XF_BgraphColor color);
extern int XF_BgraphClear(XF_Bgraph *bg);


//根据不同平台，分别实现
extern int XF_BgraphFlush(XF_Bgraph *bg);


//可扩展接口
extern int XF_BgraphSetPos(XF_Bgraph *bg, uint8 x, uint8 y);
extern int XF_BgraphGetPos(XF_Bgraph *bg, uint8 *x, uint8 *y);
extern int XF_BgraphFlushArea(XF_Bgraph *bg, uint8 x, uint8 y, uint8 lenght, uint8 height, XF_BgraphColor color);
extern int XF_BgraphSetPixel(XF_Bgraph *bg, uint8 x, uint8 y, XF_BgraphColor color);

#endif

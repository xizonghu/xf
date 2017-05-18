#include "xftypedef.h"
#include "xfbgraph.h"

//#define XF_BGRAPH_PIXEL_CELL              32
//#define XF_BGRAPH_CELL_OFFSET             5  //log2(BGRAPH_PIXEL_CELL)
//#define XF_BGRAPH_CELL_SHIFT              0x1f  // 0xff << BGRAPH_CELL_OFFSET

//#define LCD_PIXEL_WIDTH                           128U
//#define LCD_PIXEL_HEIGHT                          64U
#define LCD_PIXEL_CELL                          8U    //一个cell占的像素数
#define LCD_PIXEL_BYTE                          8U //一个存储单位占的像素数

//#define LCD_BYTE_WIDTH                            (LCD_PIXEL_WIDTH / 8)  
//#define LCD_BYTE_HEIGHT                           (LCD_PIXEL_HEIGHT / 8)

/*static uint8 mfb[LCD_PIXEL_WIDTH][LCD_BYTE_HEIGHT] = {0};
XF_Bgraph globalGraph = {
    mfb,
    LCD_PIXEL_WIDTH,
    LCD_PIXEL_HEIGHT,
    0,
    0,
};*/

XF_Bgraph globalGraph = {0};

/*static void write_font(XF_Bgraph *bg, uint8 x, uint8 y, uint8 const *bits, uint8 h) {
    uint32 *fb = &mfb[y][x >> XF_BGRAPH_CELL_OFFSET];  //将x转为fb位置 (x >> 5) = (x / 32)
    uint32 shft = (x & 0x1FU);     //(x & 0x1FU) = (x % 32)
    for (y = 0; y < h; ++y, fb += (XF_BGRAPH_PIXEL_WIDTH >> XF_BGRAPH_CELL_OFFSET)) {  //(LCD_LENGHT >> 5) = (32)
        *fb |= ((uint32)bits[y] << shft);
        if (shft > 24U) {  //一个字节8bit，超出本cell，需要去填充下一个cell
            *(fb + 1) |= ((uint32)bits[y] >> (32U - shft));
        }
    }
}*/

void XF_BgraphDraw_H(XF_Bgraph *bg, uint8 x, uint8 y, uint8 *data, uint8 width, uint8 height, XF_BgraphFill fill) {
    uint8 posX = 0;
    uint8 sizeX = (x + width < bg->width) ? (x + width) : bg->width;
    uint8 sizeY = (y + height < bg->height) ? (y + height) : bg->height;
    uint8 byteWidth = bg->width / LCD_PIXEL_BYTE;

    for (; y < sizeY; y++) {
        uint8 *pfb = (uint8*)(bg->fb + y*byteWidth + x/LCD_PIXEL_BYTE);
        for (posX = x; posX < sizeX; posX += LCD_PIXEL_BYTE) {
            if (XF_BGRAPH_FILL_REVERSE == fill) {
                *pfb = ~(*data);
            }
            else {
                *pfb = *data;
            }
            pfb++;
            data++;
        }
    }
}

//只支持y为16的倍数
/*void XF_BgraphDraw_VH(XF_Bgraph *bg, uint8 x, uint8 y, uint8 *data, uint8 width, uint8 height, XF_BgraphFill fill) {
    uint8 posX = 0;
    uint8 sizeX = (x + width < bg->width) ? (x + width) : bg->width;
    uint8 sizeY = (y + height < bg->height) ? (y + height) : bg->height;
    uint8 poscellY = y / LCD_PIXEL_CELL;
    uint8 sizecellY = sizeY / LCD_PIXEL_CELL;
    for (; poscellY < sizecellY; poscellY++) {
        uint8 *pFb = (uint8*)(bg->fb + poscellY*bg->width + x);
        for (posX = x; posX < sizeX; posX++) {
            if (XF_BGRAPH_FILL_REVERSE == fill) {
                *pFb = ~(*data);
            }
            else {
                *pFb = *data;
            }
            pFb++;
            data++;
        }
    }
}*/

static void write_fb_VH(XF_Bgraph *bg, uint8 x, uint8 y, uint8 dat) {
    uint8 *pfb1, *pfb2; //因为fb以8个像素对齐到一个字节的方式存储数据，所以要写一个字节的数据可能涉及fb的两个地址
    uint8 mask = y % LCD_PIXEL_CELL;
    uint8 posRow = y / LCD_PIXEL_CELL;

    //写pfb1段的数据
    pfb1 = bg->fb + (posRow + 0) * bg->width + x;
    *pfb1 &= 0xff >> (LCD_PIXEL_CELL - mask);   //清除原有数据位
    *pfb1 |= dat << mask;

    if (mask) {
        //写pfb2段的数据
        pfb2 = bg->fb + (posRow + 1) * bg->width + x;
        *pfb2 &= 0xff << mask;
        *pfb2 |= dat >> (LCD_PIXEL_CELL - mask);
    }
}

void XF_BgraphDraw_VH(XF_Bgraph *bg, uint8 x, uint8 y, uint8 *data, uint8 width, uint8 height, XF_BgraphFill fill) {
    uint8 posX = 0;
    uint8 sizeX = (x + width < bg->width) ? (x + width) : bg->width;
    uint8 sizeY = (y + height < bg->height) ? (y + height) : bg->height;
    uint8 poscellY = y / LCD_PIXEL_CELL;
    uint8 sizecellY = sizeY / LCD_PIXEL_CELL;
    for (; y < sizeY; y += LCD_PIXEL_CELL) {
        for (posX = x; posX < sizeX; posX++) {
            if (XF_BGRAPH_FILL_REVERSE == fill) {
                write_fb_VH(bg, posX, y, ~(*data));
            }
            else {
                write_fb_VH(bg, posX, y, *data);
            }
            data++;
        }
    }
}


void XF_BgraphClear(XF_Bgraph *bg) {
    uint16 size = bg->width / 8 * bg->height;
    uint8 *pfb = bg->fb;
    while (0 < size--) {
        *pfb = 0;
        pfb++;
    }        
}

void XF_BgraphInit(XF_Bgraph *bg, uint8 *fb, uint8 width, uint8 height) {
    bg->fb = fb;
    bg->width = width;
    bg->height = height;
    bg->posX = 0;
    bg->posY = 0;
}

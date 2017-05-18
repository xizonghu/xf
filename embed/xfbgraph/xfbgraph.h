#ifndef __XF_BGRAPH_H__
#define __XF_BGRAPH_H__

//屏幕一般不会直接操作每个像素，而是通过缓存区间接操作。
//屏幕的缓存区共计（屏幕宽度*屏幕高度）个像素，（屏幕宽度*屏幕高度/8）个字节。有的屏幕会将缓存区再细分为多个缓存块。
//缓存区存储像素数据的方式分为两种，按行存储（水平方式[H]），按列存储（垂直方式[V]）,混合存储（水平方向的若干个像素组成一个cell，以cell为单位按垂直方式存储；或者垂直方向的若干个像素组成一个cell，以cell为单位按水平方式存储）。smlock上使用的就是8个垂直像素组成cell按行存储。
//我们使用屏幕时，为了减少操作次数和集中操作，往往会在内存中再画出一个大小和屏幕缓存相同的区域framebuffer。
//关于framebuffer和屏幕缓存区的映射关系，由于数据量大且操作频繁，不考虑做函数映射而选择直接一一对应。或者直接取消framebuffer机制。

//      水平方式            垂直方式            混合方式[VH]
//      __________      ||||||||||      //////////
//      __________      ||||||||||      //////////
//      __________      ||||||||||      //////////
//fb    [ph][bw]        [pw][bh]        [ph/c][pw]        pw宽度(像素) bw宽度(字节) ph高度(像素) bh高度(字节) c混合方式下一个cell的bit数(此时数据类型等于cell位)

//#define XF_BGRAPH_PIXEL_WIDTH             128U  //屏幕宽度
//#define XF_BGRAPH_PIXEL_HEIGHT            64U   //屏幕高度

//typedef uint32_t cell;

#define XF_BgraphDraw(a,b,c,d,e,f,g)       XF_BgraphDraw_VH(a,b,c,d,e,f,g)

typedef enum XF_BGRAPH_COLOR_E {
    XF_BGRAPH_COLOR_WHITE,
    XF_BGRAPH_COLOR_BLACK,
} XF_BgraphColor;

typedef enum XF_BGRAPH_FILL_E {
    XF_BGRAPH_FILL_NORMAL,
    XF_BGRAPH_FILL_REVERSE,
} XF_BgraphFill;

typedef struct XF_BGRAPH_S {
    uint8 *fb;  //framebuffer
    uint8 width;
    uint8 height;
    uint8 posX;
    uint8 posY;
} XF_Bgraph;


extern XF_Bgraph globalGraph;

//基础接口，已提供，也可自己实现
extern void XF_BgraphInit(XF_Bgraph *bg, uint8 *fb, uint8 width, uint8 height);
extern void XF_BgraphDraw_H(XF_Bgraph *bg, uint8 x, uint8 y, uint8 *data, uint8 width, uint8 height, XF_BgraphFill fill);
extern void XF_BgraphDraw_V(XF_Bgraph *bg, uint8 x, uint8 y, uint8 *data, uint8 width, uint8 height, XF_BgraphFill fill);
extern void XF_BgraphDraw_VH(XF_Bgraph *bg, uint8 x, uint8 y, uint8 *data, uint8 width, uint8 height, XF_BgraphFill fill);
extern void XF_BgraphDraw_HV(XF_Bgraph *bg, uint8 x, uint8 y, uint8 *data, uint8 width, uint8 height, XF_BgraphFill fill);
extern void XF_BgraphClear(XF_Bgraph *bg);


//不同屏幕，分别实现
extern void XF_BgraphFlush(XF_Bgraph *bg);


//可扩展接口
extern int XF_BgraphSetPos(XF_Bgraph *bg, uint8 x, uint8 y);
extern int XF_BgraphGetPos(XF_Bgraph *bg, uint8 *x, uint8 *y);
extern int XF_BgraphFlushArea(XF_Bgraph *bg, uint8 x, uint8 y, uint8 lenght, uint8 height);
extern int XF_BgraphSetPixel(XF_Bgraph *bg, uint8 x, uint8 y);

#endif

#ifndef __XF_BGRAPH_H__
#define __XF_BGRAPH_H__

//��Ļһ�㲻��ֱ�Ӳ���ÿ�����أ�����ͨ����������Ӳ�����
//��Ļ�Ļ��������ƣ���Ļ���*��Ļ�߶ȣ������أ�����Ļ���*��Ļ�߶�/8�����ֽڡ��е���Ļ�Ὣ��������ϸ��Ϊ�������顣
//�������洢�������ݵķ�ʽ��Ϊ���֣����д洢��ˮƽ��ʽ[H]�������д洢����ֱ��ʽ[V]��,��ϴ洢��ˮƽ��������ɸ��������һ��cell����cellΪ��λ����ֱ��ʽ�洢�����ߴ�ֱ��������ɸ��������һ��cell����cellΪ��λ��ˮƽ��ʽ�洢����smlock��ʹ�õľ���8����ֱ�������cell���д洢��
//����ʹ����Ļʱ��Ϊ�˼��ٲ��������ͼ��в��������������ڴ����ٻ���һ����С����Ļ������ͬ������framebuffer��
//����framebuffer����Ļ��������ӳ���ϵ���������������Ҳ���Ƶ����������������ӳ���ѡ��ֱ��һһ��Ӧ������ֱ��ȡ��framebuffer���ơ�

//      ˮƽ��ʽ            ��ֱ��ʽ            ��Ϸ�ʽ[VH]
//      __________      ||||||||||      //////////
//      __________      ||||||||||      //////////
//      __________      ||||||||||      //////////
//fb    [ph][bw]        [pw][bh]        [ph/c][pw]        pw���(����) bw���(�ֽ�) ph�߶�(����) bh�߶�(�ֽ�) c��Ϸ�ʽ��һ��cell��bit��(��ʱ�������͵���cellλ)

//#define XF_BGRAPH_PIXEL_WIDTH             128U  //��Ļ���
//#define XF_BGRAPH_PIXEL_HEIGHT            64U   //��Ļ�߶�

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

//�����ӿڣ����ṩ��Ҳ���Լ�ʵ��
extern void XF_BgraphInit(XF_Bgraph *bg, uint8 *fb, uint8 width, uint8 height);
extern void XF_BgraphDraw_H(XF_Bgraph *bg, uint8 x, uint8 y, uint8 *data, uint8 width, uint8 height, XF_BgraphFill fill);
extern void XF_BgraphDraw_V(XF_Bgraph *bg, uint8 x, uint8 y, uint8 *data, uint8 width, uint8 height, XF_BgraphFill fill);
extern void XF_BgraphDraw_VH(XF_Bgraph *bg, uint8 x, uint8 y, uint8 *data, uint8 width, uint8 height, XF_BgraphFill fill);
extern void XF_BgraphDraw_HV(XF_Bgraph *bg, uint8 x, uint8 y, uint8 *data, uint8 width, uint8 height, XF_BgraphFill fill);
extern void XF_BgraphClear(XF_Bgraph *bg);


//��ͬ��Ļ���ֱ�ʵ��
extern void XF_BgraphFlush(XF_Bgraph *bg);


//����չ�ӿ�
extern int XF_BgraphSetPos(XF_Bgraph *bg, uint8 x, uint8 y);
extern int XF_BgraphGetPos(XF_Bgraph *bg, uint8 *x, uint8 *y);
extern int XF_BgraphFlushArea(XF_Bgraph *bg, uint8 x, uint8 y, uint8 lenght, uint8 height);
extern int XF_BgraphSetPixel(XF_Bgraph *bg, uint8 x, uint8 y);

#endif

#ifndef __XF_FONT_H__
#define __XF_FONT_H__

//字库像素数据的存储方式分为三种
//按行存储（水平方式）
//按列存储（垂直方式）
//混合存储（水平方向的若干个像素组成一个cell，以cell为单位按垂直方式存储；或者垂直方向的若干个像素组成一个cell，以cell为单位按水平方式存储）。

typedef struct XF_BGRAPH_FONT_S {
    const char *name;  //字库名字
    char *addr;  //字库地址
    int size;  //字数
    uint8 fontWidth;
    uint8 fontHeight;
    uint8 fontSize;  //单个字体所占存储空间，单位字节
    uint8 *(*addrOf)(uint16 val);   //字符内码转为字库地址, 输入该字符的计算机内码，返回该字符的字库数据地址
    //uint16 (*offsetOf)(uint16 val);   //输入字符内码，返回字符在字库中的偏移。与addrOf功能类似
} XF_BgraphFont;

#endif

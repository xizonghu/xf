#ifndef __XF_FONT_H__
#define __XF_FONT_H__

//汉字字库的内码最好用GBK编码（单双编码，英文单字节兼容ASCII，中文双字节）

typedef struct XF_BGRAPH_FONT_S {
    const char *name;  //字库名字
    uint8 *addr;  //字库地址
    int size;  //字数
    uint8 fontWidth;
    uint8 fontHeight;
    uint8 fontSize;  //单个字体所占存储空间，单位字节
    uint8 *(*addrOf)(uint16 val);   //字符内码转为字库地址, 输入该字符的计算机内码，返回该字符的字库数据地址
    //uint16 (*offsetOf)(uint16 val);   //输入字符内码，返回字符在字库中的偏移。与addrOf功能类似
} XF_BgraphFont;

#endif

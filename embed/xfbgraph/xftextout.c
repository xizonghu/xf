#include "xftypedef.h"

#include "xftextout.h"

/*XF_Textout globalTextout = {
    &globalGraph,
    &font8x16VH,
    &fontCN16x16VH,
};*/

XF_Textout globalTextout = {0};

void XF_TextoutInit(XF_Textout *tt, XF_Bgraph *graph, XF_BgraphFont *en, XF_BgraphFont *other) {
    tt->graph = graph;
    tt->fontChar = en;
    tt->fontOther = other;
}

void XF_TextoutPrint(XF_Textout *tt, uint8 x, uint8 y, char *str, XF_BgraphFill fill) {
    while (*str != '\0') {
        XF_BgraphFont *font = XF_NULL;
        uint8 *data = XF_NULL;
        uint16 val = *str;
        if (val < 0x80) {   //english
            font = tt->fontChar;
            str++;
        }
        else {  //chinese
            font = tt->fontOther;
            str+= 2;
        }

        data = font->addrOf(val);

        XF_BgraphDraw(tt->graph, x, y, data, font->fontWidth, font->fontHeight, fill);
        x += font->fontWidth;
    }
}

void XF_TextoutClear(XF_Textout *tt) {
    XF_TextoutPrint(tt, 0, 0, "                ", XF_BGRAPH_FILL_NORMAL);
    XF_TextoutPrint(tt, 0, 16, "                ", XF_BGRAPH_FILL_NORMAL);
    XF_TextoutPrint(tt, 0, 32, "                ", XF_BGRAPH_FILL_NORMAL);
    XF_TextoutPrint(tt, 0, 48, "                ", XF_BGRAPH_FILL_NORMAL);
}

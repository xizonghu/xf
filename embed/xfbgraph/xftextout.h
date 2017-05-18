#ifndef __XF_TEXTOUT_H__
#define __XF_TEXTOUT_H__

#include "xfbgraph.h"
#include "xffont.h"

/*typedef enum XF_TEXTOUT_MODE_E {
    XF_TEXTOUT_MODE_NORMAL,
    XF_TEXTOUT_MODE_REVERSE,
} XF_TextoutMode;*/

typedef struct XF_TEXTOUT_S {
    XF_Bgraph *graph;
    XF_BgraphFont *fontChar;
    XF_BgraphFont *fontOther;
} XF_Textout;

extern XF_Textout globalTextout;

extern void XF_TextoutInit(XF_Textout *tt, XF_Bgraph *graph, XF_BgraphFont *en, XF_BgraphFont *other);
extern void XF_TextoutPrint(XF_Textout *tt, uint8 x, uint8 y, char *str, XF_BgraphFill fill);
extern void XF_TextoutClear(XF_Textout *tt);


#endif

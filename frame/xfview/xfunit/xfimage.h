#ifndef __XF_IMAGE_H__
#define __XF_IMAGE_H__

typedef struct XF_VIEW_IMAGE_S {
    XF_VIEW_Unit super;
    uint8 *data;
    uint8 width;
    uint8 height;
} XF_VIEW_Image;

extern XF_VIEW_Image *XF_VIEW_ImageNew(attr x, attr y, uint8 *data, uint8 width, uint8 height);
extern void XF_VIEW_ImageDelete(XF_VIEW_Image* img);

#endif

#include "xftypedef.h"
#include "xfbgraph.h"
#include "xftextout.h"
#include "xfmalloc.h"

#include "xfunit.h"
#include "xfimage.h"

/*static void label_create(XF_VIEW_Label *label) {
}*/

/*static void label_destroy(XF_VIEW_Label *label) {
}*/

static void image_show(XF_VIEW_Image *img) {
    XF_BgraphDraw(&globalGraph, img->super.point.x, img->super.point.y, img->data, img->width, img->height, XF_BGRAPH_FILL_NORMAL);
    XF_BgraphFlush(&globalGraph);
}

static void onMessageReceiver(uint8 *res, XF_VIEW_Unit *unit, XF_VIEW_UnitMessage *msg) {
    XF_VIEW_Image *img = (XF_VIEW_Image*)unit;
    *res = XF_VIEW_UNIT_MESSAGE_RES_OK;

    switch (msg->type) {
        case XF_VIEW_UNIT_MESSAGE_TYPE_SHOW: {
            image_show(img);
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_FOCUS: {
            if (XF_VIEW_UNIT_KEY_UP == msg->val || XF_VIEW_UNIT_KEY_BACK == msg->val ) {
                *res = XF_VIEW_UNIT_MESSAGE_RES_PREV;
            }
            else {
                *res = XF_VIEW_UNIT_MESSAGE_RES_NEXT;
            }
            break;
        }
        case XF_VIEW_UNIT_MESSAGE_TYPE_DELETE: {
            XF_VIEW_ImageDelete(img);
            break;
        }
    }
}

XF_VIEW_Image *XF_VIEW_ImageNew(attr x, attr y, uint8 *data, uint8 width, uint8 height) {
    XF_VIEW_Image *img = XF_malloc(sizeof(XF_VIEW_Image));

    if (XF_NULL == img) return XF_NULL;

    img->super.point.x = x;
    img->super.point.y = y;
    //img->super.type = XF_VIEW_UNIT_TYPE_IMAGE;
    img->super.visible = XF_VIEW_UNIT_VISIBALE_TRUE;
    img->super.onMessageReceiver = onMessageReceiver;
    img->data = data;
    img->width = width;
    img->height = height;
    return img;
}

void XF_VIEW_ImageDelete(XF_VIEW_Image* img) {
    XF_free(img);
}

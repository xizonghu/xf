#ifndef __XF_LABEL_H__
#define __XF_LABEL_H__

typedef struct XF_VIEW_LABEL_S {
    XF_VIEW_Unit super;
    char *val;
} XF_VIEW_Label;

extern XF_VIEW_Label *XF_VIEW_LabelNew(attr x, attr y, const char *val);
extern void XF_VIEW_LabelDelete(XF_VIEW_Label* label);

extern void XF_VIEW_LabelSetValue(XF_VIEW_Label *label, char *val);

#endif

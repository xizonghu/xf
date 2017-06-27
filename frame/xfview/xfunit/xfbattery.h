#ifndef __XF_BATTERY_H__
#define __XF_BATTERY_H__

typedef struct XF_VIEW_BATTERY_S {
    XF_VIEW_Unit super;
    attr val;
    void (*show)(uint8 val);
} XF_VIEW_Battery;

extern XF_VIEW_Battery *XF_VIEW_BatteryNew(attr x, attr y, void (*show)(uint8 val));
extern void XF_VIEW_BatteryDelete(XF_VIEW_Battery *bat);

extern void XF_VIEW_BatterySetVal(XF_VIEW_Battery *bat, uint8 val);

#endif

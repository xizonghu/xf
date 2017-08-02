#ifndef __XF_TIMER_H__
#define __XF_TIMER_H__

#include "xftick.h"

typedef struct XF_TIMER_S {
    XF_Tick timeout;
    uint8 overflow;
} XF_Timer;

extern void XF_TimerSetTimeout(XF_Timer *timer, uint16 timeoutMS);
extern uint8 XF_TimerIsTimeout(XF_Timer *timer);
extern void XF_TimerDelayMs(uint16 ms);

#endif

#include "typedef.h"
#include "xftimer.h"

void XF_TimerSetTimeout(XF_Timer *timer, uint16 timeoutMS) {
    XF_Timer tick = XF_TickGetValue();
    timer->timeout = timeoutMS + tick;
    if (timer->timeout < tick) timer->overflow = 1;
}

uint8 XF_TimerIsTimeout(XF_Timer *timer) {
    XF_Timer tick = XF_TickGetValue();
    if (0 == timer->overflow) {
        if (timer->timeout < tick) return 1;
    }
    else {
        if (timer->timeout > tick) timer->overflow = 0;
    }
    return 0;
}

void XF_TimerDelayMs(uint16 ms) {
    XF_Timer t = {0};

    XF_TimerSetTimeout(&t, ms);
    while (!XF_TimerIsTimeout(&t));
}

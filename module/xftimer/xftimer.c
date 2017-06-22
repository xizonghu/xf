#include "xftypedef.h"
#include "xftimer.h"

static XF_Timer *mTimerListHead = XF_NULL;

int8 XF_TimerStart(XF_Timer *t) {
    XF_Timer *pos = XF_NULL;

    if (XF_NULL == t) return -1;
    if (XF_NULL == mTimerListHead) {
        mTimerListHead = t;
        t->next = XF_NULL;
        return 0;
    }

    //tip:没有考虑已存在的情况
    for (pos = mTimerListHead; XF_NULL != pos->next; pos = pos->next);
    pos->next = t;
    t->next = XF_NULL;
    return 0;
}

uint16 XF_TimerStop(XF_Timer *t) {
    XF_Timer *prev = XF_NULL;

    if (XF_NULL == t) return -1;
    if (XF_NULL == mTimerListHead) return -2;

    if (mTimerListHead == t) {
        mTimerListHead = mTimerListHead->next;
        t->next = XF_NULL;
        return 0;
    }

    for (prev = mTimerListHead; prev->next != XF_NULL && prev->next != t; prev = prev->next);
    if (XF_NULL == prev->next) return -3;

    if (t == prev->next) {
        prev->next = prev->next->next;
        t->next = XF_NULL;
        return 0;
    }

    return 0;

}

uint16 XF_TimerPoll() {

}


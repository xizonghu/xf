#include "xftypedef.h"

#include "xfsa.h"

#define NULL    0

typedef struct XF_Signal_s {
    XF_SignalId id;
    uint8 posAction;  //指向空位置
    uint8 sizeAction;
    XF_SignalState state;
    const XF_SignalAction **queueAction;
    struct XF_Signal_s *next;
} XF_Signal;

static XF_Signal *mHeadSignal = NULL;

static void XF_SignalSetState(XF_Signal *s, XF_SignalState state) {
    s->state = state;
}

XF_SAErrno XF_SignalRegister(XF_Signal *s) {
    XF_Signal *ps = mHeadSignal;

    if(NULL == mHeadSignal) {
        mHeadSignal = s;
        mHeadSignal->next = 0;
        return XF_SA_SUCCESS;
    }

    while(1) {
        if(NULL == ps) {
            ps->next = s;
            s->next = NULL;
            break;
        }
        ps = ps->next;
    }

    return XF_SA_SUCCESS;
}

XF_SAErrno XF_SignalUnregister(XF_Signal *s) {
    XF_Signal *ps = mHeadSignal;

    if(NULL == mHeadSignal) {
        return XF_SA_ERR_EMPTY;
    }

    if(s == mHeadSignal) {
        mHeadSignal = NULL;
        return XF_SA_SUCCESS;
    }

    while(1) {
        if(NULL == ps->next) {
            return XF_SA_ERR_EMPTY;
        } else if(s == ps->next) {
            break;
        }
        ps = ps->next;
    }

    ps->next = ps->next->next;
    s->next = 0;

    return XF_SA_SUCCESS;
}

XF_SAErrno XF_SignalMainLoop() {
    XF_Signal *ps = mHeadSignal;
    uint8 i = 0;

    if(NULL == mHeadSignal) {
        return XF_SA_SUCCESS;
    }

    while(ps) {
        if(XF_SIGNAL_STATE_NOTIFY == XF_SignalGetState(ps)) {
            XF_SignalProcessAction(ps);
            i++;
        }
        ps = ps->next;
    }

    return i;
}

XF_SAErrno XF_SignalCreate(XF_Signal *s, XF_SignalId id, uint8 size, const XF_SignalAction **bufActions) {
    s->id = id;
    s->posAction = 0;
    s->sizeAction = size;
    s->state = XF_SIGNAL_STATE_STOP;
    s->queueAction = (XF_SignalAction**)bufActions;
    s->next = 0;
    return XF_SA_SUCCESS;
}

XF_SAErrno XF_SignalStart(XF_Signal *s) {
    XF_SignalSetState(s, XF_SIGNAL_STATE_LISTEN);
	return XF_SA_SUCCESS;
}

XF_SAErrno XF_SignalStop(XF_Signal *s) {
    XF_SignalSetState(s, XF_SIGNAL_STATE_STOP);
	return XF_SA_SUCCESS;
}

XF_SignalState XF_SignalGetState(XF_Signal *s) {
    return s->state;
}

XF_SAErrno XF_SignalAddAction(XF_Signal *s, XF_SignalAction *act) {
    if(NULL == act || NULL == act->handler) return XF_SA_ERR_NULL_POINTER;

    if((s->posAction + 1) >= s->sizeAction) {
        return XF_SA_ERR_FULL;
    }
	
    s->queueAction[s->posAction] = act;
    s->posAction++;
    return XF_SA_SUCCESS;
}

XF_SAErrno XF_SignalRemoveAction(XF_Signal *s, XF_SignalAction *act) {
    uint8 i = 0;
    if(s->posAction <= 0) {
        return XF_SA_ERR_EMPTY;
    }

    for(i = 0; i < s->posAction; i++) {
        if(s->queueAction[i] == act) break;
    }

    if(i == s->posAction) return XF_SA_ERR_EMPTY;

    for(; i < s->posAction; i++) {
        s->queueAction[i] = s->queueAction[i+1];
    }
    s->posAction--;
    s->queueAction[s->posAction] = 0;

    return XF_SA_SUCCESS;
}

XF_SAErrno XF_SignalNotifyAction(XF_Signal *s) {
    if(XF_SIGNAL_STATE_LISTEN != XF_SignalGetState(s)) return XF_SA_ERR_STATE;
    XF_SignalSetState(s, XF_SIGNAL_STATE_NOTIFY);
    return XF_SA_SUCCESS;
}

XF_SAErrno XF_SignalProcessAction(XF_Signal *s) {
    uint8 i = 0;
    XF_SignalState state = XF_SignalGetState(s);

    if(!(XF_SIGNAL_STATE_LISTEN == state || XF_SIGNAL_STATE_NOTIFY == state)) return XF_SA_ERR_STATE;
    XF_SignalSetState(s, XF_SIGNAL_STATE_PROCESS);

    for(i = 0; i < s->posAction; i++) {
        s->queueAction[i]->handler(s->id);
    }

    //XF_SignalSetState(s, XF_SIGNAL_STATE_DONE);
	XF_SignalSetState(s, XF_SIGNAL_STATE_LISTEN);
    return XF_SA_SUCCESS;
}
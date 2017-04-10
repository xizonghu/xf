#ifndef __XF_SA_H__
#define __XF_SA_H__

#define XF_SignalNotifyActionSync    XF_SignalProcessAction
#define XF_SignalNotifyActionAsyn    XF_SignalNotifyAction

typedef uint8 XF_SignalState;
typedef uint16 XF_SAErrno;
typedef uint8 XF_SignalId;
typedef void (*XF_signal_action_callback)(XF_SignalId id);

typedef enum {
    XF_SIGNAL_STATE_STOP,
    XF_SIGNAL_STATE_LISTEN,
    XF_SIGNAL_STATE_COMEIN,
    XF_SIGNAL_STATE_NOTIFY,
    XF_SIGNAL_STATE_PROCESS,
    XF_SIGNAL_STATE_DONE,
    XF_SIGNAL_STATE_SIZE
} XF_SignalStateEnum;

typedef enum {
    XF_SA_SUCCESS = (uint16)0,
    XF_SA_ERR = 0x8000,
    XF_SA_ERR_EMPTY,
    XF_SA_ERR_FULL,
    XF_SA_ERR_STATE,
    XF_SA_ERR_NULL_POINTER,
} XF_SAErrnoEnum;

typedef struct {
    XF_signal_action_callback handler;
} XF_SignalAction;

typedef struct XF_Signal_s XF_Signal;

//system call
extern XF_SAErrno XF_SignalRegister(XF_Signal *s);
extern XF_SAErrno XF_SignalUnregister(XF_Signal *s);
extern XF_SAErrno XF_SignalMainLoop();

//signal manage
extern XF_SAErrno XF_SignalCreate(XF_Signal *s, XF_SignalId id, uint8 size, const XF_SignalAction **bufActions);
extern XF_SAErrno XF_SignalStart(XF_Signal *s);
extern XF_SAErrno XF_SignalStop(XF_Signal *s);
extern XF_SignalState XF_SignalGetState(XF_Signal *s);

//action manage
extern XF_SAErrno XF_SignalAddAction(XF_Signal *s, XF_SignalAction *act);
extern XF_SAErrno XF_SignalRemoveAction(XF_Signal *s, XF_SignalAction *act);

//use
extern XF_SAErrno XF_SignalNotifyAction(XF_Signal *s);
extern XF_SAErrno XF_SignalProcessAction(XF_Signal *s);


#endif

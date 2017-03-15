#ifndef __XF_STATE_H__
#define __XF_STATE_H__

typedef struct {
    uint8_t what;
    void *data;
    int size;
} XF_Message;

typedef struct {
    void (*entry)(void);
    void (*exit)(void);
    int (*processMessage)(XF_Message *msg);
} XF_State;

typedef struct {
    XF_State **states;
    uint8_t sizeStates;
    XF_State *currState;
} XF_StateMachine;

int XF_SMachCreate(XF_StateMachine *mach, XF_State *states[], uint8_t size);

int XF_SMachAddState(XF_StateMachine *mach, XF_State *state);

int XF_SMachInitState(XF_StateMachine *mach, XF_State *state);

int XF_SMachTransitiveTo(XF_StateMachine *mach, XF_State *state);

int XF_SMachSendMessage(XF_StateMachine *mach, XF_Message *msg);

#endif
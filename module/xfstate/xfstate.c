#include "xfconf.h"
#include "xfstate.h"

int XF_SMachCreate(XF_StateMachine *mach, XF_State *states[], uint8_t size) {
    mach->states= states;
    mach->sizeStates = size;
    return 0;
}

int XF_SMachAddState(XF_StateMachine *mach, XF_State *state) {
    uint8_t i = 0;
    for(i = 0; i < mach->sizeStates; i++) {
        if(0 != mach->states[i]) continue;
        mach->states[i] = state;
        return 0;
    }
    return -1;
}

int XF_SMachInitState(XF_StateMachine *mach, XF_State *state) {
    mach->currState = state;
    if(mach->currState->entry) mach->currState->entry();
    return 0;
}

int XF_SMachTransitiveTo(XF_StateMachine *mach, XF_State *state) {
    if(mach->currState->exit) mach->currState->exit();
    mach->currState = state;
    if(mach->currState->entry) mach->currState->entry();
    return 0;
}

int XF_SMachSendMessage(XF_StateMachine *mach, XF_Message *msg) {
	if(mach->currState->processMessage)
        return mach->currState->processMessage(msg);
    return 0;
}
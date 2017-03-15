#ifndef __CUNLOCK_H__
#define __CUNLOCK_H__

typedef struct {
    void start();
    void input();
    void timeout();
    void scan();
    int unlock(FP_Pwd *pwd);
} CONTROLLER_Unlock;

extern ControllerBind();

extern CONTROLLER_Unlock cUnlock;

#endif

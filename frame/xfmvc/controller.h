#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

typedef struct {
    void *if;
} CONTROLLER_Interface;

extern ControllerBind();

extern CONTROLLER_Unlock cUnlock;

#endif

#ifndef __XF_TIMER_H__
#define __XF_TIMER_H__

typedef struct XF_TIMER_S {
    uint16 timeout;
    void (*onTrigger)(void);
    struct XF_TIMER_S *next;
} XF_Timer;

extern uint16 XF_TimerStart(XF_Timer *t);
extern uint16 XF_TimerStop(XF_Timer *t);
extern uint16 XF_TimerPoll();  //ģ����ѯ���ܣ��������ѭ����.

//����malloc
extern XF_Timer *XF_TimerNew(uint16 timeout, void (*onTrigger)(void));
extern void XF_TimerDelete(XF_Timer *t);

#endif

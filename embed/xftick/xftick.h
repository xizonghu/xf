#ifndef __XF_TICK_H__
#define __XF_TICK_H__
//���ǵ�Ƕ��ʽtimerһ���Ϊ16bit����һ��tick��ʾʱ�����1ms�����Լ���ʱ������Ϊ65535ms��ÿ��һ������tick���ᱻ���㡣
//���ʹ��tick��Ϊ�鿴��ʱ���߳�ʱ�Ļ�׼�Ļ����䷶Χ���ܴ���һ���������ڡ�

typedef uint16 XF_Tick;

extern void XF_TickInit();
extern XF_Tick XF_TickGetValue(); 

#endif

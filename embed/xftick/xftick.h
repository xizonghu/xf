#ifndef __XF_TICK_H__
#define __XF_TICK_H__
//考虑到嵌入式timer一般多为16bit，计一个tick表示时间过了1ms，所以计数时间周期为65535ms，每过一个周期tick都会被清零。
//如果使用tick作为查看延时或者超时的基准的话，其范围不能大于一个计数周期。

typedef uint16 XF_Tick;

extern void XF_TickInit();
extern XF_Tick XF_TickGetValue(); 

#endif

#ifndef __TIMER_H__
#define __TIMER_H__

extern void bsp_timer_us_init();
extern unsigned int bsp_timer_get_us_counter();

extern void bsp_timer_ms_init();
extern unsigned int bsp_timer_get_ms_counter();

#endif

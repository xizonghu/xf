#ifndef __RTC_H__
#define __RTC_H__

extern void bsp_rtc_init();
extern void bsp_rtc_get_time(char *timebuf);
extern void bsp_rtc_set_time(char *timebuf);

#endif

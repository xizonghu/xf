#include "stdio.h"

#ifndef __API_H__
#define __API_H__

#define api_sprintf(str, format, ...)        sprintf(str, format, __VA_ARGS__)
#define api_sscanf(str, format, ...)         sscanf(str, format, __VA_ARGS__)

//extern int api_sprintf(char *buf, const char *format, ...);
extern int api_time2string(char *str, char *timebuf);
extern int api_time_to_string5(char *str, char *timebuf);
extern int api_int2str(char *str, int val);
extern int api_date_to_string2(char *str, char *timebuf);
extern int api_date_to_string3(char *str, char *datebuf);
extern int api_int_to_str2(char *str, int val);
extern int api_int_to_string4(char *str, int val);
extern int api_version_to_string(char *str, const char *date);


#endif

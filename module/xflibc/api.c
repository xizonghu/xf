#include "hal.h"
#include "stdio.h"
#include "string.h"

#include "api.h"

//int api_sprintf(char *buf, const char *format, ...) {
    //sprintf(buf, format, ...);
//    return 0;
//}

int api_time2string(char *str, char *timebuf) {
	sprintf(str, "%02d-%02d %02d:%02d", *(timebuf + 1), *(timebuf + 2), *(timebuf + 3), *(timebuf + 4));
    return 0;
}

int api_time_to_string5(char *str, char *timebuf) {
	sprintf(str, "20%02d-%02d-%02d %02d:%02d", *(timebuf + 0), *(timebuf + 1), *(timebuf + 2), *(timebuf + 3), *(timebuf + 4));
    return 0;
}

int api_date_to_string2(char *str, char *timebuf) {
    sprintf(str, "%02d-%02d", *(timebuf + 1), *(timebuf + 2));
    return 0;
}

int api_date_to_string3(char *str, char *datebuf) {
    sprintf(str, "20%02dƒÍ%02d‘¬%02d»’", *(datebuf + 0), *(datebuf + 1), *(datebuf + 2));
    return 0;
}

int api_int2str(char *str, int val) {
	sprintf(str, "%03d", val);
    return 0;
}

int api_int_to_str2(char *str, int val) {
	sprintf(str, "%02d", val);
    return 0;
}

int api_int_to_string4(char *str, int val) {
    sprintf(str, "%04d", val);
    return 0;
}

int api_version_to_string(char *str, const char *date) {
    char s_month[5];
    int month, day, year;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    sscanf(date, "%s %d %d", s_month, &day, &year);

    month = (strstr(month_names, s_month)-month_names)/3 + 1;

    sprintf(str, "%04d%02d%02d", year, month, day);
    return 0;
}

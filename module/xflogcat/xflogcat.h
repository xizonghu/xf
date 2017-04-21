#ifndef __XF_LOGCAT_H__
#define __XF_LOGCAT_H__

#define XF_Logcat.v  

typedef struct {
    void (*v)(const char *TAG, ...);
} XF_Logcat;

#endif
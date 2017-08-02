#ifndef __XF_LOGCAT_H__
#define __XF_LOGCAT_H__

#define XF_Logcat.v  

//debug����,ע�͵�����ʾ������Ϣ
#define DEBUG
#define DEBUG_LEVEL_D
#define DEBUG_LEVEL_V

#define LOG_PRINT_LOCAL(...) do { \
    char str[80] = {0}; \
    sprintf(str, __VA_ARGS__); \
    term_send(str, strlen(str)); \
} while(0)

//0.[A]������(Assert)
//1.[E]������(Error)
//2.[W]������(Warn)
//3.[I]����Ϣ(Info)
//4.[D]������(Debug)
//5.[V]����ϸ(Verbose)

#ifdef DEBUG
#define LOG_A(TAG, ...) LOG_PRINT_LOCAL("A " TAG ": " __VA_ARGS__)
#define LOG_E(TAG, ...) LOG_PRINT_LOCAL("E " TAG ": " __VA_ARGS__)
#define LOG_W(TAG, ...) LOG_PRINT_LOCAL("W " TAG ": " __VA_ARGS__)
#define LOG_I(TAG, ...) LOG_PRINT_LOCAL("I " TAG ": " __VA_ARGS__)

#ifdef DEBUG_LEVEL_D
#define LOG_D(TAG, ...) LOG_PRINT_LOCAL("D " TAG ": " __VA_ARGS__)
#else
#define LOG_V(TAG, ...)
#endif

#ifdef DEBUG_LEVEL_V
#define LOG_V(TAG, ...) LOG_PRINT_LOCAL("V " TAG ": " __VA_ARGS__)
#else
#define LOG_V(TAG, ...)
#endif

typedef struct {
    void (*v)(const char *TAG, ...);
} XF_Logcat;

#endif

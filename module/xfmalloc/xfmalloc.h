#ifndef __XF_MALLOC_H__
#define __XF_MALLOC_H__

typedef struct XF_MALLOC_CONFIG_S {
    void *addr;
    uint16 size;
    uint16 sizeAvalid;
    uint16 sizeUsed;
} XF_MALLOC_CONFIG_T;

extern XF_MALLOC_CONFIG_T XF_MallocConfig;  //需要外部实现
extern void *XF_malloc(uint8 numbytes);
extern void XF_free(void *firstbyte);

#endif
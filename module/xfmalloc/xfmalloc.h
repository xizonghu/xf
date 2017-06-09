#ifndef __XF_MALLOC_H__
#define __XF_MALLOC_H__

#define XF_MALLOC_SIZE    512

typedef struct XF_MALLOC_CONFIG_S {
    void *addr;
    uint16 size;
} XF_MALLOC_CONFIG_T;

extern XF_MALLOC_CONFIG_T XF_MallocConfig;  //��Ҫ�ⲿʵ��
extern void *XF_malloc(uint8 numbytes);
extern void XF_free(void *firstbyte);

#endif
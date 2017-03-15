#ifndef __XF_MALLOC_H__
#define __XF_MALLOC_H__

#define XF_MALLOC_SIZE    5120

extern void *XF_malloc(uint8_t numbytes);
extern void XF_free(void *firstbyte);

#endif
#ifndef __XF_MALLOC_H__
#define __XF_MALLOC_H__

#define XF_MALLOC_SIZE    512

extern void *XF_malloc(uint8 numbytes);
extern void XF_free(void *firstbyte);

#endif
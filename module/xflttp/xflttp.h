#ifndef __XF_LTTP_H__
#define __XF_LTTP_H__

#include "xftypedef.h"

//LTTP(Linked Things Transfer Protocol, ��ʽ����Э��)

#ifdef __cplusplus
extern "C" {
#endif

//tip:Ҳ������ֻ��ָ����ʽ�Ľṹ���ʺ϶���ΪLTTP_PACKET_P_T
typedef struct LTTP_PACKET_S {
    uint8 src;
    uint8 dst;
    int size;
    char data[0];
} __attribute__ ((packed)) LTTP_PACKET_T;

extern LTTP_PACKET_T *lttp_bytes_to_object(char *data);
extern uint16 lttp_to_bytes(char *b, uint8 src, uint8 dst, int size, char *data);

#ifdef __cplusplus
}
#endif

#endif

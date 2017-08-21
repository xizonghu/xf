#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xflttp.h"

LTTP_PACKET_T *lttp_bytes_to_object(char *data) {
    LTTP_PACKET_T *pack = (LTTP_PACKET_T *)data;
    return pack;
}

uint16 lttp_to_bytes(char *b, uint8 src, uint8 dst, int size, char *data) {
    LTTP_PACKET_T *pack = (LTTP_PACKET_T*)b;
    pack->src = src;
    pack->dst = dst;
    pack->size = size;
    memcpy((char*)pack->data, data, size);
    return sizeof(LTTP_PACKET_T) + pack->size;
}


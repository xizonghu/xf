#include <string.h>

#include "xftypedef.h"
#include "xffifo.h"

#define XF_NULL  0

void XF_FIFOInit(XF_Fifo *fifo, void *bufItems, uint16 sizeItem, uint16 countItem) {
    fifo->posHead = XF_NULL;
    fifo->postTail = XF_NULL;
    fifo->bufItems = bufItems;
    fifo->sizeItem = sizeItem;
    fifo->countItem = countItem;
}

uint16 XF_FIFOUsedSize(XF_Fifo *fifo) {
    return (fifo->posHead > fifo->postTail) ? (fifo->countItem - fifo->posHead + fifo->postTail) : (fifo->postTail - fifo->posHead);
}

uint16 XF_FIFOUnusedSize(XF_Fifo *fifo) {
    return (fifo->posHead <= fifo->postTail) ? (fifo->countItem - fifo->postTail + fifo->posHead) : (fifo->posHead - fifo->postTail);
}

uint16 XF_FIFORead(XF_Fifo *fifo, void *item) {
    if(0 == XF_FIFOUsedSize(fifo)) {
        return 0;
    }

    memcpy((char*)item, (char*)fifo->bufItems + fifo->posHead * fifo->sizeItem, fifo->sizeItem);
    fifo->posHead = (fifo->posHead + 1) % fifo->countItem;

    return 1;

}

uint16 XF_FIFOWrite(XF_Fifo *fifo, void *item) {

    if(0 == XF_FIFOUnusedSize(fifo)) {
        return 0;
    }

    memcpy((char*)fifo->bufItems + fifo->postTail * fifo->sizeItem, (char*)item, fifo->sizeItem);
    fifo->postTail = (fifo->postTail + 1) % fifo->countItem;

    //Êý¾Ý±»¸²¸Ç
    if(fifo->posHead == fifo->postTail) fifo->posHead = (fifo->postTail + 1) % fifo->countItem;

    return 1;

}

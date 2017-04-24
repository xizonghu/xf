#include "xftypedef.h"

#include "xfutil.h"

#define HEXSTR(val) (((val) > 9) ? ((val) - 10 + 'A') : ((val) + '0'))

//uint16 XF_ByteToHex(void *str, const void *b, uint16 size) {
//(void)的大小未知，所以不能使用str++，故换为(uint8*)，不能使用(uint16*)，str++会移动2个byte
uint16 XF_ByteToHex(uint8 *str, const uint8 *b, uint16 size) {
	uint8 *src = str;

    while(size-- > 0) {
        *(str++) = HEXSTR(*b >> 4);  //*(b++) / 16
        *(str++) = HEXSTR(*b & 0x0F);  //*(b++) % 16
        *(str++) = ' ';
		b++;
    }
    *(str++) = '\0';

    return (uint16)(str - src);
}

//static int XF_ByteToHex(const char *data, int size) {
//    char hexStr[4] = {0};
//    int i = 0;
//    for(i = 0; i < size; i++) {
//        sprintf(hexStr, "%02x", *(data + i));
//        printf(" %s", hexStr);
//    }
//    printf("\n");
//    return 0;
//}

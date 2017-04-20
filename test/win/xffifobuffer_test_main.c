#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#include "xftypedef.h"
#include "xffifobuffer.h"

int main() {
    XF_FIFOBuffer testfifo = {0};
    char buffer[6] = {0};
    char str[10] = {0};
    int size = 0;
	int i = 100;

    XF_FIFOBufferInit(&testfifo, buffer, sizeof(buffer));

    //–¥∫Ø ˝≤‚ ‘
    //Õ∑<Œ≤£¨ø’œ–>ø…–¥
    size = XF_FIFOBufferWrite(&testfifo, "12", 2);
    size = XF_FIFOBufferWrite(&testfifo, "34", 2);
    //Õ∑<Œ≤£¨ø’œ–<ø…–¥
    size = XF_FIFOBufferWrite(&testfifo, "56", 2);
    //Õ∑>Œ≤£¨ø’œ–<ø…–¥£¨Œª÷√ £”‡>ø…–¥
    size = XF_FIFOBufferRead(&testfifo, str, 1);str[size] = 0;
    size = XF_FIFOBufferWrite(&testfifo, "78", 2);
    //Õ∑>Œ≤£¨ø’œ–<ø…–¥£¨Œª÷√ £”‡<ø…–¥
    size = XF_FIFOBufferWrite(&testfifo, "90", 2);

	size = XF_FIFOBufferRead(&testfifo, str, 6);str[size] = 0;
    //memset(buffer, 0, sizeof(buffer));

    //≤‚∂¡∫Ø ˝
    // £”‡Œª÷√>∂¡
    size = XF_FIFOBufferWrite(&testfifo, "1234", 4);
    size = XF_FIFOBufferRead(&testfifo, str, 2);str[size] = 0;
    // £”‡Œª÷√<=∂¡£¨
    size = XF_FIFOBufferRead(&testfifo, str, 5);str[size] = 0;
    size = XF_FIFOBufferWrite(&testfifo, "5678", 4);
    size = XF_FIFOBufferRead(&testfifo, str, 1);str[size] = 0;
    size = XF_FIFOBufferRead(&testfifo, str, 2);str[size] = 0;

	srand(time(0));
	while(i--) {
        int len = rand()%sizeof(buffer);
		memcpy(str, "123456", len);str[len] = 0;
		size = XF_FIFOBufferWrite(&testfifo, str, strlen(str));
		printf("%d:[%s]			", size, str);
		len = rand()%sizeof(buffer);
		size = XF_FIFOBufferRead(&testfifo, str, len);str[size] = 0;
		printf("%d:[%s]\n", size, str);
    }
    return 0;
}
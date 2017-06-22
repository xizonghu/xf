int sys_strlen(char *str) {
    int i = 0;
    while(*(str + i) != 0x00) {
        i++;
    }
    return i;
}

int sys_strcat(char *dst, char *src) {
    int i = 0;
    int len = sys_strlen(dst);
    while(*(src + i) != 0x0) {
        *(dst + i + len) = *(src + i);
        i++;
    }
    *(dst + i + len) = 0x0;
    return i;
}

int sys_strcpy(char *dst, char *src) {
    int i = 0;
    while(*(src + i) != 0x0) {
        *(dst + i) = *(src + i);
        i++;
    }
    *(dst + i) = 0x0;
    return i;
}

char *sys_strstr(const char * str1,const char * str2)
{
    char *cp = (char *)str1;
    char *s1, *s2;
 
    if (!*str2)
        return((char *)str1);
 
    while (*cp)
    {
        s1 = cp;
        s2 = (char *)str2;
 
        while (*s1 && *s2 && !(*s1 - *s2))
            s1++, s2++;
 
        if (!*s2)
            return(cp);
 
        cp++;
    }
    return(SYS_NULL);
}

int sys_strcmp(char *a, char *b){
    int ret = 0;
    if(!a || !b) return -2;
    while(!(ret = *(unsigned char*)a - *(unsigned char*)b) && *b) {
        a++;
        b++;
    }
    if (ret < 0) {
        ret = -1 ;
    } else if (ret > 0) {
        ret = 1 ;
    }

    return ret;
}

int sys_memcmp(char *a, char *b, int size) {
    int i = 0;
    if(size <= 0)
        return -2;

    for(i = 0 ; i < size; i++) {
        if(*(a + i) > *(b + i))
            return 1;
        else if(*(a + i) < *(b + i))
            return -1;
    }
    return 0;
}

int sys_memcpy(char *dst, char *src, int size) {
    int i = 0;
    for(i = 0; i < size; i++) {
        *(dst + i) = *(src + i);
    }
    return i;
}

char* sys_memstr(char *dst, int dstSize, char *src, int srcSize) {
    int i = 0, j = 0;
    int size = dstSize - srcSize;
    if(0 > size) {
        return SYS_NULL;
    }

    for(i = 0; i <= size; i++) {
        for(j = 0; j < srcSize; j++) {
            if(*(dst + i + j) != *(src + j))
                break;
        }
        if(j == srcSize) return (dst + i);
    }

    return SYS_NULL;
}

/*void sys_delay_ms(unsigned int ms) {                         
	unsigned int a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}*/

int sys_memset(char *src, char ch, int size) {
    int i = 0;
    for(i = 0; i < size; i++) {
        *(src + i) = ch;
    }
    return i;
}

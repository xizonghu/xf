#include "xfstring.h"

int XF_strcmp(const char *str1,const char *str2)
{
    /*������while(*str1++==*str2++)���Ƚϣ��������ʱ�Ի�ִ��һ��++��
    return���صıȽ�ֵʵ��������һ���ַ���Ӧ��++�ŵ�ѭ�����н��С�*/
    while(*str1 == *str2)
    {
        if(*str1 == '\0')
            return 0;
        str1++;
        str2++;
    }
    return *str1 - *str2;
}
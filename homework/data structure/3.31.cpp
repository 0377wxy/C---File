// 3.31

#include <stdio.h>

int main()
{
    char s[100];
    scanf("%s", &s);
    int n = 0;
    for (; s[n] != '@'; n++)
    {
    }
    n = n - 1;
    for (int i = 0; i < n; i++, n--)
    {
        if (s[i] != s[n])
        {
            printf("N");
            return 0;
        }
    }
    printf("Y");
    return 0;
}
/*
运行结果：
qwertrewq@
Y
qwerqw@
N
*/
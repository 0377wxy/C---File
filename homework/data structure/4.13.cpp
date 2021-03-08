// 4.13

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Str
{
    char s[40];
    int lenght;
};

int main()
{
    struct Str *p1;
    p1 = (struct Str *)malloc(sizeof(struct Str));
    scanf("%s", &(p1->s));
    p1->lenght = strlen(p1->s);

    struct Str *p2;
    p2 = (struct Str *)malloc(sizeof(struct Str));
    scanf("%s", &(p2->s));
    p2->lenght = strlen(p2->s);

    int f[40] = {0};
    for (int i = 0; i < p1->lenght; i++)
    {
        int F = 0;
        for (int k = 0; k < p2->lenght; k++)
        {
            if (p1->s[i + k] != p2->s[k])
            {
                F = 1;
                break;
            }
        }
        if (F == 0)
        {
            for (int k = 0; k < p2->lenght; k++)
            {
                f[i + k] = 1;
            }
        }
    }
    for (int i = 0; i < p1->lenght; i++)
    {
        if (f[i] == 0)
        {
            printf("%c", p1->s[i]);
        }
    }
    return 0;
}

/*
运行结果：
1，
qwerqwerqwer
we
qrqrqr
2.
qwererertttterter
erer
qwtttterter
*/
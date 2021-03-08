// 4.10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Str
{
    char s[30];
    int lenght;
};

void reverse(struct Str *p)
{
    char c[30];
    for (int i = 0; i < p->lenght; i++)
    {
        c[p->lenght - i - 1] = p->s[i];
    }
    c[p->lenght] = '\0';
    strcpy(p->s, c);
}

int main()
{
    struct Str *p;
    p = (struct Str *)malloc(sizeof(struct Str));
    scanf("%s", &(p->s));
    p->lenght = strlen(p->s);
    reverse(p);
    printf("%s", p->s);
    return 0;
}

/*
运行结果：
asdf
fdsa
*/
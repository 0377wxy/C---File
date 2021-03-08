// 4.11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Str
{
    char s[30];
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

    struct Str *p3;
    p3 = (struct Str *)malloc(sizeof(struct Str));
    int n[30];
    int j = 0;

    int num[150] = {0};
    for (int i = 0; i < p2->lenght; i++)
    {
        num[int(p2->s[i])] = 1;
    }
    for (int i = 0; i < p1->lenght; i++)
    {
        if (num[int(p1->s[i])] == 0)
        {
            p3->s[j] = p1->s[i];
            n[j] = i;
            j++;
        }
    }
    for (int i = 0; i < j; i++)
    {
        printf("%c , %d\n", p3->s[i], n[i]);
    }
    return 0;
}

/*
运行结果：
qwertyuiop
iywtw
q , 0
e , 2
r , 3
u , 6
o , 8
p , 9
*/
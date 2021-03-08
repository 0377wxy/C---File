// 3.18

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Stack
{
    int num;
    char p[20];
};

void stack_initialization(struct Stack *s)
{
    s->num = -1;
}
void push_back(struct Stack *s, char a)
{
    if (s->num >= 20)
    {
        printf("栈满\n");
    }
    else
    {
        s->num = s->num + 1;
        s->p[s->num] = a;
    }
}
char back(struct Stack *s)
{
    if (s->num >= -1)
    {
        return s->p[s->num];
    }
    else
    {
        printf("栈为空\n");
        return '0';
    }
}
void pop(struct Stack *s)
{
    s->num--;
}

int main()
{
    printf("输入表达式：\n");
    char c[40];
    scanf("%s", &c); // 读入表达式
    struct Stack *s = (struct Stack *)malloc(sizeof(struct Stack));
    stack_initialization(s); // 初始化栈
    for (int i = 0; c[i] != '\0'; i++)
    {
        if (c[i] == '(' || c[i] == '{' || c[i] == '[')
        {
            push_back(s, c[i]);
        }
        else
        {
            char a = back(s);
            if (c[i] == ')' || c[i] == '}' || c[i] == ']')
            {
                if (a == '0' || a != '(' && c[i] == ')' || a != '{' && c[i] == '}' || a != '[' && c[i] == ']')
                {
                    printf("不匹配\n");
                    return 0;
                }
                else
                {
                    if (a == '(' && c[i] == ')' || a == '{' && c[i] == '}' || a == '[' && c[i] == ']')
                    {
                        pop(s);
                    }
                }
            }
        }
    }
    if (s->num != -1)
    {
        printf("不匹配\n");
    }
    else
    {
        printf("匹配完成\n");
    }
    free(s);
    return 0;
}

/*
运行结果：

输入表达式：
((({{{[[]]}}))
不匹配

输入表达式：
(34{ded[ed]})(){}[]
匹配完成

*/

// 2.23
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node
{
    char date = '!';
    Node *p = NULL;
};
struct Link
{
    struct Node *start;
    struct Node *end;
};

void insert(struct Link *L) // 插入链表元素
{
    L->start = (struct Node *)malloc(sizeof(struct Node));
    L->end = L->start;
    int n = 0;
    char a;
    printf("元素个数:\n");
    scanf("%d", &n);
    a = getchar();
    printf("元素内容：\n");
    for (int i = 0; i < n; i++)
    {
        struct Node *p1 = (struct Node *)malloc(sizeof(struct Node));
        p1->p = NULL;
        scanf("%c", &(p1->date));
        a = getchar();
        L->end->p = p1;
        L->end = p1;
    }
}

struct Link *connect(struct Link *L1, struct Link *L2) // 连接两个链表
{
    struct Link *C = (struct Link *)malloc(sizeof(struct Link));
    int a1 = 0, a2 = 0;
    struct Node *p1 = L1->start;
    // 确定新链表起始位置
    while (p1 != L1->end)
    {
        a1++;
        p1 = p1->p;
    }
    struct Node *p2 = L2->start;
    while (p2 != L2->end)
    {
        a2++;
        p2 = p2->p;
    }
    if (a2 > a1)
    {
        struct Link *temp = L2;
        L2 = L1;
        L1 = temp;
    }
    // 连接两个表
    C->start = L1->start;
    L1->end->p = L2->start->p;
    return C;
}
void delect(struct Link *L) // 释放空间
{
    for (struct Node *p1 = L->start; p1 != NULL;)
    {
        struct Node *p2 = p1->p;
        free(p1);
        p1 = p2;
    }
    free(L);
}

int main()
{
    printf("L1的输入：\n");
    struct Link *L1 = (struct Link *)malloc(sizeof(struct Link));
    insert(L1);
    printf("L2的输入：\n");
    struct Link *L2 = (struct Link *)malloc(sizeof(struct Link));
    insert(L2);
    struct Link *L3 = connect(L1, L2);
    for (struct Node *p1 = L3->start->p; p1 != NULL; p1 = p1->p)
    {
        printf("%c  ", p1->date);
    }
    delect(L3);
    return 0;
}

/*
运行结果：
L1的输入：
元素个数:
3
元素内容：
q 
w
e
L2的输入：
元素个数:
2
元素内容：
t
y
q  w  e  t  y
*/
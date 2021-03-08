#include <stdio.h>
#include <stdlib.h>
#define LENGTH 5

struct Queue
{
    char s[LENGTH];
    int rear;   // 队尾元素位置
    int lenght; // 内含元素个数
};

void insert(struct Queue *q)
{
    char a, b;
    scanf("%c", &a);
    b = getchar();
    if (q->lenght >= LENGTH)
    {
        printf("空间已满\n");
    }
    else
    {
        q->s[q->rear] = a;
        q->rear = (q->rear + 1) % LENGTH;
        q->lenght++;
    }
}

void gethead(struct Queue *q)
{
    if (q->lenght <= 0)
    {
        printf("无元素\n");
    }
    else
    {
        char a = q->s[(q->rear - q->lenght + LENGTH) % LENGTH];
        q->lenght--;
        printf("%c\n", a);
    }
}

int main()
{
    struct Queue *q;
    q = (struct Queue *)malloc(sizeof(struct Queue));
    q->rear = 0;
    q->lenght = 0;
    int f = 1;
    while (1)
    {
        printf("入：1    出：0    停：2\n");
        scanf("%d", &f);
        getchar();
        if (f == 1)
        {
            insert(q);
        }
        else if (f == 0)
        {
            gethead(q);
        }
        else
        {
            return 0;
        }
    }
}

/*
运行结果：
入：1    出：0    停：2
1
q
入：1    出：0    停：2
1
w
入：1    出：0    停：2
0
q
入：1    出：0    停：2
0
w
入：1    出：0    停：2
0
无元素
入：1    出：0    停：2
1
a
入：1    出：0    停：2
1
s
入：1    出：0    停：2
1
d
入：1    出：0    停：2
1
f
入：1    出：0    停：2
1 
g
入：1    出：0    停：2
1
h
空间已满
入：1    出：0    停：2
0
a
入：1    出：0    停：2
0
s
入：1    出：0    停：2
0
d
入：1    出：0    停：2
0
f
入：1    出：0    停：2
0
g
入：1    出：0    停：2
0
无元素
入：1    出：0    停：2
2
*/
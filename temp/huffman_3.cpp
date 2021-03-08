#include <malloc.h>
#include <iostream>
#include <vector>
#include <string>
typedef char DataType;
#define MAXNUM 50
using namespace std;

class HuffNode /* 哈夫曼树结点的结构 */
{
public:
    DataType data;    /* 数据用字符表示 */
    double weight;    /* 权值 */
    HuffNode *parent; /* 双亲 */
    HuffNode *left;   /* 左孩子 */
    HuffNode *right;  /* 右孩子 */
    HuffNode *next;
};
typedef struct /* 哈夫曼编码的存储结构 */
{
    DataType cd[MAXNUM]; /* 存放编码位串 */
    int start;           /* 编码的起始位置 */
} HuffCode;

/* 建立哈夫曼树 */
HuffNode *HuffmanCreate(HuffNode *ht, int &n)
{
    int i, k;
    double m1, m2;
    /*初始化*/
    ht->left = NULL;
    ht->right = NULL;
    ht->parent = NULL;
    ht->next = NULL;
    HuffNode *p = ht;

    cout << "权值是否确定?(Y/N)" << endl;
    char at;
    cin >> at;

    if (at == 'Y') // 给定权值的情况，题目不是这个要求
    {
        while (1) /* 输入结点值和信息 */
        {

            DataType c;
            printf("第%d个元素的=>\n\t结点值：", i);
            scanf("%c", &c);
            if (c == '#')
            {
                printf("输入结束\n");
                break;
            }
            p->next = (HuffNode *)malloc(sizeof(HuffNode));
            /*初始化*/
            p = p->next;
            p->left = NULL;
            p->right = NULL;
            p->parent = NULL;
            p->next = NULL;

            p->data = c;
            printf("\t权  重：");
            scanf("%lf", &(p->weight));
            getchar();
            n++;
        }
    }
    else // 由任意字符计算出权值
    {
        cout << "请输入一串字符" << endl;
        at = cin.get();
        int asc[70] = {0};
        while (at != '#')
        {
            asc[at - 65]++;
            at = cin.get();
        }
        for (int i = 0; i < 69; i++)
        {
            if (asc[i] != 0)
            {
                p->next = (HuffNode *)malloc(sizeof(HuffNode));
                /*初始化*/
                p = p->next;
                p->left = NULL;
                p->right = NULL;
                p->parent = NULL;
                p->next = NULL;
                p->data = (char)(i + 65);
                p->weight = asc[i];
                n++;
                cout << p->data << "  " << p->weight << endl;
            }
        }
    }

    HuffNode *f;
    for (i = 1; i < n; i++)
    {
        p = (HuffNode *)malloc(sizeof(HuffNode)); // 新建中间节点
        f = ht->next;
        p->data = '@'; // 中间节点的数据都为 “ @ ”
        p->left = NULL;
        p->right = NULL;
        p->parent = NULL;
        p->next = NULL;

        m1 = m2 = 32767; /* 初始化，令m1、m2为整数最大值 */
        HuffNode *p1 = NULL, *p2 = NULL;
        while (f != NULL) /* 找出权值最小的两个结点 */
        {
            if (f->parent == NULL)
                if (f->weight < m1)
                {
                    m2 = m1;        /* m1为最小权值 */
                    p2 = p1;        /* p1为最小权值的位置 */
                    m1 = f->weight; /* m1存放最小权值 */
                    p1 = f;
                }
                else if (f->weight < m2)
                {
                    m2 = f->weight; /* m2为次小权值 */
                    p2 = f;         /* p2为次小权值的位置 */
                }
            f = f->next;
        }
        p1->parent = p;
        p2->parent = p;
        p->weight = m1 + m2; /* 新结点的的权值为最小权值和次小权值的和 */
        p->left = p1;        /* p1为新结点的左孩子 */
        p->right = p2;       /* p2为新结点的右孩子 */

        HuffNode *p3 = ht->next;
        while (p3->next != NULL)
        {
            p3 = p3->next;
        }
        p3->next = p;
    }
    printf("哈夫曼树已成功建立！\n");
    return p; /* 返回结点个数 */
}

void Encoding(HuffNode *h, int n) /* 哈夫曼编码 */
{
    printf("输出哈夫曼编码：\n");
    int i, k, c;
    HuffNode *f = h->next;
    for (i = 1; i <= n; i++) /* 对所有结点循环 */
    {

        string d;
        HuffNode *f1 = f;
        while (f1->parent != NULL) /* 直到树根为止 */
        {
            if (f1->parent->left == f1)
                d.insert(0, 1, '0'); /* 规定左树为代码0 */
            else
                d.insert(0, 1, '1'); /* 规定右树为代码1 */

            f1 = f1->parent; /* f1指双亲的位置 */
        }
        cout << f->data << " " << d << endl;
        f = f->next;
    }
}

void Decoding(HuffNode *ht) /* 哈夫曼译码 */
{
    int m, k;

    DataType c, ch[200]; /* c接收输入电文，ch存储 */
    printf("请输入电文(0 or 1)，以#为结束标志：\n");
    c = getchar();
    k = 1;
    while (c != '#') /* 单个字符循环输入，以'#'结束 */
    {
        ch[k] = c; /* 将单个字符依次存入ch字符串中 */
        c = getchar();
        k = k + 1; /* ch数组下标后移 */
    }
    m = k; /* 标记数组存储末尾位置 */
    HuffNode *f = ht;
    k = 1; /* k记录电文字符的个数 */
    printf("输出哈夫曼译码：\n");
    while (k < m) /* k循环到数组末尾结束 */
    {
        while (f->left != NULL) /* 直到左孩子结点为0结束 */
        {
            if (ch[k] == '0') /* 若接收的字符为0，则存为左孩子 */
                f = f->left;
            if (ch[k] == '1') /* 若接收的字符为1，则存为右孩子 */
                f = f->right;
            k++; /* ch数组下标后移 */
        }
        printf("%c", f->data);
        f = ht; /* 每次都从根结点开始查找 */
    }
    printf("\n");
}

int main()
{
    HuffNode *h, *p;
    int n = 0;
    h = (HuffNode *)malloc(sizeof(HuffNode));
    p = HuffmanCreate(h, n);
    Encoding(h, n);
    Decoding(p);
    return 0;
}
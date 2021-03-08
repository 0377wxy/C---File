#include <iostream>
#include <limits.h>
using namespace std;

//节点类
class Node
{
public:
    int key;
    Node *next;
    Node(int k)
    {
        key = k;
        next = NULL;
    }
};

//单链表类
class List
{
public:
    Node *head;
    Node *tail;
};

//初始化单链表
List *list_initialization(int k)
{
    List *li = new List;
    li->head = new Node(k);
    li->tail = li->head;
    return li;
}

//插入节点,保持升序
void insert_node(List *li, int k)
{
    Node *temp = li->head;
    while (1)
    {
        if (temp->next != NULL && temp->next->key < k)
        {
            temp = temp->next;
        }
        else
        {
            break;
        }
    }
    Node *new_node = new Node(k);
    new_node->next = temp->next;
    temp->next = new_node;
    if (new_node->next == NULL)
    {
        li->tail = new_node;
    }
}

//销毁单链表
void destroy_list(List *li)
{
    Node *temp1 = li->head;
    Node *temp2 = li->head->next;
    while (1)
    {
        delete (temp1);
        if (temp2 == NULL)
        {
            break;
        }
        temp1 = temp2;
        temp2 = temp2->next;
    }
    delete (li);
}

//输出单链表
void print_list(List *li)
{
    cout << "  ---------" << endl;
    for (Node *t = li->head; t != NULL; t = t->next)
    {
        cout << t->key << " ";
    }
    cout << endl;
    cout << "  ---------" << endl
         << endl;
}

//合并链表(a+b)
void merge_list(List *a, List *b)
{
    a->tail->next = b->head->next;
    b->head->next = NULL;
}

//逆转链表
void reverse_list(List *li)
{
    if (li->head->next == NULL)
    {
        return;
    }
    Node *front = li->head;
    Node *middle = front->next;
    Node *back = middle->next;
    while (1)
    {
        middle->next = front;
        if (back == NULL)
        {
            break;
        }
        front = middle;
        middle = back;
        back = back->next;
    }
    li->head->next = NULL;
    li->tail = li->head;
    li->head = middle;
}

int main()
{
    List *positive = list_initialization(0);
    List *negative = list_initialization(INT_MIN);

    cout << "请输入要插入的元素（0为终止）" << endl;
    int temp = 1;
    while (1)
    {
        cin >> temp;
        if (!temp) //终止
        {
            break;
        }
        if (temp > 0)
        {
            insert_node(positive, temp);
        }
        else
        {
            insert_node(negative, temp);
        }
    }
    cout << "原链表（带头结点）：" << endl;
    print_list(positive);
    print_list(negative);

    reverse_list(positive);
    reverse_list(negative);

    cout << " 逆转后的链表（带头结点）：" << endl;
    print_list(positive);
    print_list(negative);

    destroy_list(positive);
    destroy_list(negative);
    return 0;
}

/*
1
23
-1
6
-1123
45
-34
5643
-6
342
4
-1
0
*/
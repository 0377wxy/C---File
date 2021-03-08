#include <iostream>
using namespace std;

class Node
{
public:
    int m;
    int num;
    Node *next;
    Node(int x, int nu)
    {
        m = x;
        num = nu;
        next = NULL;
    };
};

class Link
{
public:
    int num;
    Node *start; // 指向第一个元素
    Node *end;   // 指向最后一个元素
    Link()
    {
        num = 0;
        start = NULL;
        end = NULL;
    };
};

void initialization(Link *li) // 读入数据，创建链表
{
    int n, m, temp;
    cout << "请输入人数n  报数上限值m" << endl;
    cin >> n >> m;
    cout << "请依次输入每人持有的密码" << endl;

    li->start = new Node(-1, -1); // 第一个元素(空的)
    li->end = li->start;

    for (int i = 1; i <= n; i++) // 后续元素
    {
        cin >> temp;

        li->end->next = new Node(temp, i);
        li->num++;
        li->end = li->end->next;
    }
    li->end->next = li->start; // 形成一个环
}

void pop_up(Link *li) //弹出停止报数的人
{
    int temp_m = li->start->next->m;
    Node *temp_ptr = li->start->next;
    Node *old = li->start;
    cout << "弹出顺序" << endl;
    while (li->num != 0) // 链表为空才结束
    {
        if (temp_ptr->m != -1)
        {
            temp_m--;
            if (temp_m == 0)
            {
                temp_m = temp_ptr->m;
                cout << temp_ptr->num << endl;
                temp_ptr = temp_ptr->next;
                delete (old->next);
                old->next = temp_ptr;
                li->num--;
            }
            else
            {
                temp_ptr = temp_ptr->next;
                old = old->next;
            }
        }
        else
        {
            temp_ptr = temp_ptr->next;
            old = old->next;
        }
    }
}

int main()
{
    Link *li = new Link();
    initialization(li);
    pop_up(li);
    delete (li);
    return 0;
}
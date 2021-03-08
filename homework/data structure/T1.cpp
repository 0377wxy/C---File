#include <iostream>
using namespace std;

class Node
{
public:
    int m;      // 持有的密码
    int num;    // 人所处的次序
    Node *next; // 指向下一个人
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
    for (int i = 1; i <= n; i++)
    {
        cin >> temp;
        if (li->start == NULL) // 如果输入的是第一个元素
        {
            li->start = new Node(temp, i);
            li->num++;
            li->end = li->start;
        }
        else // 输入的是后续元素
        {
            li->end->next = new Node(temp, i);
            li->num++;
            li->end = li->end->next;
        }
    }
    li->end->next = li->start; // 首尾相连，形成一个环
}

void pop_up(Link *li) // 弹出停止报数的人
{
    int temp_m = li->start->next->m;
    Node *temp_ptr = li->start->next;
    cout << "弹出顺序" << endl;
    while (li->num != 0) // 链表为空才结束
    {

        if (temp_ptr->next->m != -1) //
        {
            temp_m--; // 倒着计数

            if (temp_m <= 1)
            {
                Node *t = temp_ptr->next->next;
                cout << temp_ptr->next->num << endl;
                delete (temp_ptr->next); // 删除倒数到1的节点，释放空间
                li->num--;               // 环中节点个数减一
                temp_ptr->next = t;
                if (temp_ptr->next->m != -1)
                {
                    temp_m = temp_ptr->next->m;
                }
                else
                {
                    temp_m = temp_ptr->next->next->m;
                }
            }
            temp_ptr = temp_ptr->next; // 向下一个节点循环
        }
        else
        {
            temp_ptr = temp_ptr->next;
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

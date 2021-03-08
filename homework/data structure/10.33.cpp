// 10.33  单链表实现简单选择排序

#include <iostream>
using namespace std;

class Node
{
public:
    int key;
    Node *ptr;
    Node()
    {
        key = -1;
        ptr = NULL;
    }
};

int main()
{
    cout << "输入数据数量 和 数据" << endl;
    int n, x;
    cin >> n;
    Node *start = new Node();
    Node *temp = start;
    for (int i = 0; i < n; i++)
    {
        temp->ptr = new Node();
        cin >> x;
        temp->ptr->key = x;
        temp = temp->ptr;
    }
    cout << "输入完成" << endl;

    Node *goal = start; //  指向被替换的对象
    while (goal->ptr->ptr != NULL)
    {
        temp = goal;
        Node *pos = NULL;
        int mi = 99999;
        while (temp->ptr != NULL)
        {
            if (temp->ptr->key < mi)
            {
                mi = temp->ptr->key;
                pos = temp;
            }
            temp = temp->ptr;
        }
        if (pos != goal)
        {
            if (pos != goal->ptr)
            {
                Node *p;

                p = goal->ptr->ptr;
                goal->ptr->ptr = pos->ptr->ptr;
                pos->ptr->ptr = p;

                p = goal->ptr;
                goal->ptr = pos->ptr;
                pos->ptr = p;
            }
            else
            {
                goal->ptr = pos->ptr;
                pos->ptr = goal->ptr->ptr;
                goal->ptr->ptr = pos;
            }
        }

        goal = goal->ptr;
        Node *t = start;
        while (t->ptr != NULL)
        {
            cout << t->ptr->key << " ";
            t = t->ptr;
        }
        cout << endl;
    }

    return 0;
}
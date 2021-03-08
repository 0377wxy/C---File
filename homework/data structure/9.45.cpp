// 9.45 哈希表  链地址法处理冲突

#include <iostream>
using namespace std;

class Node
{
public:
    int key;
    Node *ptr;
    Node()
    {
        key = 999999;
        ptr = NULL;
    }
};

int Prime_number(int x)
{
    int temp[10000] = {0};
    for (int i = 2; i < x / 2; i++)
    {
        if (temp[i] == 1)
        {
            continue;
        }
        for (int j = 2 * i; j < x; j += i)
        {
            temp[j] = 1;
        }
    }
    for (int i = x - 1; i > 0; i--)
    {
        if (temp[i] == 0)
        {
            return i;
        }
    }
}

int Hash(int k, int n)
{
    int x = k % n;
    return x;
}

int main()
{
    cout << "请输入表长（m） ：" << endl;
    int m;
    cin >> m;
    int n = Prime_number(m);
    Node *p = new Node[m];
    cout << "请输入要存储的关键字（0为结束）：" << endl;
    int temp, pos;
    while (1)
    {
        cin >> temp;
        if (temp == 0)
        {
            break;
        }
        pos = Hash(temp, n);
        Node *temp_p = &(p[pos]);
        while (1)
        {
            if (temp_p->key > temp)
            {
                Node *t = temp_p->ptr;
                temp_p->ptr = new Node();
                temp_p->ptr->ptr = t;
                temp_p->ptr->key = temp_p->key;
                temp_p->key = temp;
                break;
            }
            else
            {
                temp_p = temp_p->ptr;
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        cout << i << " 位置： ";
        Node *temp_p = &(p[i]);
        while (temp_p->key != 999999)
        {
            cout << temp_p->key << " ";
            temp_p = temp_p->ptr;
        }
        cout << endl;
    }
    return 0;
}
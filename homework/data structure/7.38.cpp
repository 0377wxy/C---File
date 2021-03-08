// 7.38   中缀表达式 转换 后缀表达式

#include <iostream>
#include <string>
using namespace std;

class Edge
{
public:
    int position;
    Edge *next;
    Edge()
    {
        position = -1;
        next = NULL;
    }
};

class Node
{
public:
    string key;    //关键字
    int in;        //入度数
    Edge *out;     //出度
    Edge *out_end; //出度末尾（用于新建图）
    int flag;      //标记
    Node()
    {
        in = 0;
        out = new Edge();
        out_end = out;
        flag = 0;
    }
};

class Stack
{
public:
    int num;
    int *st = NULL;
    Stack(int a)
    {
        num = 0;
        st = new int[a];
    }
    void push_back(int x)
    {
        st[num] = x;
        num++;
    }
    int back()
    {
        return st[num - 1];
    }
    void pop_back()
    {
        num--;
    }
};

void Post_order(Node *V, int n, int x)
{
    Edge *temp = V[x].out;
    while (temp->position != -1)
    {
        Post_order(V, n, temp->position);
        temp = temp->next;
    }
    cout << V[x].key;
}

int main()
{
    cout << "请输入节点个数：" << endl;
    int n;
    cin >> n;
    Node *V = new Node[n];
    cout << "请依次输入节点关键字: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "节点序号：" << i << "  输入节点关键字： ";
        cin >> V[i].key;
    }
    cout << "请输入节点关系:（前行 后继）（用节点序号表示） " << endl;
    while (1)
    {
        int a, b;
        cin >> a;
        if (a == -1) //	输入-1则终止输入
        {
            break;
        }
        cin >> b;

        V[a].out_end->position = b;
        V[b].in++; // 增加后继节点的入度
        V[a].out_end->next = new Edge();
        V[a].out_end = V[a].out_end->next;
    }

    int top;
    for (int i = 0; i < n; i++) // 寻找树根
    {
        if (V[i].in == 0)
        {
            top = i;
            break;
        }
    }
    Post_order(V, n, top);

    return 0;
}
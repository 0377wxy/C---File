// 7.14   用非递归深搜遍历强连通图

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

void DFS(Node *V)
{
    Stack st(20);
    st.push_back(0);
    V[0].flag = 1;
    cout << V[0].key << " ";
    while (st.num != 0)
    {
        int f = 0;
        Edge *e = V[st.back()].out;
        while (e->position != -1)
        {
            if (V[e->position].flag != 1)
            {
                st.push_back(e->position);
                V[e->position].flag = 1;
                cout << V[e->position].key << " ";
                f = 1;
                break;
            }
            e = e->next;
        }
        if (f == 0)
        {
            st.pop_back();
        }
        /*
        cout << endl
             << "------" << endl;
        for (int i = 0; i < st.num; i++)
        {
            cout << st.st[i] << " ";
        }
        cout << endl
             << "--------" << endl;
        */
    }
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

    DFS(V);

    /*
    cout << "-----图信息-----" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "关键字： " << V[i].key << " "
             << "入度" << V[i].in << endl;
        cout << "  指向的点： ";
        Edge *e = V[i].out;
        while (e != NULL)
        {
            if (e->position != -1)
                cout << e->position << " ";
            e = e->next;
        }
        cout << endl;
    }
    cout << "------------" << endl;
    */

    return 0;
}
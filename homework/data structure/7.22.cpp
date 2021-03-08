// 7.14   用深搜判断两点是否有路径相邻

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
    int flag;      //标记是否输出（用于检查回路）
    Node()
    {
        in = 0;
        out = new Edge();
        out_end = out;
        flag = 0;
    }
};

void DFS(int u, int v, Node *V, int &f)
{
    Edge *e = V[u].out;
    while (e->position != -1)
    {
        if (e->position == v)
            f = 1;
        else
        {
            DFS(e->position, v, V, f);
        }
        e = e->next;
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
    cout << "请输入要查找的两个点" << endl;
    string a, b;
    cin >> a >> b;
    int u, v;
    for (int i = 0; i < n; i++)
    {
        if (V[i].key == a)
        {
            u = i;
        }
        if (V[i].key == b)
        {
            v = i;
        }
    }

    int f = 0;
    DFS(u, v, V, f);
    if (f == 1)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
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
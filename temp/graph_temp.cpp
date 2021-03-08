#include <iostream>
#include <string>
using namespace std;

class Stack
{
public:
    int num;
    int *st = NULL;
    Stack(int a = 30)
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
    int term;
    Node()
    {
        in = 0;
        out = new Edge();
        out_end = out;
        flag = 0;
        term = 0;
    }
};

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
        cout << "   所属学期： ";
        cin >> V[i].term;
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

    Stack st[7];         // 一个星学期一个栈
    int stack_sum = 0;   // 栈内总元素个数
    int stack_index = 1; // 当前被使用的栈

    int f = 1;
    for (int i = 0; i < n; i++) //  寻找第一个入度为0的节点，入栈
    {
        if (V[i].in == 0)
        {
            f = 0;
            st[V[i].term].push_back(i);
        }
    }
    for (int i = 1; i < 7; i++) // 统计栈中元素
    {
        stack_sum += st[i].num;
    }

    if (f == 1) // 若无入度为0的节点，则有回路
    {
        cout << endl;
        cout << "存在回路" << endl;
        return 0;
    }

    cout << "第 1 学期： " << endl;

    while (stack_sum != 0)
    {
        int top = st[stack_index].back(); //取出栈顶元素
        cout << V[top].key << "   ";
        st[stack_index].pop_back();
        V[top].flag = 1; //标记为 已输出

        Edge *e = V[top].out;
        while (e != NULL)
        {
            int temp = e->position;
            V[temp].in--;
            if (V[temp].in == 0)
            {
                st[V[temp].term].push_back(temp); // 新产生的入度为0的节点入栈
            }
            e = e->next;
        }

        if (st[stack_index].num == 0)
        {
            stack_index++;
            if (stack_index < 7 && st[stack_index].num != 0)
            {
                cout << endl;
                cout << "第 " << stack_index << " 学期： " << endl;
            }
        }

        stack_sum = 0;
        for (int i = 1; i < 7; i++) // 统计栈中元素
        {
            stack_sum += st[i].num;
        }
    }
    for (int i = 0; i < n; i++) // 栈空但还有节点未输出则有回路
    {
        if (V[i].flag == 0)
        {
            cout << "存在回路" << endl;
        }
    }
    return 0;
}
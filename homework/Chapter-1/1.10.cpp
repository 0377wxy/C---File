#include <iostream>
using namespace std;

class Stack_order
{
public:
    int num;
    int *st = NULL;
    Stack_order(int a = 30)
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

class Queue_order
{
public:
    int num;
    int *st = NULL;
    Queue_order(int a = 100)
    {
        num = 0;
        st = new int[a];
    }
    void push_back(int x)
    {
        st[num] = x;
        num++;
    }

    int pop()
    {
        int temp = st[0];
        for (int i = 1; i < num; i++)
        {
            st[i - 1] = st[i];
        }
        num--;
        return temp;
    }
};

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

class Stack_Linked
{
public:
    Node *head;
    Node *tail;
    int num;
    Stack_Linked()
    {
        head = new Node(0);
        num = 0;
    }
    int back()
    {
        return head->next->key;
    }
    void push_back(int k)
    {
        Node *temp = new Node(k);
        temp->next = head->next;
        head->next = temp;
        num++;
    }
    void pop_back()
    {
        Node *temp = head->next;
        head->next = head->next->next;
        delete temp;
        num--;
    }
};

class Queue_Linked
{
public:
    Node *head;
    Node *tail;
    int num;
    Queue_Linked()
    {
        num = 0;
        head = new Node(0);
        tail = head;
    }
    void push_back(int k)
    {
        tail->next = new Node(k);
        tail = tail->next;
        num++;
    }
    int pop()
    {
        num--;
        Node *temp = head->next;
        head->next = head->next->next;
        int k = temp->key;
        delete temp;
        return k;
    }
};

int main()
{
    Stack_order stack1;
    Queue_order queue1;
    Stack_Linked stack2;
    Queue_Linked queue2;
    int temp;
    cout << "请输入数值（终止符结束）：" << endl;
    while (cin >> temp)
    {
        stack1.push_back(temp);
        queue1.push_back(temp);
        stack2.push_back(temp);
        queue2.push_back(temp);
    }
    cout << "顺序储存结构的结果：" << endl;
    while (stack1.num)
    {
        int temp = stack1.back();
        if (temp > 0)
        {
            cout << temp << " ";
        }
        stack1.pop_back();
    }
    cout << endl;
    while (queue1.num)
    {
        int temp = queue1.pop();
        if (temp < 0)
        {
            cout << temp << " ";
        }
    }
    cout << endl;

    cout << "链式储存结构的结果：" << endl;
    while (stack2.num)
    {
        int temp = stack2.back();
        if (temp > 0)
        {
            cout << temp << " ";
        }
        stack2.pop_back();
    }
    cout << endl;
    while (queue2.num)
    {
        int temp = queue2.pop();
        if (temp < 0)
        {
            cout << temp << " ";
        }
    }
    cout << endl;
    return 0;
}

/*
1 -2 -5 -67 34 12 -7 34 987 -1234 
*/
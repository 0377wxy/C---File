#include <iostream>
#include <limits.h>
#include <math.h>
#define STACK_SIZE 100;
using namespace std;

class Node
{
public:
    int begin, end;
    int middle;
    int begin_max, end_max;
    int begin_min, end_min;
    int all_max, all_min;
    int begin_f, end_f;
    Node(int b, int e)
    {
        begin = b;
        end = e;
        middle = floor((b + e) / 2);
        begin_max = INT_MAX;
        end_max = INT_MAX;
        all_max = INT_MAX;
        begin_min = INT_MIN;
        end_min = INT_MIN;
        all_min = INT_MIN;
        begin_f = 0;
        end_f = 0;
    }
};

class Stack
{
public:
    Node **st;
    int num;
    Stack()
    {
        st = new Node *[100];
        num = 0;
    }
    ~Stack()
    {
        delete st;
    }
    void push(int b, int e)
    {
        Node *temp = new Node(b, e);
        st[num] = temp;
        num++;
    }
    Node *top()
    {
        return st[num - 1];
    }
    void pop()
    {
        num--;
    }
};

int main()
{
    cout << "要输入的数字个数： ";
    int n, temp;
    int *data = new int[n];
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        data[i] = temp;
    }

    Stack stack;
    stack.push(0, n - 1);
    while (1)
    {
        Node *temp = stack.top();

        if (temp->begin_f == 0)
        {
            if (temp->end - temp->begin > 1)
            {
                stack.push(temp->begin, temp->middle);
                continue;
            }
            else
            {
                temp->begin_max = max(data[temp->begin], data[temp->end]);
                temp->begin_min = min(data[temp->begin], data[temp->end]);
                temp->begin_f = 1;
            }
        }
        if (temp->end_f == 0)
        {
            if (temp->end - temp->begin > 1)
            {
                stack.push(temp->middle, temp->end);
                continue;
            }
            else
            {
                temp->end_max = max(data[temp->begin], data[temp->end]);
                temp->end_min = min(data[temp->begin], data[temp->end]);
                temp->end_f = 1;
            }
        }
        temp->all_max = max(temp->begin_max, temp->end_max);
        temp->all_min = min(temp->begin_min, temp->end_min);
        if (stack.num == 1)
        {
            break;
        }
        else
        {
            stack.pop();
            Node *top = stack.top();
            /*
            cout << temp->begin << "  " << temp->end << " :"
                 << temp->all_max << "  " << temp->all_min << endl;
            */
            if (top->begin == temp->begin)
            {
                top->begin_f = 1;
                top->begin_max = temp->all_max;
                top->begin_min = temp->all_min;
            }
            else
            {
                top->end_f = 1;
                top->end_max = temp->all_max;
                top->end_min = temp->all_min;
            }
            delete temp;
        }
    }
    cout << "最大： " << stack.top()->all_max << endl;
    cout << "最小： " << stack.top()->all_min << endl;
    delete stack.top();

    return 0;
}
// 6.60
#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int date;
    Node *c;
    Node *b;
    Node(int a)
    {
        date = a;
        c = NULL;
        b = NULL;
    }
};

class Tree
{
public:
    Node *root;
    int num = 0;
};

int main()
{
    Tree t1;
    int n = 0;

    t1.root = new Node(1);
    t1.root->c = new Node(2);
    t1.root->c->b = new Node(3);
    t1.root->c->c = new Node(4);
    t1.root->c->c->b = new Node(5);
    t1.root->c->c->b->c = new Node(6);
    t1.root->c->b->c = new Node(7);

    vector<Node *> st1;
    st1.push_back(t1.root);
    Node *p = t1.root;
    while (!st1.empty())
    {
        while (p != NULL)
        {

            st1.push_back(p);
            p = p->c;
        }
        if (!st1.empty())
        {
            p = st1.back();
            if (p->c == NULL)
            {
                n++;
            }
            st1.pop_back();
            p = p->b;
        }
    }
    cout << n << endl;
    return 0;
}

/*
运行结果：
3
*/
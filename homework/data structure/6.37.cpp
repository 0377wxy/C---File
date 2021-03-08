// 6.37
#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int main_data;
    Node *left = NULL;
    Node *right = NULL;

    Node(int x)
    {
        main_data = x;
        left = NULL;
        right = NULL;
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
    Tree t1, t2;

    t1.root = new Node(1);
    t1.root->left = new Node(2);
    t1.root->right = new Node(3);
    t1.root->left->left = new Node(4);
    t1.root->left->right = new Node(5);
    t1.root->left->right->left = new Node(6);
    t1.root->right->right = new Node(7);

    vector<Node *> st1, st2;
    st1.push_back(t1.root);
    Node *p = t1.root;
    while (!st1.empty())
    {
        while (p != NULL)
        {
            cout << " " << p->main_data;
            st1.push_back(p);
            p = p->left;
        }
        if (!st1.empty())
        {
            p = st1.back();
            st1.pop_back();
            p = p->right;
        }
    }

    return 0;
}

/*
运行结果：
 1 2 4 5 6 3 7
*/
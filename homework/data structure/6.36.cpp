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

    t2.root = new Node(1);
    t2.root->left = new Node(2);
    t2.root->right = new Node(3);
    t2.root->left->left = new Node(4);
    t2.root->left->right = new Node(5);
    t2.root->left->right->left = new Node(6);
    //t2.root->right->right = new Node(7);

    vector<Node *> st1, st2;
    st1.push_back(t1.root);
    st2.push_back(t2.root);
    Node *p1 = t1.root;
    Node *p2 = t2.root;
    int f = 1;
    while (!st1.empty() && !st2.empty() && f == 1)
    {
        while (p1 != NULL && p2 != NULL)
        {
            //cout << " " << p1->main_data;
            st1.push_back(p1);
            p1 = p1->left;

            //cout << " " << p2->main_data;
            st2.push_back(p2);
            p2 = p2->left;

            if (p1 != NULL && p2 == NULL || p2 != NULL && p1 == NULL)
            {
                f = 0;
            }
        }
        if (!st1.empty())
        {
            p1 = st1.back();
            st1.pop_back();
            p1 = p1->right;

            p2 = st2.back();
            st2.pop_back();
            p2 = p2->right;

            if (p1 != NULL && p2 == NULL || p2 != NULL && p1 == NULL)
            {
                f = 0;
            }
        }
    }
    if (f == 1)
    {
        cout << "相似" << endl;
    }
    else
    {
        cout << "不相似" << endl;
    }

    return 0;
}

/*
运行结果：
（第45行有效时）
相似
（第45行无效时）
不相似
*/
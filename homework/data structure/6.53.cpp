// 6.53
#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int main_data;
    Node *left = NULL;
    Node *right = NULL;
    int i;

    Node(int x)
    {
        main_data = x;
        left = NULL;
        right = NULL;
        i = 1;
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
    t1.root->left = new Node(2);
    t1.root->right = new Node(3);
    t1.root->left->left = new Node(4);
    t1.root->left->right = new Node(5);
    t1.root->left->right->left = new Node(6);
    t1.root->right->right = new Node(7);

    vector<Node *> st1, st2;
    // st1.push_back(t1.root);
    Node *p = t1.root;
    while (!st1.empty() || p != NULL)
    {
        while (p != NULL)
        {
            // cout << " " << p->main_data;
            st1.push_back(p);
            if (st1.size() > n)
            {
                n = st1.size();
            }
            p = p->left;
        }
        if (!st1.empty())
        {

            if (st1.back()->i == 1)
            {
                (st1.back()->i)++;
                p = st1.back()->right;
            }
            else
            {
                // cout << " " << st1.back()->main_data;
                st1.back()->i = 1;
                st1.pop_back();
                p = NULL;
            }
        }
    }

    p = t1.root;
    int f = 0;
    while (!st1.empty() || p != NULL)
    {
        while (p != NULL)
        {
            // cout << " " << p->main_data;
            st1.push_back(p);
            p = p->left;
        }
        if (!st1.empty())
        {

            if (st1.back()->i == 1)
            {
                (st1.back()->i)++;
                p = st1.back()->right;
            }
            else
            {
                if (st1.size() == n - 1 && st1.back()->left == NULL && st1.back()->right == NULL && f == 0)
                {
                    for (int i = 0; i < st1.size(); i++)
                    {
                        cout << st1[i]->main_data << " ";
                    }
                    cout << endl;
                    f = 1;
                }

                st1.pop_back();
                p = NULL;
            }
        }
    }

    return 0;
}

/*
运行结果：
 1 2 4 
删除 f ，可输出全部的符合要求的路径
*/
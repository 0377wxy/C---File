// 9.32  在二叉排序树中找前驱与后继
#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int main_data;
    Node *left = NULL;
    Node *right = NULL;
    Node *father = NULL;
    int f;

    Node(int x)
    {
        main_data = x;
        left = NULL;
        right = NULL;
        father = NULL;
        f = 1;
    }
};

class Tree
{
public:
    Node *root;
    int num = 0;
    Tree()
    {
        root = NULL;
    }
};

void node_insert(Tree *T, int x)
{
    if (T->root == NULL)
    {
        T->root = new Node(x);
    }
    else
    {
        Node *node = T->root;

        while (1)
        {

            if (x < node->main_data)
            {

                if (node->left != NULL)
                {
                    node = node->left;
                }
                else
                {
                    node->left = new Node(x);
                    node->left->father = node;
                    break;
                }
            }
            else
            {
                if (node->right != NULL)
                {
                    node = node->right;
                }
                else
                {
                    node->right = new Node(x);
                    node->right->father = node;
                    break;
                }
            }
        }
    }
}

Node *search(Tree *T, int x, Node *temp)
{
    if (temp->main_data == x)
    {
        return temp;
    }
    Node *a, *b;
    if (temp->left == NULL)
    {
        a = NULL;
    }
    else
    {
        a = search(T, x, temp->left);
    }
    if (temp->right == NULL)
    {
        b = NULL;
    }
    else
    {
        b = search(T, x, temp->right);
    }

    if (a != NULL)
    {
        return a;
    }
    else if (b != NULL)
    {
        return b;
    }
    else
    {
        return NULL;
    }
}

int Precursor(Tree *T, int x)
{
    Node *aim = search(T, x, T->root);
    if (aim->left != NULL)
    {
        Node *temp = aim->left;
        while (1)
        {
            if (temp->right == NULL)
            {
                return temp->main_data;
            }
            else
            {
                temp = temp->right;
            }
        }
    }
    else
    {
        Node *temp = aim;
        while (1)
        {
            if (temp->father->right == temp)
            {
                return temp->father->main_data;
            }
            else
            {
                temp = temp->father;
            }
        }
    }
}

int Successor(Tree *T, int x)
{
    Node *aim = search(T, x, T->root);
    if (aim->right != NULL)
    {
        Node *temp = aim->right;
        while (1)
        {
            if (temp->left == NULL)
            {
                return temp->main_data;
            }
            else
            {
                temp = temp->left;
            }
        }
    }
    else
    {
        Node *temp = aim;
        while (1)
        {
            if (temp->father->left == temp)
            {
                return temp->father->main_data;
            }
            else
            {
                temp = temp->father;
            }
        }
    }
}

int main()
{
    Tree *T = new Tree();
    int x;
    cout << "读入二叉排序树(0为终止): " << endl;
    while (1)
    {
        cin >> x;
        if (x == 0)
        {
            break;
        }
        else
        {
            node_insert(T, x);
        }
    }
    cout << "要查找的对象： " << endl;
    cin >> x;
    cout << "前驱： " << Precursor(T, x) << endl;
    cout << "后继： " << Successor(T, x) << endl;

    return 0;
}
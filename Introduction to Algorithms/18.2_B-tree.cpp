// B数的基本操作

#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    int num = 0;
    int t = 3;
    vector<int> key;
    vector<Node *> c;
    bool leaf = true;
    Node()
    {
        key = vector<int>(2 * t - 1, 1000);
        c = vector<Node *>(2 * t, NULL);
    }
};

class B_Tree
{
private:
    Node *root;

public:
    static int t;
    static int Read;
    static int Write;
    Node *get_root()
    {
        return root;
    }
    void set_root(Node *ro)
    {
        root = ro;
    }
    B_Tree()
    {
        root = new Node();
        Write++;
    }
    void spilt_child(Node *x, int i)
    {
        Node *z = new Node();
        Node *y = x->c[i];
        z->leaf = y->leaf;
        z->num = t - 1;
        for (int j = 0; j < t - 1; j++)
        {
            z->key[j] = y->key[j + t];
        }
        if (!x->leaf)
        {
            for (int j = 0; j < t; j++)
            {
                z->c[j] = y->c[j + t];
            }
        }
        y->num = t - 1;
        for (int j = x->num; j >= i + 1; j--)
        {
            x->c[j + 1] = x->c[j];
        }
        x->c[i + 1] = z;
        for (int j = x->num - 1; j >= i; j--)
        {
            x->key[j + 1] = x->key[j];
        }
        x->key[i] = y->key[t - 1];
        x->num += 1;
        Write = Write + 3;
    }
    void insert(int k)
    {
        Node *r = root;
        if (r->num == 2 * t - 1)
        {
            Node *s = new Node();
            root = s;
            s->leaf = false;
            s->c[0] = r;
            spilt_child(s, 0);
            insert_nonfull(s, k);
        }
        else
        {
            insert_nonfull(r, k);
        }
    }
    void insert_nonfull(Node *x, int k)
    {
        int i = x->num - 1;
        if (x->leaf)
        {
            while (i >= 0 && x->key[i] > k)
            {
                x->key[i + 1] = x->key[i];
                i--;
            }
            x->key[i + 1] = k;
            x->num++;
            Write++;
        }
        else
        {
            while (i >= 0 && x->key[i] > k)
            {
                i--;
            }
            i++;
            Read++;
            if (x->c[i]->num == 2 * t - 1)
            {
                spilt_child(x, i);
            }
            if (k > x->key[i])
            {
                i++;
            }
            insert_nonfull(x->c[i], k);
        }
    }
    void delete_node(Node *x, int k)
    {
        int i = 0;
        while (i < x->num && k != x->key[i])
        {
            i++;
        }
        if (i < x->num)
        {
            if (x->leaf)
            {
                for (int j = i; j < x->num - 1; j++)
                {
                    x->key[j] = x->key[j + 1];
                }
                x->num -= 1;
            }
            else
            {
                if (x->c[i]->num >= t)
                {
                    x->key[i] = x->c[i]->key[x->c[i]->num - 1];
                    delete_node(x->c[i], x->c[i]->key[x->c[i]->num - 1]);
                }
                else if (x->c[i + 1]->num >= t)
                {
                    x->key[i] = x->c[i + 1]->key[0];
                    delete_node(x->c[i + 1], x->c[i + 1]->key[0]);
                }
                else
                {
                    x->c[i]->key[x->c[i]->num] = x->key[i];
                    for (int j = 0; j < x->c[i + 1]->num; j++)
                    {
                        x->c[i]->key[j + x->c[i]->num + 1] = x->c[i + 1]->key[j];
                    }
                    for (int j = 0; j <= x->c[i + 1]->num; j++)
                    {
                        x->c[i]->c[j + x->c[i]->num + 1] = x->c[i + 1]->c[j];
                    }
                    x->c[i]->num = x->c[i]->num + 1 + x->c[i + 1]->num;
                    delete x->c[i + 1];
                    for (int j = i; j < x->num - 1; j++)
                    {
                        x->key[j] = x->key[j + 1];
                        x->c[j + 1] = x->c[j + 2];
                    }
                    x->num--;
                    delete_node(x->c[i], k);
                }
            }
        }
        else
        {
            i = 0;
            while (k > x->key[i])
            {
                i++;
            }
            if (x->c[i]->num >= t)
            {
                delete_node(x->c[i], k);
            }
            else
            {
                if (i - 1 >= 0 && x->c[i - 1]->num >= t)
                {
                    for (int j = x->c[i]->num; j > 0; j--)
                    {
                        x->c[i]->key[j] = x->c[i]->key[j - 1];
                    }
                    for (int j = x->c[i]->num + 1; j > 0; j--)
                    {
                        x->c[i]->c[j] = x->c[i]->c[j - 1];
                    }
                    x->c[i]->num++;
                    x->c[i]->key[0] = x->key[i - 1];
                    x->c[i]->c[0] = x->c[i - 1]->c[x->c[i - 1]->num];
                    x->key[i - 1] = x->c[i - 1]->key[x->c[i - 1]->num - 1];
                    x->c[i - 1]->num--;
                    delete_node(x->c[i], k);
                }
                else if (i + 1 <= x->num - 1 && x->c[i + 1]->num >= t)
                {
                    x->c[i]->key[x->c[i]->num] = x->key[i];
                    x->c[i]->c[x->c[i]->num + 1] = x->c[i + 1]->c[0];
                    x->c[i]->num++;
                    x->key[i] = x->c[i + 1]->key[0];
                    for (int j = 0; j < x->c[i + 1]->num - 2; j++)
                    {
                        x->c[i]->key[j] = x->c[i]->key[j + 1];
                    }
                    for (int j = 0; j < x->c[i + 1]->num - 1; j++)
                    {
                        x->c[i]->c[j] = x->c[i]->c[j + 1];
                    }
                    x->c[i + 1]->num--;
                    delete_node(x->c[i], k);
                }
                else if (i - 1 >= 0 && x->c[i - 1]->num < t)
                {
                    x->c[i - 1]->key[x->c[i - 1]->num] = x->key[i - 1];
                    for (int j = 0; j < x->c[i]->num; j++)
                    {
                        x->c[i + 1]->key[j + x->c[i + 1]->num + 1] = x->c[i]->key[j];
                    }
                    for (int j = 0; j <= x->c[i]->num; j++)
                    {
                        x->c[i + 1]->c[j + x->c[i + 1]->num + 1] = x->c[i]->c[j];
                    }
                    x->c[i - 1]->num = x->c[i - 1]->num + 1 + x->c[i]->num;
                    delete x->c[i];
                    for (int j = i - 1; j < x->num - 1; j++)
                    {
                        x->key[j] = x->key[j + 1];
                        x->c[j + 1] = x->c[j + 2];
                    }
                    x->num--;
                    delete_node(x->c[i - 1], k);
                }
                else if (i + 1 <= x->num - 1 && x->c[i + 1]->num < t)
                {
                    x->c[i]->key[x->c[i]->num] = x->key[i];
                    for (int j = 0; j < x->c[i + 1]->num; j++)
                    {
                        x->c[i]->key[j + x->c[i]->num + 1] = x->c[i + 1]->key[j];
                    }
                    for (int j = 0; j <= x->c[i + 1]->num; j++)
                    {
                        x->c[i]->c[j + x->c[i]->num + 1] = x->c[i + 1]->c[j];
                    }
                    x->c[i]->num = x->c[i]->num + 1 + x->c[i + 1]->num;
                    delete x->c[i + 1];
                    for (int j = i; j < x->num - 1; j++)
                    {
                        x->key[j] = x->key[j + 1];
                        x->c[j + 1] = x->c[j + 2];
                    }
                    x->num--;
                    delete_node(x->c[i], k);
                }
            }
        }
    }
};

int B_Tree::t = 3;
int B_Tree::Read = 0;
int B_Tree::Write = 0;

int main()
{
    B_Tree *tree = new B_Tree();
    tree->insert(2);
    tree->insert(10);
    tree->insert(15);
    tree->insert(3);
    tree->insert(6);
    tree->insert(7);
    tree->insert(34);
    tree->insert(21);
    tree->insert(4);
    tree->insert(11);
    tree->insert(13);
    tree->insert(9);
    tree->insert(1);
    tree->insert(8);
    tree->insert(12);
    tree->delete_node(tree->get_root(), 11);
    tree->delete_node(tree->get_root(), 10);
    tree->delete_node(tree->get_root(), 6);
    tree->delete_node(tree->get_root(), 15);
    tree->delete_node(tree->get_root(), 7);
    tree->delete_node(tree->get_root(), 9);
    tree->delete_node(tree->get_root(), 13);
    tree->delete_node(tree->get_root(), 12);

    return 0;
}
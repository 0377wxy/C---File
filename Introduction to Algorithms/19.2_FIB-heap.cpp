// 斐波纳契堆

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Node
{
public:
    int key;
    Node *right = NULL;
    Node *left = NULL;
    Node *father = NULL;
    Node *child = NULL;
    int degree = 0;
    bool mark = false;
    Node(int k)
    {
        key = k;
    }
};

class FIB_Heap
{
private:
    Node *min = NULL;
    int num = 0;

public:
    Node *get_min()
    {
        return min;
    }
    void FIB_insert(int k)
    {
        Node *x = new Node(k);
        if (min == NULL)
        {
            min = x;
            x->left = x;
            x->right = x;
        }
        else
        {
            x->left = min;
            x->right = min->right;
            x->left->right = x;
            x->right->left = x;
            if (k < min->key)
            {
                min = x;
            }
        }
        num++;
    }
    void FIB_union(FIB_Heap heap)
    {
        if (heap.min == NULL)
        {
            return;
        }
        else if (this->min == NULL)
        {
            min = heap.min;
            num = heap.num;
        }
        else
        {
            union_heap(heap.min, this->min);
            if (heap.min->key < this->min->key)
            {
                this->min = heap.min;
            }
            this->num += heap.num;
        }
    }
    void union_heap(Node *a, Node *b)
    {
        Node *c = a->right;
        Node *d = b->right;
        c->left = b;
        d->left = a;
        a->right = d;
        b->right = c;
    }
    Node *FBI_extract_min()
    {
        Node *z = min;
        if (z != NULL)
        {
            if (z->degree != 0)
            {
                union_heap(this->min, z->child);
                Node *temp = min->right;
                while (temp->left != z->child)
                {
                    temp->father = NULL;
                    temp = temp->right;
                }
            }
            if (z->right == z)
            {
                min = NULL;
            }
            else
            {
                min->right->left = min->left;
                min->left->right = min->right;
                min = min->right;
                consolidate();
            }
            num--;
        }
        return z;
    }
    void consolidate()
    {
        vector<Node *> A(floor(log2(num)) + 2, NULL);
        Node *w = min;
        for (int i = 0; i < num; i++)
        {
            Node *x = w;
            int d = w->degree;
            while (A[d] != NULL && A[d] != x)
            {
                Node *y = A[d];
                if (y->key < x->key)
                {
                    Node *a = y->left;
                    Node *b = x->right;

                    y->left->right = y->right;
                    y->right->left = y->left;
                    x->left->right = x->right;
                    x->right->left = x->left;

                    x->left = a;
                    x->right = a->right;
                    x->left->right = x;
                    x->right->left = x;

                    y->right = b;
                    y->left = b->left;
                    y->left->right = y;
                    y->right->left = y;

                    FIB_link(x, y);
                    x = y;
                }
                else
                {
                    FIB_link(y, x);
                }
                A[d] = NULL;
                d++;
            }
            w = x->right;
            A[d] = x;
        }
        min = NULL;
        for (int i = 0; i < A.size(); i++)
        {
            if (A[i] != NULL)
            {
                if (min == NULL)
                {
                    min = A[i];
                }
                else
                {
                    if (A[i]->key < min->key)
                    {
                        min = A[i];
                    }
                }
            }
        }
    }
    void FIB_link(Node *y, Node *x)
    {
        y->right->left = y->left;
        y->left->right = y->right;
        if (x->child == NULL)
        {
            x->child = y;
            y->left = y;
            y->right = y;
        }
        else
        {
            x->child->right->left = y;
            y->right = x->child->right;
            x->child->right = y;
            y->left = x->child;
        }
        y->father = x;
        x->degree++;
        y->mark = false;
    }
    void FIB_decrease_key(Node *x, int k)
    {
        if (x->key < k)
        {
            cout << " error " << endl;
        }
        x->key = k;
        Node *y = x->father;
        if (y != NULL && x->key < y->key)
        {
            cut(x, y);
            cascading_cut(y);
        }
        if (x->key < min->key)
        {
            min = x;
        }
    }
    void cut(Node *x, Node *y)
    {
        if (y->degree == 1)
        {
            y->child = NULL;
        }
        else
        {
            y->child = x->right;
            x->left->right = x->right;
            x->right->left = x->left;
        }
        x->left = min;
        x->right = min->right;
        x->left->right = x;
        x->right->left = x;
        y->degree--;
        x->father = NULL;
        x->mark = false;
    }
    void cascading_cut(Node *y)
    {
        Node *z = y->father;
        if (z != NULL)
        {
            if (y->mark == false)
            {
                y->mark = true;
            }
            else
            {
                cut(y, z);
                cascading_cut(z);
            }
        }
    }
    void FBI_delecte(Node *x)
    {
        FIB_decrease_key(x, -100000);
        FBI_extract_min();
    }
};

int main()
{
    FIB_Heap *heap = new FIB_Heap();
    heap->FIB_insert(3);
    heap->FIB_insert(7);
    heap->FIB_insert(1);
    heap->FIB_insert(2);
    heap->FIB_insert(10);
    heap->FIB_insert(4);
    heap->FIB_insert(5);
    heap->FIB_insert(18);
    heap->FIB_insert(20);
    heap->FIB_insert(14);
    heap->FIB_insert(17);
    heap->FIB_insert(0);
    heap->FIB_insert(16);
    heap->FIB_insert(21);
    heap->consolidate();
    // heap->FBI_extract_min();
    heap->FBI_delecte(heap->get_min()->child->right->child);
    heap->FBI_delecte(heap->get_min()->child->right->child);
    return 0;
}
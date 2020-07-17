// 顺序统计树

#include <string>
#include <iostream>
using namespace std;

template <class T>
class Node
{
private:
    T main_data;
    int size = 1;
    Node<T> *left = NULL;
    Node<T> *right = NULL;
    Node<T> *father = NULL;
    string color = "R";
    T nil_data;

public:
    Node<T>(T data, T nil) : main_data(data), nil_data(nil) {}
    T get_data()
    {
        return main_data;
    }
    void set_data(T data)
    {
        main_data = data;
    }
    int get_size()
    {
        return size;
    }
    void set_size(int si)
    {
        size = si;
    }
    Node<T> *get_left()
    {
        return left;
    }
    void set_left(Node<T> *le)
    {
        left = le;
    }
    Node<T> *get_right()
    {
        return right;
    }
    void set_right(Node<T> *ri)
    {
        right = ri;
    }
    Node<T> *get_father()
    {
        return father;
    }
    void set_farher(Node<T> *fa)
    {
        father = fa;
    }
    string get_color()
    {
        return color;
    }
    void set_color(string co)
    {
        color = co;
    }
    Node<T> *minimun()
    {
        if (left->get_data() != nil_data)
        {
            Node<T> *temp = left;
            while (temp->get_left()->get_data() != nil_data)
            {
                temp = temp->get_left();
            }
            return temp;
        }
        else
        {
            return this;
        }
    }
    Node<T> *maximum()
    {
        if (right->get_data() != nil_data)
        {
            Node<T> *temp = right;
            while (temp->get_right()->get_data() != nil_data)
            {
                temp = temp->get_right();
            }
            return temp;
        }
        else
        {
            return this;
        }
    }
    Node<T> *predecessor()
    {
        if (left->get_data() != nil_data)
        {
            return left->maximum();
        }
        Node<T> *temp = this;
        while (temp->get_father()->get_data() != nil_data)
        {
            if (temp->get_father()->get_right() == temp)
            {
                return temp->get_father();
            }
            else
            {
                temp = temp->get_father();
            }
        }
        return NULL;
    }
    Node<T> *successor()
    {
        if (right->get_data() != nil_data)
        {
            return right->minimun();
        }
        Node<T> *temp = this;
        while (temp->get_father()->get_data() != nil_data)
        {
            if (temp->get_father()->get_left() == temp)
            {
                return temp->get_father();
            }
            else
            {
                temp = temp->get_father();
            }
        }
        return NULL;
    }
};

template <class T>
class Tree
{
private:
    Node<T> *root;
    int num = 0;
    Node<T> *NIL;

public:
    Tree<T>(T nil_data, Node<T> *ro = NULL) : root(ro)
    {
        NIL = new Node<T>(nil_data, nil_data);
        NIL->set_color("B");
        NIL->set_size(0);
    }
    ~Tree<T>()
    {
        this->post_order_traversal_destructuring(root);
        root = NULL;
        delete NIL;
    }
    void post_order_traversal_destructuring(Node<T> *temp)
    {
        if (temp->get_left() != NIL)
        {
            this->post_order_traversal_destructuring(temp->get_left());
        }
        if (temp->get_right() != NIL)
        {
            this->post_order_traversal_destructuring(temp->get_right());
        }
        cout << "   " << temp->get_data() << endl;
        delete temp;
        temp = NULL;
    }
    int &get_num()
    {
        return num;
    }
    Node<T> *get_root()
    {
        return root;
    }
    void set_root(Node<T> *ro)
    {
        root = ro;
        root->set_farher(NIL);
    }
    bool search(T data, Node<T> *ro)
    {
        if (ro == NIL)
        {
            return false;
        }
        Node<T> *temp1 = ro;
        if (ro->get_data() == data)
        {
            return true;
        }
        else
        {
            if (this->search(data, temp1->get_left()) ||
                this->search(data, temp1->get_right()))
                return true;
            else
            {
                return false;
            }
        }
    }
    void insert(T data)
    {
        Node<T> *new_pode = new Node<T>(data, NIL->get_data());
        new_pode->set_left(NIL);
        new_pode->set_right(NIL);
        if (root == NULL)
        {
            this->set_root(new_pode);
            root->set_color("B");
            num++;
            RB_insert_fixup(new_pode);
            return;
        }
        Node<T> *temp = root;
        while (temp != NIL)
        {
            temp->set_size(temp->get_size() + 1);
            if (data < temp->get_data())
            {
                new_pode->set_farher(temp);
                temp = temp->get_left();
            }
            else
            {
                new_pode->set_farher(temp);
                temp = temp->get_right();
            }
        }
        if (data < new_pode->get_father()->get_data())
        {
            new_pode->get_father()->set_left(new_pode);
        }
        else
        {
            new_pode->get_father()->set_right(new_pode);
        }
        num++;
        RB_insert_fixup(new_pode);
    }
    void RB_insert_fixup(Node<T> *z)
    {
        while (z->get_father()->get_color() == "R")
        {
            if (z->get_father() == z->get_father()->get_father()->get_left())
            {
                Node<T> *y = z->get_father()->get_father()->get_right();
                if (y->get_color() == "R")
                {
                    y->set_color("B");
                    z->get_father()->set_color("B");
                    z->get_father()->get_father()->set_color("R");
                    z = z->get_father()->get_father();
                }
                else
                {
                    if (z->get_father()->get_right() == z)
                    {
                        z = z->get_father();
                        this->left_rotate(z);
                    }
                    z->get_father()->set_color("B");
                    z->get_father()->get_father()->set_color("R");
                    this->right_rotate(z->get_father()->get_father());
                }
            }
            else
            {
                Node<T> *y = z->get_father()->get_father()->get_left();
                if (y->get_color() == "R")
                {
                    z->get_father()->set_color("B");
                    y->set_color("B");
                    z->get_father()->get_father()->set_color("R");
                    z = z->get_father()->get_father();
                }
                else
                {
                    if (z->get_father()->get_left() == z)
                    {
                        z = z->get_father();
                        this->right_rotate(z);
                    }
                    z->get_father()->set_color("B");
                    z->get_father()->get_father()->set_color("R");
                    this->left_rotate(z->get_father()->get_father());
                }
            }
            root->set_color("B");
        }
    }
    void transplant(Node<T> *Old, Node<T> *New)
    {
        if (Old->get_father() == NIL)
        {
            this->set_root(NIL);
        }
        else if (Old->get_father()->get_left() == Old)
        {
            Old->get_father()->set_left(New);
        }
        else
        {
            Old->get_father()->set_right(New);
        }
        New->set_farher(Old->get_father());
    }
    Node<T> *delete_search(T data, Node<T> *ro)
    {
        if (ro == NULL)
        {
            return NULL;
        }
        Node<T> *temp1 = ro;
        if (ro->get_data() == data)
        {
            return ro;
        }
        else
        {
            Node<T> *x;
            x = this->delete_search(data, temp1->get_left());
            if (x != NIL)
            {
                return x;
            }
            else
            {
                x = this->delete_search(data, temp1->get_right());
                return x;
            }
        }
    }
    void RB_delete(T data)
    {
        Node<T> *z = delete_search(data, root);
        Node<T> *y = z;
        string y_originall_color = y->get_color();
        Node<T> *x;
        if (z->get_left() == NIL)
        {
            x = z->get_right();
            transplant(z, x);
            RB_delete_size_fix(x, root);
        }
        else if (z->get_right() == NIL)
        {
            x = z->get_left();
            transplant(z, x);
            RB_delete_size_fix(x, root);
        }
        else
        {
            y = z->get_right()->minimun();
            y_originall_color = y->get_color();
            x = y->get_right();
            if (z->get_right() == y)
            {
                x->set_farher(y);
            }
            else
            {
                transplant(y, x);
                y->set_right(z->get_right());
                y->get_right()->set_farher(y);
            }
            transplant(z, y);
            y->set_left(z->get_left());
            y->get_left()->set_farher(y);
            y->set_color(z->get_color());
            y->set_size(z->get_size());
            RB_delete_size_fix(x, root);
        }
        if (y_originall_color == "B")
        {
            RB_delete_fixup(x);
        }
    }
    void RB_delete_fixup(Node<T> *x)
    {
        while (x != root && x->get_color() == "B")
        {
            if (x == x->get_father()->get_left())
            {
                Node<T> *w = x->get_father()->get_right();
                if (w->get_color() == "R")
                {
                    x->get_father()->set_color("R");
                    w->set_color("B");
                    left_rotate(x->get_father());
                    w = x->get_father()->get_right();
                }
                if (w->get_left()->get_color() == "B" && w->get_right()->get_color() == "B")
                {
                    w->set_color("R");
                    x = x->get_father();
                }
                else
                {
                    if (w->get_right()->get_color() == "B")
                    {
                        w->set_color("R");
                        w->get_left()->set_color("B");
                        right_rotate(w);
                        w = x->get_father()->get_right();
                    }
                    x->get_father()->set_color("B");
                    w->set_color("R");
                    w->get_right()->set_color("B");
                    left_rotate(x->get_father());
                    x = root;
                }
            }
            else
            {
                Node<T> *w = x->get_father()->get_left();
                if (w->get_color() == "R")
                {
                    x->get_father()->set_color("R");
                    w->set_color("B");
                    right_rotate(x->get_father());
                    w = x->get_father()->get_left();
                }
                if (w->get_right()->get_color() == "B" && w->get_left()->get_color() == "B")
                {
                    w->set_color("R");
                    x = x->get_father();
                }
                else
                {
                    if (w->get_left()->get_color() == "B")
                    {
                        w->set_color("R");
                        w->get_right()->set_color("B");
                        left_rotate(w);
                        w = x->get_father()->get_left();
                    }
                    x->get_father()->set_color("B");
                    w->set_color("R");
                    w->get_left()->set_color("B");
                    right_rotate(x->get_father());
                    x = root;
                }
            }
        }
        x->set_color("B");
    }
    void RB_delete_size_fix(Node<T> *start, Node<T> *end)
    {
        Node<T> *temp = start;
        do
        {
            temp = temp->get_father();
            temp->set_size(temp->get_size() - 1);
        } while (temp != end);
    }
    void left_rotate(Node<T> *x)
    {
        Node<T> *y = x->get_right();
        y->set_size(x->get_size());
        x->set_size(x->get_left()->get_size() + y->get_left()->get_size() + 1);
        x->set_right(y->get_left());
        if (y->get_left() != NIL && y->get_left() != NULL)
        {
            y->get_left()->set_farher(x);
        }
        y->set_farher(x->get_father());
        if (x->get_father() == NIL)
        {
            this->set_root(y);
        }
        else if (x == x->get_father()->get_left())
        {
            x->get_father()->set_left(y);
        }
        else
        {
            x->get_father()->set_right(y);
        }
        y->set_left(x);
        x->set_farher(y);
    }
    void right_rotate(Node<T> *x)
    {
        Node<T> *y = x->get_left();
        y->set_size(x->get_size());
        x->set_size(x->get_right()->get_size() + y->get_right()->get_size() + 1);
        x->set_left(y->get_right());
        if (y->get_right() != NIL && y->get_right() != NULL)
        {
            y->get_right()->set_farher(x);
        }
        y->set_farher(x->get_father());
        if (x->get_father() == NIL)
        {
            this->set_root(y);
        }
        else if (x->get_father()->get_left() == x)
        {
            x->get_father()->set_left(y);
        }
        else
        {
            x->get_father()->set_right(y);
        }
        y->set_right(x);
        x->set_farher(y);
    }
    Node<T> *os_select(Node<T> *start, int i)
    {
        int r = start->get_left()->get_size() + 1;
        if (r == i)
        {
            return start;
        }
        else
        {
            if (i < r)
            {
                return os_select(start->get_left(), i);
            }
            else
            {
                return os_select(start->get_right(), i - r);
            }
        }
    }
    int os_rank(Node<T> *x)
    {
        int r = x->get_left()->get_size() + 1;
        Node<T> *temp = x;
        while (temp != root)
        {
            if (temp = temp->get_father()->get_right())
            {
                r = r + temp->get_father()->get_left()->get_size() + 1;
            }
            temp = temp->get_father();
        }
        return r;
    }
};

int main()
{
    Tree<int> *tree = new Tree<int>(-100);
    tree->insert(1);
    tree->insert(2);
    tree->insert(13);
    tree->insert(4);
    tree->insert(5);
    tree->insert(10);
    tree->insert(7);
    tree->insert(0);
    cout << tree->os_select(tree->get_root(), 7)->get_data() << endl;
    cout << tree->os_rank(tree->os_select(tree->get_root(), 7)) << endl;
    //tree->RB_delete(5);
    //tree->RB_delete(7);
    cout << "   xxx x  " << endl;
    delete tree;

    return 0;
}
//二叉树的基本功能的实现

#include <iostream>
using namespace std;

template <class T>
class Node
{
private:
    T main_data;
    Node<T> *left = NULL;
    Node<T> *right = NULL;
    Node<T> *father = NULL;

public:
    Node<T>(T data) : main_data(data) {}
    T get_data()
    {
        return main_data;
    }
    void set_data(T data)
    {
        main_data = data;
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
    Node<T> *minimun()
    {
        if (left != NULL)
        {
            Node<T> *temp = left;
            while (temp->get_left() != NULL)
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
        if (right != NULL)
        {
            Node<T> *temp = right;
            while (temp->get_right() != NULL)
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
        if (left != NULL)
        {
            return left->maximum();
        }
        Node<T> *temp = this;
        while (temp->get_father() != NULL)
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
        if (right != NULL)
        {
            return right->minimun();
        }
        Node<T> *temp = this;
        while (temp->get_father() != NULL)
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

public:
    Tree<T>(Node<T> *ro = NULL) : root(ro) {}
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
    }
    bool search(T data, Node<T> *ro)
    {
        if (ro == NULL)
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
            this->search(data, temp1->get_left());
            this->search(data, temp1->get_right());
        }
    }

    void insert(T data)
    {
        Node<T> *new_pode = new Node<T>(data);
        if (root == NULL)
        {
            root = new_pode;
            return;
        }
        Node<T> *temp = root;
        while (temp != NULL)
        {
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
    }
    void transplant(Node<T> *Old, Node<T> *New)
    {
        if (Old->get_father() == NULL)
        {
            root = New;
        }
        else if (Old->get_father()->get_left() == Old)
        {
            Old->get_father()->set_left(New);
        }
        else
        {
            Old->get_father()->set_right(New);
        }
        if (New != NULL)
        {
            New->set_farher(Old->get_father());
        }
    }

    void delete_(T data, Node<T> *ro)
    {
        if (ro == NULL)
        {
            return;
        }
        Node<T> *temp1 = ro;
        if (ro->get_data() == data)
        {
            if (ro->get_left() == NULL)
            {
                this->transplant(ro, ro->get_right());
            }
            else if (ro->get_right() == NULL)
            {
                this->transplant(ro, ro->get_left());
            }
            else
            {
                Node<T> *temp = ro->get_right()->minimun();
                if (temp != ro->get_right())
                {
                    this->transplant(temp, temp->get_right());
                    temp->set_right(ro->get_right());
                    temp->get_right()->set_farher(temp);
                }
                this->transplant(ro, temp);
                temp->set_left(ro->get_left());
                temp->get_left()->set_farher(temp);
            }
        }
        else
        {
            this->search(data, temp1->get_left());
            this->search(data, temp1->get_right());
        }
    }
};

int main()
{
    Tree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(7);
    tree.insert(4);
    tree.insert(3);
    tree.insert(6);
    cout << tree.get_root()->successor()->get_data() << endl;
    cout << tree.get_root()->predecessor()->get_data() << endl;
    cout << tree.search(0, tree.get_root()) << endl;
    return 0;
}
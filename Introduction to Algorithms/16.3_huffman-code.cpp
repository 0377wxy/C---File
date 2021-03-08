// 赫夫曼编码

#include <iostream>
#include <vector>

#include <algorithm>
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
    bool operator<(Node<T> &x)
    {
        return this->get_data() < x.get_data();
    }
    bool operator>(Node<T> &x)
    {
        return this->get_data() > x.get_data();
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

void huffman_code()
{
    vector<Node<int>> Q;
    Q.push_back(Node<int>(5));
    Q.push_back(Node<int>(9));
    Q.push_back(Node<int>(12));
    Q.push_back(Node<int>(13));
    Q.push_back(Node<int>(16));
    Q.push_back(Node<int>(45));
    while (Q.size() > 1)
    {
        Node<int> temp(0);
        vector<Node<int>>::iterator x = min_element(Q.begin(), Q.end());
        temp.set_left(&(*x));
        Q.erase(x);
        vector<Node<int>>::iterator y = min_element(Q.begin(), Q.end());
        temp.set_right(&(*y));
        Q.erase(y);
        temp.set_data(temp.get_left()->get_data() + temp.get_right()->get_data());
        Q.push_back(temp);
    }
    cout << "           x          " << endl;
}
int main()
{
    huffman_code();
    return 0;
}
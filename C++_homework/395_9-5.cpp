#include <iostream>
#include <cassert>
using namespace std;

//类模板的定义
template <class T>
class Node
{
private:
    Node<T> *next; //指向后继结点的指针
public:
    T data;                                 //数据域
    Node(const T &data, Node<T> *next = 0); //构造函数
    void insertAfter(Node<T> *p);           //在本结点之后插入一个同类结点p
    Node<T> *deleteAfter();                 //删除本结点的后继结点，并返回其地址
    Node<T> *nextNode();                    //获取后继结点的地址
    const Node<T> *nextNode() const;        //获取后继结点的地址
};
//类的实现部分
//构造函数，初始化数据和指针成员
template <class T>
Node<T>::Node(const T &data, Node<T> *next /* = 0 */) : data(data), next(next) {}

//返回后继结点的指针
template <class T>
Node<T> *Node<T>::nextNode()
{
    return next;
}

//返回后继结点的指针
template <class T>
const Node<T> *Node<T>::nextNode() const
{
    return next;
}
//在当前结点之后插入一个结点p
template <class T>
void Node<T>::insertAfter(Node<T> *p)
{
    p->next = next; //p结点指针域指向当前结点的后继结点
    next = p;       //当前结点的指针域指向p
}
//删除当前结点的后继结点，并返回其地址
template <class T>
Node<T> *Node<T>::deleteAfter()
{
    Node<T> *tempPtr = next; //将欲删除的结点地址存储到tempPtr中
    if (next == 0)           //如果当前结点没有后继结点，则返回空指针
        return 0;
    next = tempPtr->next; //使当前结点的指针域指向tempPtr的后继结点
    return tempPtr;       //返回被删除的结点的地址
}

int main()
{
    Node<int> *p = new Node<int>(0);
    Node<int> *q = new Node<int>(6);
    Node<int> *x, *y;
    for (int i = 0; i < 5; i++)
    {
        x = new Node<int>(i + 1);
        y = new Node<int>(10 - i);
        p->insertAfter(x);
        q->insertAfter(y);
    }

    cout << "-----------" << endl;
    while (q->nextNode())
    {
        x = q;
        q = q->nextNode();
        p->insertAfter(x);
    }
    p->insertAfter(q);
    while (p->nextNode())
    {
        cout << p->data << endl;
        p = p->nextNode();
    }
    cout << p->data << endl;
    return 0;
}

/*
输出结果：
0
10
9
8
7
6
6
5
4
3
2
1
*/
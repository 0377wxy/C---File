#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class TT>
class Node
{
private:
    TT data;
    Node<TT> *next = NULL;

public:
    Node(TT initdate)
    {
        data = initdate;
    }
    TT getDate()
    {
        return data;
    }
    Node<TT> *getNext()
    {
        return next;
    }
    void setDate(TT newdata)
    {
        data = newdata;
    }
    void setNext(Node<TT> *newnext)
    {
        next = newnext;
    }
};

template <class T1>
class UnorderList
{
private:
    Node<T1> *head = NULL;
    static int num;

public:
    void add(T1 item);
    int size() const;
    bool search(T1 item);
    void remove(T1 item);
    void show() const;
};

template <class T1>
int UnorderList<T1>::num = 0;

template <class T1>
void UnorderList<T1>::add(T1 item)
{
    Node<T1> *temp;
    Node<T1> *previous = NULL;
    Node<T1> *current = head;
    temp = new Node<T1>(item);
    bool stop = false;
    while (current != NULL && !stop)
    {
        if (current->getDate() > item)
        {
            stop = true;
        }
        else
        {
            previous = current;
            current = current->getNext();
        }
    }
    if (previous == NULL)
    {
        temp->setNext(head);
        head = temp;
    }
    else
    {
        temp->setNext(current);
        previous->setNext(temp);
    }
    num++;
}

template <class T1>
int UnorderList<T1>::size() const
{
    return num;
}

template <class T1>
void UnorderList<T1>::remove(T1 item)
{
    Node<T1> *current = head;
    Node<T1> *previous = NULL;
    bool found = false;
    while (!found && current != NULL)
    {
        if (current->getDate() == item)
            found = true;
        else
        {
            previous = current;
            current = current->getNext();
        }
    }
    if (found)
    {
        if (previous == NULL)
            head = current->getNext();
        else
            previous->setNext(current->getNext());
        delete current;
    }
    else
    {
        cout << "  bland    " << endl;
    }
}
template <class T1>
bool UnorderList<T1>::search(T1 item)
{
    Node<T1> *current = head;
    bool stop = false;
    bool found = false;
    while (current != NULL && !stop && !found)
    {
        if (current->getDate() == item)
        {
            found = true;
        }
        else if (current->getDate() > item)
        {
            stop = true;
        }
        else
        {
            current = current->getNext();
        }
    }
    return found;
}

template <class T1>
void UnorderList<T1>::show() const
{
    Node<T1> *current = head;
    while (current != NULL)
    {
        cout << current->getDate() << endl;
        current = current->getNext();
    }
}

int main()
{
    UnorderList<double> x1;
    x1.add(12);
    x1.add(0.1);
    x1.add(7.6);
    x1.add(20.4);
    cout << x1.size() << endl;
    x1.show();
    x1.remove(7.6);
    x1.show();
    return 0;
}
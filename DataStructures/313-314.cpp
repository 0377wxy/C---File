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
};

template <class T1>
int UnorderList<T1>::num = 0;

template <class T1>
void UnorderList<T1>::add(T1 item)
{
    Node<T1> *temp;
    temp = new Node<T1>(item);
    temp->setNext(head);
    head = temp;
    num++;
}

template <class T1>
int UnorderList<T1>::size() const
{
    return num;
}

template <class T1>
bool UnorderList<T1>::search(T1 item)
{
    Node<T1> *current = head;
    bool found = false;
    while (current != NULL && !found)
    {
        if (current->getDate() == item)
            found = true;
        else
            current = current->getNext();
    }
    return found;
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

int main()
{
    UnorderList<int> x1;
    x1.add(12);
    x1.add(22);
    cout << "size   " << x1.size() << endl;
    cout << " find   " << x1.search(12) << endl;
    x1.remove(12);
    cout << "find2   " << x1.search(12) << endl;
    x1.remove(12);
    cout << "size   " << x1.size() << endl;
    return 0;
}
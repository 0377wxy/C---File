#include <iostream>
#include <limits.h>
using namespace std;

class Node
{
    int key;
    Node *prev;
    Node *next;
    Node(int k)
    {
        key = k;
        prev = NULL;
        next = NULL;
    }
};

class List
{
    int num;
    Node *head;
    Node *tail;
    List()
    {
        num = 0;
        head = new Node(INT_MIN);
        tail = head;
    }
    ~List()
    {
        Node *temp1 = head;
        Node *temp2 = head;
        while (temp1)
        {
        }
    }
};

void x

    int
    main()
{
    return 0;
}
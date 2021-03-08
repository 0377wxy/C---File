#include <iostream>
#include <limits.h>
using namespace std;

class Node
{
public:
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
public:
    int num;
    int p_n; //1为正，-1为负；
    Node *head;
    Node *tail;
    List()
    {
        num = 0;
        p_n = 1;
        head = NULL;
        tail = NULL;
    }
    ~List()
    {
        Node *temp1 = head;
        Node *temp2 = head->next;
        while (temp1)
        {
            temp2 = temp1->next;
            delete temp1;
            temp1 = temp2;
        }
    }
    void insert_b(int k)
    {
        Node *temp = new Node(k);
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
        num++;
    }
    void insert_f(int k)
    {
        Node *temp = new Node(k);
        if (head == NULL)
        {
            head = temp;
            return;
        }
        temp->next = head;
        head->prev = temp;
        head = temp;
        num++;
    }
    void delect_f()
    {
        Node *temp = head->next;
        delete head;
        head = temp;
        num--;
    }
    void formalize()
    {
        Node *temp;
        while (/* condition */)
        {
            /* code */
        }
    }
    void input_BN()
    {
        int temp;
        temp = cin.get();
        while (1)
        {
            if (temp == '-' || temp >= '0' && temp <= '9')
            {
                break;
            }
            temp = cin.get();
        }
        if (temp == '-')
        {
            p_n = -1;
            temp = cin.get();
        }
        head = new Node(temp - '0');
        tail = head;
        while (1)
        {
            temp = cin.get();
            if (temp < '0' || temp > '9')
            {
                break;
            }
            insert_b(temp - '0');
        }
    }
    void print_BN()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->key;
            temp = temp->next;
        }
        cout << endl;
    }
};

List *add_BN(List *li1, List *li2)
{
    Node *temp1 = li1->tail;
    Node *temp2 = li2->tail;
    List *result = new List();
    int f = 0, s = 0;
    while (temp1 && temp2)
    {
        s = temp1->key + temp2->key + f;
        f = s / 10;
        s = s % 10;
        result->insert_f(s);
        temp1 = temp1->prev;
        temp2 = temp2->prev;
    }
    while (temp1)
    {
        result->insert_f(temp1->key + f);
        if (f == 1)
        {
            f = 0;
        }
        temp1 = temp1->prev;
    }
    while (temp2)
    {
        result->insert_f(temp2->key + f);
        if (f == 1)
        {
            f = 0;
        }
        temp2 = temp2->prev;
    }
    if (f == 1)
    {
        result->insert_f(f);
    }
    return result;
}

List *sub_BN(List *li1, List *li2)
{
    Node *temp1 = li1->tail;
    Node *temp2 = li2->tail;
    List *result = new List();
    int f = 0, s = 0;
    while (temp2)
    {
        s = temp1->key - temp2->key - f;
        if (s < 0)
        {
            f = 1;
            s += 10;
        }
        result->insert_f(s);
        temp1 = temp1->prev;
        temp2 = temp2->prev;
    }
    while (temp1)
    {
        result->insert_f(temp1->key - f);
        if (f == 1)
        {
            f = 0;
        }
        temp1 = temp1->prev;
    }
    result->formalize();
    return result;
}

int main()
{
    int n;
    cout << "次数" << endl;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        List *li1 = new List();
        List *li2 = new List();
        li1->input_BN();
        li2->input_BN();
        List *li3 = add_BN(li1, li2);
        cout << "结果： " << endl;
        li3->print_BN();
        delete li1;
        delete li2;
        delete li3;
        cout << "---------------------" << endl;
    }

    return 0;
}
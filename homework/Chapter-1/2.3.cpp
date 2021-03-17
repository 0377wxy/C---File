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
    // 在后面插入一个节点
    void insert_b(int k)
    {
        Node *temp = new Node(k);
        if (tail == NULL)
        {
            tail = temp;
            head = tail;
        }
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
        num++;
    }
    // 在前面插入一个节点
    void insert_f(int k)
    {
        Node *temp = new Node(k);
        if (head == NULL)
        {
            head = temp;
            tail = head;
            return;
        }
        temp->next = head;
        head->prev = temp;
        head = temp;
        num++;
    }
    // 删除前面的一个节点
    void delect_f()
    {
        Node *temp = head->next;
        delete head;
        head = temp;
        num--;
    }
    // 清楚前面的0，修改0时的符号
    void formalize()
    {
        Node *temp1 = head;
        while (temp1 != tail && temp1->key == 0)
        {
            head = head->next;
            delete temp1;
            temp1 = head;
        }
        if (head->key == 0)
        {
            p_n = 1;
        }
    }
    // 读入大数
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
    // 输出大数，无回车
    void print_()
    {
        if (p_n < 0)
        {
            cout << "-";
        }
        Node *temp = head;
        while (temp)
        {
            cout << temp->key;
            temp = temp->next;
        }
    }
    // 输出大数，有回车
    void print_BN()
    {
        print_();
        cout << endl;
    }
};

// 无符号加法
List *add_UBN(List *li1, List *li2)
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

// 无符号减法
List *sub_UBN(List *li1, List *li2)
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
        else
        {
            f = 0;
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

// 返回简单比较结果，第一位符号，第二位无符号数
int *compare_BN(List *li1, List *li2)
{
    int *result = new int[2];
    if (li1->p_n == li2->p_n)
    {
        result[0] = 0;
    }
    else if (li1->p_n > li2->p_n)
    {
        result[0] = 1;
    }
    else
    {
        result[0] = -1;
    }

    if (li1->num > li2->num || li1->num == li2->num && li1->head->key > li2->head->key)
    {
        result[1] = 1;
    }
    else if (li1->num < li2->num || li1->num == li2->num && li1->head->key < li2->head->key)
    {
        result[1] = -1;
    }
    else
    {
        Node *temp1 = li1->head;
        Node *temp2 = li2->head;
        result[1] = 0;
        while (temp1)
        {
            if (temp1->key > temp2->key)
            {
                result[1] = 1;
                break;
            }
            else if (temp1->key < temp2->key)
            {
                result[1] = -1;
                break;
            }
            else
            {
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
        }
    }
    return result;
}

// 有符号加法
List *add_BN(List *li1, List *li2)
{
    int *com = compare_BN(li1, li2);
    List *li3;
    if (com[0] == 0)
    {
        li3 = add_UBN(li1, li2);
        li3->p_n = li1->p_n;
    }
    else
    {
        if (com[1] > 0)
        {
            li3 = sub_UBN(li1, li2);
            li3->p_n = li1->p_n;
        }
        else
        {
            li3 = sub_UBN(li2, li1);
            li3->p_n = li2->p_n;
        }
    }
    delete com;
    li3->formalize();
    return li3;
}

// 有符号减法
List *sub_BN(List *li1, List *li2)
{
    int *com = compare_BN(li1, li2);
    List *li3;
    if (com[0] != 0)
    {
        li3 = add_UBN(li1, li2);
        li3->p_n = li1->p_n;
    }
    else
    {
        if (com[1] > 0)
        {
            li3 = sub_UBN(li1, li2);
            li3->p_n = li1->p_n;
        }
        else
        {
            li3 = sub_UBN(li2, li1);
            li3->p_n = -(li2->p_n);
        }
    }
    li3->formalize();
    delete com;
    return li3;
}

// 返回比较结果
void print_com(List *li1, List *li2)
{
    int *com = compare_BN(li1, li2);
    if (com[0] > 0 ||
        com[0] == 0 && com[1] > 0 && li1->p_n > 0 ||
        com[0] == 0 && com[1] < 0 && li1->p_n < 0)
    {
        li1->print_();
        cout << " > ";
        li2->print_();
        cout << endl;
    }
    else if (com[0] < 0 ||
             com[0] == 0 && com[1] < 0 && li1->p_n > 0 ||
             com[0] == 0 && com[1] > 0 && li1->p_n < 0)
    {
        li1->print_();
        cout << " < ";
        li2->print_();
        cout << endl;
    }
    else
    {
        li1->print_();
        cout << " = ";
        li2->print_();
        cout << endl;
    }
    delete com;
}

List *mul_BN(List *li1, List *li2)
{
    List *temp_p;
    if (li1->num < li2->num)
    {
        temp_p = li1;
        li1 = li2;
        li2 = temp_p;
    }
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
        List *li4 = sub_BN(li1, li2);
        cout << "加结果：  ";
        li3->print_BN();
        cout << "减结果：  ";
        li4->print_BN();
        print_com(li1, li2);
        delete li1;
        delete li2;
        delete li3;
        delete li4;
        cout << "---------------------" << endl;
    }
    return 0;
}

/*

*/
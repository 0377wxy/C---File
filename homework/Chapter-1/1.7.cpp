#include <iostream>
#include <vector>
using namespace std;

//节点类
class Node
{
public:
    int key;
    Node *next;
    Node(int k)
    {
        key = k;
        next = NULL;
    }
};

//链表类
class List
{
public:
    Node *head;
    Node *tail;
    int num;
    List()
    {
        head = NULL;
        tail = NULL;
        num = 0;
    }
};

//新建链表
List *initialize_list(int *seq, int num)
{
    List *li = new List();
    li->head = new Node(seq[0]);
    li->tail = li->head;
    li->num++;
    if (num > 1)
    {
        for (int i = 1; i < num; i++)
        {
            li->tail->next = new Node(seq[i]);
            li->tail = li->tail->next;
            li->num++;
        }
    }
    li->tail->next = li->head;
    return li;
}

//出列过程
void dequeue_process(List *li, int *seq, int password, int num)
{
    Node *temp1 = li->tail;
    Node *temp2 = temp1->next;
    int pass = 0;
    while (li->num)
    {
        pass++;
        if (pass == password)
        {
            temp1->next = temp1->next->next;
            seq[num - li->num] = temp2->key;
            delete (temp2);
            li->num--;
            temp2 = temp1->next;
            pass = 0;
            continue;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    delete li;
}

//输出结果
void print_result(int *seq, int num)
{
    cout << "    ----结果-----" << endl;
    for (int i = 0; i < num; i++)
    {
        cout << seq[i] << " ";
    }
    cout << endl;
    cout << "    -------------" << endl;
}

int main()
{
    cout << "请输入游戏人数：" << endl;
    int num;
    cin >> num;
    if (num <= 0)
        return 0;

    int *sequence = new int[num];
    for (int i = 0; i < num; i++)
    {
        sequence[i] = i + 1;
    }
    cout << "请输入密码(终止符结束)：" << endl;
    vector<int> passwords;
    int temp;
    while (cin >> temp)
    {
        if (temp <= 0)
        {
            delete sequence;
            return 0;
        }
        passwords.push_back(temp);
    }
    List *li = NULL;
    for (int i = 0; i < passwords.size(); i++)
    {
        li = initialize_list(sequence, num);
        dequeue_process(li, sequence, passwords[i], num);
    }
    print_result(sequence, num);
    delete sequence;

    return 0;
}
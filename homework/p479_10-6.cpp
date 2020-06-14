#include <iostream>
#include <list>
using namespace std;

template <class T>
void exchange(list<T> &l1, typename list<T>::iterator p1, list<T> &l2, typename list<T>::iterator p2)
{
    typename list<T>::iterator p3 = p1;
    typename list<T>::iterator p4 = p2;
    while (p1 != l1.end() && p2 != l2.end())
    {
        T temp = *p1;
        p1 = l1.erase(p1);
        l1.insert(p1, *p2);
        p2 = l2.erase(p2);
        l2.insert(p2, temp);
    }
    while (p1 != l1.end() && p2 == l2.end())
    {
        l2.insert(p2, *p1);
        p1 = l1.erase(p1);
    }
    while (p1 == l1.end() && p2 != l2.end())
    {
        l1.insert(p1, *p2);
        p2 = l2.erase(p2);
    }
}

int main()
{
    list<int> x1, x2;
    int a[] = {1, 2, 3, 4};
    int b[] = {5, 6, 7, 8, 9, 10};
    x1.assign(a, a + 4);
    x2.assign(b, b + 6);
    exchange(x1, (x1.begin())++, x2, (x2.begin()));
    for (list<int>::iterator b1 = x1.begin(); b1 != x1.end(); b1++)
    {
        cout << *b1 << ' ';
    }
    cout << endl;
    for (list<int>::iterator b2 = x2.begin(); b2 != x2.end(); b2++)
    {
        cout << *b2 << ' ';
    }
    cout << endl;

    list<int> x3, x4;
    int c[] = {1, 2, 3, 4, 11, 12};
    int d[] = {5, 6, 7, 8};
    x3.assign(c, c + 6);
    x4.assign(d, d + 4);
    exchange(x3, (x3.begin())++, x4, (x4.begin()));
    for (list<int>::iterator b1 = x3.begin(); b1 != x3.end(); b1++)
    {
        cout << *b1 << ' ';
    }
    cout << endl;
    for (list<int>::iterator b2 = x4.begin(); b2 != x4.end(); b2++)
    {
        cout << *b2 << ' ';
    }
    cout << endl;
    return 0;
}

/*
运行结果：
5 6 7 8 9 10
1 2 3 4
5 6 7 8
1 2 3 4 11 12
*/
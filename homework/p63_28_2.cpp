#include <iostream>
using namespace std;
int main()
{
    cout << "Menu: A(dd) D(elete) S(ort) Q(uit), Select one:" << endl;
    int flag = 1;
    char ch;
    while (flag)
    {
        cin >> ch;
        switch (ch)
        {
        case 'A':
            cout << "数据已经增加" << endl;
            break;
        case 'D':
            cout << "数据已经删除" << endl;
            break;
        case 'S':
            cout << "数据已经排序" << endl;
            break;
        case 'Q':
            flag = 0;
            break;
        }
    }
    return 0;
}
#include <iostream>
using namespace std;
int main()
{
    cout << "Menu: A(dd) D(elete) S(ort) Q(uit), Select one:" << endl;
    char ch;
    while (1)
    {
        cin >> ch;
        if (ch == 'A')
        {
            cout << "数据已经增加" << endl;
            continue;
        }
        if (ch == 'D')
        {
            cout << "数据已经删除" << endl;
            continue;
        }
        if (ch == 'S')
        {
            cout << "数据已经排序" << endl;
            continue;
        }
        if (ch == 'Q')
            break;
    }
    return 0;
}

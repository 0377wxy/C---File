// 静态表顺序查找算法  监视哨在高下标

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string goal;
    cout << "被查对象： " << endl;
    cin >> goal;
    char goals[30];

    // 原程序顺序表第一位为空
    for (int i = 0; i < goal.size(); i++)
    {
        goals[i + 1] = goal[i];
    }
    char x;

    cout << "要查找的对象： " << endl;
    cin >> x;

    // 高位放置哨兵
    goals[0] = goals[goal.size()];
    goals[goal.size()] = x;

    int i = 0;
    for (; i <= goal.size(); i++)
    {
        if (goals[i] == x)
        {
            break;
        }
    }
    if (i == goal.size())
    {
        cout << "未找到" << endl;
    }
    else
    {
        cout << "位置为： " << i << endl;
    }
}
// 求最大公约数 欧几里得算法

#include <vector>
#include <iostream>
using namespace std;

int eucld(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return eucld(b, a / b);
    }
}

int main()
{
    cout << eucld(30, 12);
    return 0;
}

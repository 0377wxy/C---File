#include <iostream>
using namespace std;
void fnl()
{
    static int x = 0;
    x++;
    cout << x << endl;
}
int main()
{
    for (int i = 0; i < 10; i++)
    {
        fnl();
    }
    return 0;
}
/*
运行结果：
1
2
3
4
5
6
7
8
9
10
*/
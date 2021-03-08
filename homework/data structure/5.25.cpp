// 5.25

#include <iostream>
using namespace std;

int main()
{
    int a1[2][3] = {
        0, 1, 1,
        1, 1, 0};
    int a2[2][3] = {
        1, 0, 1,
        0, 1, 0};
    int b1[4] = {1, 2, 3, 4};
    int b2[3] = {1, -2, 3};
    int a3[2][3] = {0};
    int b3[sizeof(a1) / sizeof(int) + sizeof(a2) / sizeof(int)] = {0};
    int f1 = 0,
        f2 = 0,
        f3 = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a1[i][j] != 0)
            {

                b3[f3] = b1[f1];
                f1++;
            }
            if (a2[i][j] != 0)
            {
                b3[f3] += b2[f2];
                f2++;
            }
            if (b3[f3] != 0)
            {
                a3[i][j] = 1;
                f3++;
            }
        }
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << a3[i][j] << " ";
        }
        cout << endl;
    }
    for (int j = 0; j < sizeof(a1) / sizeof(int) + sizeof(a2) / sizeof(int); j++)
    {
        if (b3[j] == 0)
        {
            break;
        }
        else
        {
            cout << b3[j] << " ";
        }
    }
    return 0;
}

/*
运行结果：
1 1 0
1 1 0
1 1 3 7

时间复杂度：
m*n  (矩阵行列数)
*/
// 5.23

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int x[4][4] = {
        0, 1, 4, 0,
        1, 0, 0, 9,
        3, 0, 0, 0,
        0, 3, 4, 0};
    int s[15][2] = {0}; //二元组顺序表
    int c[5] = {0};     //行起始向量
    int f = 0;
    for (int i = 0; i < 4; i++)
    {
        c[i] = f;
        for (int j = 0; j < 4; j++)
        {
            if (x[i][j] != 0)
            {
                s[f][0] = j;
                s[f][1] = x[i][j];
                f++;
            }
        }
    }
    for (int i = 0; i < 15; i++)
    {
        if (s[i][1] == 0)
        {
            break;
        }
        else
        {
            cout << s[i][0] << " " << s[i][1] << endl;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        cout << c[i] << "  ";
    }
    return 0;
}

/*
运行结果：
1 1
2 4
0 1
3 9
0 3
1 3
2 4
0  2  4  5  0


优点：
所需空间更小
缺点：
查询某个数的位置时比三元组顺序表难
*/
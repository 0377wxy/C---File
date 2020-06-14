#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

bool cmp(int a, int b)
{
    return a > b;
}
int main()
{
    int matrix[6][6] = {0}, mark[6][6] = {0};
    int num_sqrt, num;
    //求行列
    cin >> num;
    int sequence[10];
    int row = num, column = 1;
    num_sqrt = floor(sqrt(num));
    for (int i = num_sqrt; i > 0; i--)
    {
        int temp1 = num % i;
        if (temp1 == 0 && num / i - i < row - column)
        {
            row = num / i;
            column = i;
        }
    }
    //读取数据并排序
    for (int i = 0; i < num; i++)
    {
        cin >> sequence[i];
    }
    sort(sequence, sequence + num, cmp);
    //螺旋放入数据
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= column; j++)
        {
            mark[i][j] = 1;
        }
    }
    int i = 1, j = 1, mode = 0;
    for (int k = 0; k < num; k++)
    {
        matrix[i][j] = sequence[k];
        mark[i][j] = 0;
        switch (mode)
        {
        case 0:
            if (mark[i][j + 1] == 0 && mark[i + 1][j] == 0)
                mode = 2;
            if (mark[i][j + 1] == 0)
                mode = 1;
            break;
        case 1:
            if (mark[i + 1][j] == 0 && mark[i][j - 1] == 0)
                mode = 3;
            if (mark[i + 1][j] == 0)
                mode = 2;
            break;
        case 2:
            if (mark[i][j - 1] == 0 && mark[i - 1][j] == 0)
                mode = 0;
            if (mark[i][j - 1] == 0)
                mode = 3;
            break;
        case 3:
            if (mark[i - 1][j] == 0 && mark[i][j + 1] == 0)
                mode = 1;
            if (mark[i - 1][j] == 0)
                mode = 0;
            break;
        }
        switch (mode)
        {
        case 0:
            j++;
            break;
        case 1:
            i++;
            break;
        case 2:
            j--;
            break;
        case 3:
            i--;
            break;
        }
    }
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= column; j++)
        {
            if (j == column)
                cout << matrix[i][j];
            else
                cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
// 10.24 2-路插入排序

#include <iostream>
using namespace std;

int main()
{
    int ar[8] = {16, 23, 10, 78, 14, 36, 30, 90};
    int d[8] = {0};
    int frist = 0, final = 0;

    cout << "d数组排序过程： " << endl;

    d[0] = ar[0];
    for (int i = 0; i < 8; i++)
    {
        cout << d[i] << " ";
    }
    cout << endl;

    for (int i = 1; i < 8; i++)
    {
        if (ar[i] < d[0])
        {
            frist = (frist + 8 - 1) % 8;
            for (int j = frist; j < 8; j++)
            {
                if (d[(j + 1) % 8] < ar[i])
                {
                    d[j] = d[j + 1];
                }
                else
                {
                    d[j] = ar[i];
                    break;
                }
            }
        }
        else
        {
            final += 1;
            for (int j = final; j > 0; j--)
            {
                if (d[j - 1] > ar[i])
                {
                    d[j] = d[j - 1];
                }
                else
                {
                    d[j] = ar[i];
                    break;
                }
            }
        }

        for (int i = 0; i < 8; i++)
        {
            cout << d[i] << " ";
        }
        cout << endl;
    }
    cout << "排序结果： " << endl;
    for (int i = frist; i != final; i++)
    {
        if (i == 8)
        {
            i -= 8;
        }
        cout << d[i] << " ";
    }
    return 0;
}
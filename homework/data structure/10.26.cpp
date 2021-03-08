// 10.26 对起泡算法的改进

#include <iostream>
using namespace std;

int main()
{
    int ar[8] = {16, 23, 10, 78, 14, 40, 70, 90};
    int f = 7;
    while (1)
    {
        if (f <= 0)
        {
            break;
        }
        int x = 0;
        for (int j = 0; j < f; j++)
        {
            if (ar[j] > ar[j + 1])
            {
                int temp = ar[j];
                ar[j] = ar[j + 1];
                ar[j + 1] = temp;
                x = j;
            }
        }
        f = x;
        for (int i = 0; i < 8; i++)
        {
            cout << ar[i] << " ";
        }
        cout << "   f = " << f << endl;
    }
    return 0;
}
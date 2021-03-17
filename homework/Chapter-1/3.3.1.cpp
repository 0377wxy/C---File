#include <iostream>
using namespace std;

void swap_pos(int *data, int a, int b)
{
    int temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

void per(int *data, int k, int m)
{
    int i, j;
    if (k == m)
    {
        for (i = 0; i <= m; i++)
        {
            cout << data[i];
        }
        cout << endl;
    }
    else
    {
        for (j = k; j <= m; j++)
        {
            swap_pos(data, j, k);
            per(data, k + 1, m);
            swap_pos(data, j, k);
        }
    }
}

int main()
{
    int n;
    cin >> n;
    int *data = new int[n];
    for (int i = 0; i < n; i++)
    {
        data[i] = i + 1;
    }
    per(data, 0, n - 1);
    return 0;
}

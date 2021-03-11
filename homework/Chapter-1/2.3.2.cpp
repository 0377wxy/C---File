#include <iostream>
using namespace std;

int use[100], da[100], res[100];

void backtrack(int a, int n)
{
    if (a == n)
    {
        for (int i = 0; i < n; i++)
        {
            cout << res[i];
        }
        cout << endl;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (use[i] == 0)
            {
                use[i] = 1;
                res[a] = da[i];
                backtrack(a + 1, n);
                use[i] = 0;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        use[i] = 0;
        da[i] = i + 1;
        res[i] = 0;
    }
    backtrack(0, n);
}
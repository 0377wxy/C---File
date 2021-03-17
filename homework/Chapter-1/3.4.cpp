#include <iostream>
#include <string>
using namespace std;

int use[100], da[100], res[100];
string name[100];
int x;

void backtrack(int a, int b, int n, int m)
{
    if (a == m)
    {
        for (int i = 0; i < m; i++)
        {
            cout << name[res[i]] << " ";
        }
        x++;
        cout << endl;
    }
    else if (a < m && b > n - 1)
    {
        return;
    }

    else
    {
        for (int i = b; i < n; i++)
        {
            if (use[i] == 0)
            {
                use[i] = 1;
                res[a] = da[i];
                backtrack(a + 1, i + 1, n, m);
                use[i] = 0;
            }
        }
    }
}

int main()
{
    int n, m;
    x = 0;
    cout << "总人数：";
    cin >> n;
    cout << "所需人数：";
    cin >> m;
    cout << "输入名字： " << endl;
    for (int i = 1; i <= n; i++)
    {
        cin >> name[i];
    }
    cout << "结果：" << endl;
    for (int i = 0; i < n; i++)
    {
        use[i] = 0;
        da[i] = i + 1;
        res[i] = 0;
    }
    backtrack(0, 0, n, m);
    cout << "共 " << x << " 种结果" << endl;
    return 0;
}
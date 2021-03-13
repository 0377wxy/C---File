#include <iostream>
using namespace std;
int dir[4][2] = {0, 1,
                 0, -1,
                 1, 0,
                 -1, 0};

void dfs(int con[][15], int use[][15], int a, int b)
{
    use[a][b] = 1;
    int x, y;
    for (int i = 0; i < 4; i++)
    {
        x = a + dir[i][0];
        y = b + dir[i][1];

        if (use[x][y] == 0 && con[a][b] == con[x][y])
        {
            dfs(con, use, x, y);
        }
    }
}

int main()
{
    int m, n;
    cout << " 行列 ：" << endl;
    cin >> m >> n;
    int con[15][15];
    int use[15][15] = {0};
    int res = 0;
    for (int i = 0; i <= n + 1; i++)
    {
        use[0][i] = 1;
        use[m + 1][i] = 1;
    }
    for (int j = 0; j <= m + 1; j++)
    {
        use[j][0] = 1;
        use[j][n + 1] = 1;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> con[i][j];
        }
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (use[i][j] == 0)
            {
                dfs(con, use, i, j);
                res++;
            }
        }
    }
    cout << res << endl;
    return 0;
};
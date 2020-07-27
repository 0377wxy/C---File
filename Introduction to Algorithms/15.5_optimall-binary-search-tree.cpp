//最优二叉搜索树

#include <iostream>
#include <vector>
using namespace std;

void optimal_BST(vector<double> p, vector<double> q)
{
    int n = p.size();
    p.insert(p.begin(), 0.0);
    vector<vector<double>> e(p.size() + 1, vector<double>(q.size() + 1, 10000));
    vector<vector<double>> w(p.size() + 1, vector<double>(q.size() + 1, -1));
    vector<vector<int>> root(p.size(), vector<int>(q.size(), -1));
    for (int i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }
    for (int l = 1; l <= n; l++) // 长度
    {
        for (int i = 1; i <= n - l + 1; i++) // 起点
        {
            int j = i + l - 1;
            w[i][j] = w[i][j - 1] + p[i] + q[i];
            for (int r = i; r <= j; r++)
            {
                double temp = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (e[i][j] > temp)
                {
                    e[i][j] = temp;
                    root[i][j] = r;
                }
            }
        }
    }
    cout << e[1][n] << endl;
}

int main()
{
    vector<double> p = {0.15, 0.10, 0.05, 0.10, 0.20};
    vector<double> q = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    optimal_BST(p, q);
    return 0;
}
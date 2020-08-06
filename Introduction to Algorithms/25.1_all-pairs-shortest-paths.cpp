// 所有节点对的最短路径算法

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<vector<int>> extend_shortest_paths(vector<vector<int>> &L, vector<vector<int>> &W)
{
    int n = L.size();
    vector<vector<int>> Lx(n, vector<int>(n, 111111));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                Lx[i][j] = min(Lx[i][j], L[i][k] + W[k][j]);
            }
        }
    }
    return Lx;
}

void slow_all_pairs_shortest_paths(vector<vector<int>> W)
{
    int n = W.size();
    vector<vector<int>> Lx(W);
    int m = 1;
    while (m < n - 1)
    {
        Lx = extend_shortest_paths(Lx, Lx);
        m = m * 2;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << Lx[i][j] << "    ";
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> W;
    W.push_back(vector<int>{0, 3, 8, 111111, -4});
    W.push_back(vector<int>{111111, 0, 111111, 1, 7});
    W.push_back(vector<int>{111111, 4, 0, 111111, 111111});
    W.push_back(vector<int>{2, 111111, -5, 0, 111111});
    W.push_back(vector<int>{111111, 111111, 111111, 6, 0});
    slow_all_pairs_shortest_paths(W);
    return 0;
}
// 所有节点对的最短路径算法-Floyd_Warshall算法
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

void floyd_warshall(vector<vector<int>> &W)
{
    int n = W.size();
    vector<vector<int>> D;
    D = W;
    vector<vector<int>> F(n, vector<int>(n, 111111));
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    F[i][j] = -1;
                }
                else
                {
                    F[i][j] = i;
                }
            }
        }
    }
    for (int k = 0; k < n; k++)
    {
        vector<vector<int>> Dx(n, vector<int>(n, 111111));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    Dx[i][j] = D[i][k] + D[k][j];
                    F[i][j] = F[k][j];
                }
                else
                {
                    Dx[i][j] = D[i][j];
                }
            }
        }
        D = Dx;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << D[i][j] << "    ";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << F[i][j] << "    ";
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
    floyd_warshall(W);
    return 0;
}
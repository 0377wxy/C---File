// 矩阵链乘法问题

#include <iostream>
#include <vector>
using namespace std;

void matrix_chain_order(vector<int> p, vector<vector<int>> &m, vector<vector<int>> &s)
{
    for (int i = 0; i < m.size(); i++)
    {
        m[i][i] = 0;
    }

    int n = p.size() - 1;
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            for (int k = i; k <= j - 1; k++)
            {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void print_optimal_parens(vector<vector<int>> s, int i, int j)
{
    if (i == j)
    {
        cout << "A" << i;
    }
    else
    {
        cout << " ( ";
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        cout << " ) ";
    }
}

int main()
{
    vector<int> p{30, 35, 15, 5, 10, 20, 25};
    vector<vector<int>> m(p.size(), vector<int>(p.size(), 1000000));
    vector<vector<int>> s(p.size(), vector<int>(p.size(), 0));
    matrix_chain_order(p, m, s);
    for (int i = 0; i < p.size(); i++)
    {
        for (int j = 0; j < p.size(); j++)
        {
            cout << m[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "-------------------------" << endl;
    for (int i = 0; i < p.size(); i++)
    {
        for (int j = 0; j < p.size(); j++)
        {
            cout << s[i][j] << "  ";
        }
        cout << endl;
    }
    print_optimal_parens(s, 1, p.size() - 1);
    return 0;
}
// 求解线性方程组

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

vector<int> LUP_decomposition(vector<vector<double>> &A)
{
    int n = A.size();
    vector<int> P;
    for (int i = 0; i < n; i++)
    {
        P.push_back(i);
    }
    for (int k = 0; k < n; k++)
    {
        double temp = 0;
        int kx = k;
        for (int i = k; i < n; i++)
        {
            if (fabs(A[i][k]) > temp)
            {
                temp = fabs(A[i][k]);
                kx = i;
            }
        }
        temp = P[k];
        P[k] = P[kx];
        P[kx] = temp;
        for (int i = 0; i < n; i++)
        {
            temp = A[k][i];
            A[k][i] = A[kx][i];
            A[kx][i] = temp;
        }

        for (int i = k + 1; i < n; i++)
        {
            A[i][k] = A[i][k] / A[k][k];
            for (int j = k + 1; j < n; j++)
            {
                A[i][j] = A[i][j] - A[i][k] * A[k][j];
            }
        }
    }
    return P;
}
void LUP_solve(vector<vector<double>> A, vector<int> P, vector<double> b)
{
    vector<vector<double>> L, U;
    L = A;
    U = A;
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A.size(); j++)
        {
            if (i == j)
            {
                L[i][j] = 1;
                U[i][j] = A[i][j];
            }
            else if (i < j)
            {
                U[i][j] = A[i][j];
                L[i][j] = 0;
            }
            else if (i > j)
            {
                L[i][j] = A[i][j];
                U[i][j] = 0;
            }
        }
    }

    vector<double> x(A.size(), 0);
    vector<double> y(A.size(), 0);
    for (int i = 0; i < A.size(); i++)
    {
        double m = 0;
        for (int j = 0; j < i; j++)
        {
            m += L[i][j] * y[j];
        }
        y[i] = b[P[i]] - m;
    }
    for (int i = A.size() - 1; i >= 0; i--)
    {
        double m = 0;
        for (int j = i + 1; j < A.size(); j++)
        {
            m += U[i][j] * x[j];
        }
        x[i] = (y[i] - m) / U[i][i];
    }

    for (int j = 0; j < A.size(); j++)
    {
        cout << setw(6) << x[j] << "  ";
    }
    cout << endl;
}
void solve_linear_equations(vector<vector<double>> &A, vector<double> b)
{
    vector<int> P = LUP_decomposition(A);
    LUP_solve(A, P, b);
}

int main()
{
    vector<vector<double>> A;
    vector<double> b{3, 7, 8};
    A.push_back(vector<double>{1, 2, 0});
    A.push_back(vector<double>{3, 4, 4});
    A.push_back(vector<double>{5, 6, 3});
    solve_linear_equations(A, b);
    return 0;
}
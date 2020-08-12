// 线性规划 单纯形算法

#include <vector>
#include <iostream>
using namespace std;

void pivot(vector<int> &N, vector<int> &B, vector<vector<double>> &A, vector<double> &b, vector<double> &c, double &v, int l, int e)
{
    vector<vector<double>> Ax(b.size(), vector<double>(b.size(), 0));
    vector<double> bx(b.size(), 0);
    vector<double> cx(b.size(), 0);
    for (vector<int>::iterator i = N.begin(); i != N.end(); i++)
    {
        if (*i == e)
        {
            N.erase(i);
        }
    }
    for (vector<int>::iterator i = B.begin(); i != B.end(); i++)
    {
        if (*i == l)
        {
            N.erase(i);
        }
    }

    bx[e] = b[l] / A[l][e];
    for (int j : N)
    {
        Ax[e][j] = A[l][j] / A[l][e];
    }
    Ax[e][l] = 1 / A[l][e];

    for (int i : B)
    {
        bx[i] = b[i] - A[i][e] * bx[e];
        for (int j : N)
        {
            Ax[i][j] = A[i][j] - A[i][e] * Ax[e][j];
        }
        Ax[i][l] = -A[i][e] * Ax[e][l];
    }

    v = v + c[e] * bx[e];
    for (int j : N)
    {
        cx[j] = c[j] - c[e] * Ax[e][j];
    }
    cx[l] = -c[e] * Ax[e][l];

    N.push_back(l);
    B.push_back(e);
    A = Ax;
    b = bx;
    c = cx;
}

void simplex(vector<vector<double>> &A, vector<double> &b, vector<double> &c, double v)
{
    vector<int> N, B;
    vector<double> constraint(b.size(), 9999999);
    while (1)
    {
        int e = -1;
        for (int i : N)
        {
            if (c[i] > 0)
            {
                e = i;
                break;
            }
        }
        if (e == -1)
        {
            cout << "unbounded" << endl;
            return;
        }
        else
        {
            int l = 0;
            for (int i : B)
            {
                if (A[i][e] > 0)
                {
                    constraint[i] = b[i] / A[i][e];
                    if (constraint[i] < constraint[l])
                    {
                        l = i;
                    }
                }
            }
            if (constraint[l] == 9999999)
            {
                break;
            }
            pivot(N, B, A, b, c, v, l, e);
        }
    }
    vector<double> x(b.size(), 0);
    for (int i : B)
    {
        x[i] = b[i];
    }
    for (int i = 0; i < x.size(); i++)
    {
        cout << x[i] << "  ";
    }
    cout << endl;
}
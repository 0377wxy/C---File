// 最长公共子序列问题

#include <iostream>
#include <string>
#include <vector>
using namespace std;

string show_LCS(string X, string Y)
{
    X.insert(0, ".");
    Y.insert(0, ".");
    vector<vector<int>> c(X.size(), vector<int>(Y.size(), 0));
    vector<vector<char>> s(X.size(), vector<char>(Y.size(), 'O'));
    for (int i = 1; i < X.size(); i++)
    {
        for (int j = 1; j < Y.size(); j++)
        {
            if (X[i] == Y[j])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                s[i][j] = 'Q';
            }
            else if (c[i - 1][j] > c[i][j - 1])
            {
                c[i][j] = c[i - 1][j];
                s[i][j] = 'W';
            }
            else
            {
                c[i][j] = c[i][j - 1];
                s[i][j] = 'A';
            }
        }
    }
    string res;
    int i = X.size() - 1;
    int j = Y.size() - 1;
    while (i != 0 && j != 0)
    {
        if (s[i][j] == 'Q')
        {
            res.insert(0, 1, X[i]);
            i--;
            j--;
        }
        else if (s[i][j] == 'W')
        {
            i--;
        }
        else
        {
            j--;
        }
    }
    return res;
}

int main()
{
    string X = "ABCBDA";
    string Y = "BDCABA";
    string Z = show_LCS(X, Y);
    cout << Z << endl;
    return 0;
}
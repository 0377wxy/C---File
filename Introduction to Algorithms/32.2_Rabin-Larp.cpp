// 字符串匹配 Rabin-Karp算法

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void Rain_Karp_matcher(string T, string P, int d, int q)
{
    int n = T.size();
    int m = P.size();
    int h = int(pow(d, m - 1)) % q;
    int p = 0, t = 0;
    int f = 0;
    for (int i = 0; i < m; i++)
    {
        p = (d * p + P[i]) % q;
        t = (d * t + T[i]) % q;
    }
    for (int s = 0; s < n - m; s++)
    {
        if (p == t)
        {
            for (int i = 0; i < m; i++)
            {
                if (P[i] != T[i + s])
                {
                    f = 1;
                    break;
                }
            }
            if (f == 0)
            {
                cout << s << endl;
            }
            f = 0;
        }
        if (s < n - m)
        {
            t = (d * (t - T[s] * h) + T[s + m]) % q;
        }
        if (t < 0)
        {
            t += q;
        }
    }
}

int main()
{
    string T("1234567890987654321234567890");
    string P("345");
    Rain_Karp_matcher(T, P, 10, 13);
    return 0;
}
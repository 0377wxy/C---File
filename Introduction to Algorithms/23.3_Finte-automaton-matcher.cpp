// 利用有限自动机进行字符串匹配

#include <iostream>
#include <string>
#include <map>
using namespace std;

void Finte_automaton_matcher(string T, string P, string E)
{
    int m = P.size();
    map<string, int> Transform;
    for (int q = 0; q < m; q++)
    {

        for (char a : E)
        {
            int k = min(m, q + 1);
            for (; k > 0; k--)
            {
                //cout << P.substr(0, k) << "  " << P.substr(q - k + 1, k - 1) + string(1, a) << " " << k << endl;
                if (P.substr(0, k) == P.substr(q - k + 1, k - 1) + string(1, a))
                    break;
            }
            Transform.insert(pair<string, int>(string(1, q) + string(1, a), k));
        }
    }
    int n = T.size();
    int q = 0;
    for (int i = 0; i < n; i++)
    {
        q = Transform[string(1, q) + string(1, T[i])];
        if (q == m)
        {
            cout << i - m + 1 << endl;
        }
    }
}

int main()
{
    string T("qwertyuiopqwertyuiop");
    string P("ert");
    string E("poiuytrewq");
    Finte_automaton_matcher(T, P, E);
    return 0;
}
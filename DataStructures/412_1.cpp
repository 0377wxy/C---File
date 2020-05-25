#include <iostream>
#include <vector>
#include <map>
using namespace std;

int ff(map<int, int> &tr, map<map<map<int, int>, int>, int> &te, int weight)
{
    int max_v = 0;
    map<map<int, int>, int> tr2;
    tr2[tr] = weight;
    if (tr.size() == 0)
        return 0;
    else if (te.find(tr2) != te.end())
    {
        return te[tr2];
    }
    else
    {
        for (map<int, int>::iterator x1 = tr.begin(); x1 != tr.end(); x1++)
        {
            if (x1->first <= weight)
            {
                map<int, int> tr1 = tr;
                tr1.erase(x1->first);
                int temp = ff(tr1, te, weight - x1->first) + x1->second;
                if (temp > max_v)
                {
                    max_v = temp;
                }
            }
        }
        te[tr2] = max_v;
        return max_v;
    }
}

int main()
{
    map<int, int> tr;
    tr[2] = 3;
    tr[3] = 4;
    tr[4] = 8;
    tr[5] = 8;
    tr[9] = 10;
    int max_m = 20;
    map<map<map<int, int>, int>, int> te;
    cout << ff(tr, te, max_m) << endl;
    return 0;
}
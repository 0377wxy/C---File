// 活动选择问题

#include <iostream>
#include <vector>
using namespace std;

// 递归方法
void recursice_activity_selector(vector<int> &s, vector<int> &f, int k, vector<int> &res)
{
    int m = k + 1;
    while (m < s.size() && s[m] < f[k])
    {
        m++;
    }
    if (m < s.size())
    {
        res.push_back(m);
        recursice_activity_selector(s, f, m, res);
    }
}

// 迭代方法
void greedy_activity_selector(vector<int> &s, vector<int> &f, vector<int> &res)
{
    res.push_back(1);
    for (int i = 1, k = 1; i < s.size(); i++)
    {
        if (s[i] >= f[k])
        {
            res.push_back(i);
            k = i;
        }
    }
}

int main()
{
    vector<int> s{0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    vector<int> f{0, 4, 5, 6, 7, 9, 10, 11, 12, 14, 16};
    vector<int> res;
    // recursice_activity_selector(s, f, 0, res);
    greedy_activity_selector(s, f, res);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << "  ";
    }
    return 0;
}
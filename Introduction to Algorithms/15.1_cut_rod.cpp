// 动态规划 求解 钢条切割问题

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

// 带备忘录的自顶向下法
int memoized_cut_rod_aux(vector<int> &li, int lenght, vector<int> &value)
{
    if (value[lenght] != -1)
    {
        return value[lenght];
    }
    if (lenght == 0)
    {
        return 0;
    }
    int p = -1;
    for (int i = 1; i <= lenght; i++)
    {
        p = max(p, li[i] + memoized_cut_rod_aux(li, lenght - i, value));
    }
    value[lenght] = p;
    return p;
}
int memoizeo_cut_rod(vector<int> li, int lenght)
{
    vector<int> value(lenght + 1, -1);
    return memoized_cut_rod_aux(li, lenght, value);
}

// 自底向上法
int bottom_up_cut_rod(vector<int> li, int lenght)
{
    vector<int> value(lenght + 1, -1);
    value[0] = 0;
    for (int i = 1; i <= lenght; i++)
    {
        int p = -1;
        for (int j = 1; j <= i; j++)
        {
            p = max(p, li[j] + value[i - j]);
        }
        value[i] = p;
    }
    return value[lenght];
}

int main()
{
    vector<int> li{0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    cout << bottom_up_cut_rod(li, 4) << endl;
    return 0;
}
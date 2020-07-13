//基数排序

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
void counting_sort(vector<int> &vec, vector<int> &pos, int Max)
{
    vector<int> a(Max, 0);
    vector<int> res_pos(vec.size(), 0);
    for (int i = 0; i < vec.size(); i++)
    {
        a[vec[i]]++;
    }
    for (int i = 1; i < Max; i++)
    {
        a[i] = a[i] + a[i - 1];
    }
    for (int i = 0; i < vec.size(); i++)
    {
        res_pos[a[vec[pos[i]]] - 1] = pos[i];
        a[vec[pos[i]]]--;
    }
    pos = res_pos;
}
vector<int> radix_sort(vector<int> vec, int gap, int digit)
{
    vector<int> res_pos;
    for (int i = 0; i < vec.size(); i++)
    {
        res_pos.push_back(i);
    }
    for (int i = 0; i < digit; i = i + gap)
    {
        vector<int> vec_gap;
        for (int j = 0; j < vec.size(); j++)
        {
            vec_gap.push_back(int(vec[j] / pow(10, i)) % int(pow(10, gap)));
        }

        counting_sort(vec_gap, res_pos, pow(10, gap));
    }
    vector<int> res(vec.size(), 0);
    for (int i = 0; i < vec.size(); i++)
    {
        res[i] = vec[res_pos[i]];
    }
    return res;
}

int main()
{
    vector<int> vec{1234, 4321, 2345, 5432, 5678, 4589, 6521};
    vector<int> res = radix_sort(vec, 2, 4);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << ' ';
    }
    return 0;
}
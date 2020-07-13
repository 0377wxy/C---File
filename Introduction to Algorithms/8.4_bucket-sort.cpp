//桶排序

#include <iostream>
#include <list>
#include <vector>
#include <math.h>

using namespace std;

void bucket_sort(vector<double> &vec)
{
    vector<list<double>> vec_buc(vec.size(), list<double>());
    for (int i = 0; i < vec.size(); i++)
    {
        vec_buc[floor(vec.size() * vec[i])].push_back(vec[i]);
    }
    for (int i = 0; i < vec_buc.size(); i++)
    {
        vec_buc[i].sort();
    }
    vector<double> res;
    for (int i = 0; i < vec_buc.size(); i++)
    {
        while (!vec_buc[i].empty())
        {
            res.push_back(vec_buc[i].front());
            vec_buc[i].pop_front();
        }
    }
    vec = res;
}

int main()
{
    vector<double> vec{0.5, 0.7, 0.3, 0.11, 0.98, 0.28, 0.69};
    bucket_sort(vec);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << ' ';
    }
    return 0;
}
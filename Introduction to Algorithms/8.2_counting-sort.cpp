//计数排序

#include <iostream>
#include <vector>
using namespace std;

vector<int> counting_sort(vector<int> vec, int k)
{
    vector<int> a(k, 0);
    vector<int> res(vec.size(), 0);
    for (int i = 0; i < vec.size(); i++)
    {
        a[vec[i]]++;
    }

    for (int i = 1; i < k; i++)
    {
        a[i] = a[i] + a[i - 1];
    }
    for (int i = 0; i < vec.size(); i++)
    {
        res[a[vec[i]] - 1] = vec[i];
        a[vec[i]]--;
    }
    return res;
}

int main()
{
    vector<int> vec{2, 4, 6, 8, 1, 3, 5, 7};
    vector<int> res = counting_sort(vec, 9);

    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << ' ';
    }
    cout << endl;
    return 0;
}
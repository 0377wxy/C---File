//并归排序算法

#include <iostream>
#include <vector>
using namespace std;

void marge(vector<int> &vec, int p, int q, int r)
{
    vector<int> vec1(vec.begin() + p, vec.begin() + q + 1);
    vec1.push_back(41481277);
    vector<int> vec2(vec.begin() + q + 1, vec.begin() + r + 1);
    vec2.push_back(41481277);
    int k = 0, j = 0;
    for (int i = p; i <= r; i++)
    {
        if (vec1[k] < vec2[j] && vec1[k] != 41481277)
        {
            vec[i] = vec1[k];
            k++;
        }
        else if (vec2[j] != 41481277)
        {
            vec[i] = vec2[j];
            j++;
        }
    }
}

void marge_sort(vector<int> &vec, int begin, int end)
{
    if (begin < end - 1)
    {
        int q = (begin + end) / 2;
        marge_sort(vec, begin, q);
        marge_sort(vec, q, end);
        marge(vec, begin, q, end);
    }
}

int main()
{
    vector<int> vec{9, 7, 6, 2, 12, 45, 1};
    marge_sort(vec, 0, vec.size() - 1);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << ' ';
    }
    cout << endl;
    return 0;
}
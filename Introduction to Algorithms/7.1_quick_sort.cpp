//快速排序算法

#include <iostream>
#include <vector>
using namespace std;

int partiion(vector<int> &vec, int left, int right)
{
    int compare = vec[right];
    int l = left, r = left;
    for (; r < right; r++)
    {
        if (vec[r] < compare)
        {
            int temp = vec[l];
            vec[l] = vec[r];
            vec[r] = temp;
            l++;
        }
    }
    int temp = vec[l];
    vec[l] = vec[right];
    vec[right] = temp;

    return l;
}

void quick_sort(vector<int> &vec, int l, int r)
{
    if (l < r)
    {
        int q = partiion(vec, l, r);
        quick_sort(vec, l, q - 1);
        quick_sort(vec, q + 1, r);
    }
}

int main()
{
    vector<int> vec{1, 3, 2, 4, 9, 6, 8, 89};
    quick_sort(vec, 0, vec.size() - 1);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << ' ';
    }
}
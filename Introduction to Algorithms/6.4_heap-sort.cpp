//堆排序算法

#include <iostream>
#include <vector>
using namespace std;

//维护最大堆性质
void max_heapify(vector<int> &vec, int i)
{
    if (2 * i < vec.size() && vec[2 * i] > vec[i] && vec[2 * i] >= vec[2 * i + 1])
    {
        int temp = vec[i];
        vec[i] = vec[2 * i];
        vec[2 * i] = temp;
        max_heapify(vec, 2 * i);
    }
    else if (2 * i + 1 < vec.size() && vec[2 * i + 1] > vec[i] && vec[2 * i + 1] >= vec[2 * i])
    {
        int temp = vec[i];
        vec[i] = vec[2 * i + 1];
        vec[2 * i + 1] = temp;
        max_heapify(vec, 2 * i + 1);
    }
}

//建造堆
void build_max_heap(vector<int> &vec)
{
    for (int i = vec.size() / 2; i > 0; i--)
    {
        max_heapify(vec, i);
        for (int j = 0; j < vec.size(); j++)
        {
            cout << vec[j] << ' ';
        }
        cout << endl;
    }
}

//堆返回排序
vector<int> heap_sort(vector<int> &vec)
{
    vector<int> result;
    for (int i = vec.size() - 1; i > 1; i--)
    {
        build_max_heap(vec);
        result.push_back(vec[1]);
        vec[1] = vec[vec.size() - 1];
        vec.pop_back();
        for (int j = 0; j < vec.size(); j++)
        {
            cout << vec[j] << ' ';
        }
        cout << endl;
    }
    result.push_back(vec.back());
    return result;
}

int main()
{
    vector<int> vec{0, 1, 3, 5, 7, 2, 4, 6, 8};
    vector<int> res = heap_sort(vec);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << ' ';
    }
    return 0;
}
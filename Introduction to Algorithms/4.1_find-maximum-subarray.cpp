//并归求解最大子数问题

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<int> find_crossing_subarray(vector<int> vec, int start, int mid, int end)
{
    int sum = 0;
    vector<int> result{0, mid, mid};
    for (int i = mid; i >= start; i--)
    {
        sum += vec[i];
        if (sum > result[0])
        {
            result[0] = sum;
            result[1] = i;
        }
    }
    sum = result[0];
    for (int i = mid + 1; i <= end; i++)
    {
        sum += vec[i];
        if (sum > result[0])
        {
            result[0] = sum;
            result[2] = i;
        }
    }
    return result;
}

vector<int> find_maximum_subarray(vector<int> vec, int start, int end)
{
    if (end > start)
    {
        int mi = (start + end) / 2;
        vector<int> left = find_maximum_subarray(vec, start, mi);
        vector<int> right = find_maximum_subarray(vec, ceil((start + end) / 2.0), end);
        vector<int> mid = find_crossing_subarray(vec, start, mi, end);
        if (left[0] >= right[0] && left[0] >= mid[0])
        {
            return left;
        }
        else if (right[0] >= left[0] && right[0] >= mid[0])
        {
            return right;
        }
        else
        {
            return mid;
        }
    }
    else
    {
        vector<int> result_1{vec[start], start, end};
        return result_1;
    }
}

int main()
{
    vector<int> vec{-1, +4, -1, -2, +4, -1, +3, -1};
    vector<int> p = find_maximum_subarray(vec, 0, 7);
    cout << p[0] << ' ' << p[1] << ' ' << p[2] << endl;
    return 0;
}
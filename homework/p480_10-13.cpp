#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;

int Pow(int a, int b)
{
    return pow(a, b);
}

int main()
{
    vector<int> vec(10), res(10);
    std::generate(vec.begin(), vec.end(), []() {
        return rand() % 9;
    });
    for (vector<int>::iterator x1 = vec.begin(); x1 != vec.end(); x1++)
    {
        cout << *x1 << ' ';
    }
    cout << endl;
    transform(vec.begin(), vec.end(), res.begin(), bind1st(ptr_fun(Pow), 5));
    for (int a : res)
    {
        cout << a << ' ';
    }
    cout << endl;
    transform(vec.begin(), vec.end(), res.begin(), bind2nd(ptr_fun(Pow), 7));
    for (int a : res)
    {
        cout << a << ' ';
    }
    cout << endl;
    transform(vec.begin(), vec.end(), vec.begin(), res.begin(), ptr_fun(Pow));
    for (int a : res)
    {
        cout << a << ' ';
    }
    return 0;
}

/*
运行结果：
5 8 7 4 8 1 3 0 7 2
3125 390625 78125 625 390625 5 125 1 78125 25
78125 2097152 823543 16384 2097152 1 2187 0 823543 128
3125 16777216 823543 256 16777216 1 27 1 823543 4
*/
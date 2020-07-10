#include <iostream>
#include <cassert>
using namespace std;

template <class T>
int seqSearch(const T list[], int n, const T &key)
{
    for (int i = 0; i < n; i++)
        if (list[i] == key)
            return i;
    return -1;
}

int main()
{
    cout << "请输入查找对象" << endl;
    int n;
    cin >> n;
    int a[20] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    cout << seqSearch(a, 20, n) << endl;
    return 0;
}
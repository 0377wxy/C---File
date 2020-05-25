#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int chan(int value, vector<int> &change, vector<int> &list)
{
    // cout << "  x  " << endl;
    if (list[value] != 0)
    {
        return list[value];
    }
    else if (find(change.begin(), change.end(), value) != change.end())
    {
        list[value] = 1;
        return 1;
    }
    else
    {
        int min = value;
        for (int x1 = 0; x1 < change.size(); x1++)
        {
            if (change[x1] > value)
            {
                continue;
            }
            int temp = chan(value - change[x1], change, list) + 1;
            if (temp < min)
            {
                min = temp;
            }
        }
        list[value] = min;
        return min;
    }
}

int chan2(int num, vector<int> &change, vector<int> &list, vector<int> &coin)
{
    for (int i = 0; i <= num; i++)
    {
        if (find(change.begin(), change.end(), i) != change.end())
        {
            coin[i] = i;
            list[i] = 1;
        }
        else
        {
            int temp = i;
            for (vector<int>::iterator x1 = change.begin(); x1 != change.end(); x1++)
            {
                if (i > *x1 && list[i - *x1] + 1 < temp)
                {
                    temp = list[i - *x1] + 1;
                    coin[i] = *x1;
                }
            }

            list[i] = temp;
        }
    }
    return list[num];
}

int main()
{
    int value = 63;
    int a[] = {1, 5, 20, 50};
    vector<int> change(a, a + 4);
    vector<int> list(value + 1, 0);
    vector<int> coin(value + 1, 0);
    //cout << chan(value, change, list) << endl;
    cout << chan2(value, change, list, coin) << endl;
    for (int x1 = 0; x1 < list.size(); x1++)
    {
        cout << list[x1] << "    ";
    }
    cout << endl;
    while (value > 0)
    {
        cout << coin[value] << "   ";
        value = value - coin[value];
    }
    return 0;
}
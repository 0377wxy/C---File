#include <iostream>
#include <vector>
#include <string>
using namespace std;

string divideBy(int dec, int base)
{
    vector<int> remstack;
    string digits = "0123456789ABCDEFG";
    while (dec > 0)
    {
        int rem = dec % base;
        remstack.push_back(rem);
        dec = dec / base;
    }
    string bin;
    while (!remstack.empty())
    {
        bin = bin + digits[remstack.back()];
        remstack.pop_back();
    }
    return bin;
}

int main()
{
    int x;
    cin >> x;
    for (int i = 2; i <= 16; i++)
    {
        cout << divideBy(x, i) << "    ";
    }

    return 0;
}
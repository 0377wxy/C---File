#include <iostream>
#include <string>
using namespace std;

string toStr(int n, int bace)
{
    string converString = "0123456789ABCDEFG";
    if (n < bace)
    {
        string x1 = "";
        x1.append(1, converString[n]);
        return x1;
    }
    else
    {
        return toStr(n / bace, bace) + converString[n % bace];
    }
}

int main()
{
    cout << toStr(6, 2) << endl;
    return 0;
}
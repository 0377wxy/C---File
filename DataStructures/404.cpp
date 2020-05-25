#include <iostream>
#include <string>
using namespace std;
void hhh(int num, string &Start, string &With, string &End)
{
    if (num == 1)
    {
        cout << 1 << "    form " << Start << "   to   " << End << endl;
    }
    else
    {
        hhh(num - 1, Start, End, With);
        cout << num << "    form " << Start << "   to   " << End << endl;
        hhh(num - 1, With, Start, End);
    }
}

int main()
{
    string x1 = "#1", x2 = "#2", x3 = "#3";
    hhh(3, x1, x2, x3);
    return 0;
}
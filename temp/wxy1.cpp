#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <math.h>
using namespace std;

class A
{
public:
    int *p = NULL;
    A(int a)
    {
        p = new int(a);
    }
    int *&xx()
    {
        return p;
    }
};

int xxxx()
{
    cout << "    xxx x " << endl;
    return 9;
}

int main()
{
    string a = "R";
    cout << (a == "R") << endl;
    return 0;
}
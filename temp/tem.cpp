#include <iostream>
using namespace std;

int main()
{
    int x, y, z = 0;
    for (x = 0, y = 0; (y = 0) && (x < 4); x++)
    {
        cout << z << " " << y << endl;
        z++;
    }
    return 0;
}
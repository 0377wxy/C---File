#include <iostream>
using namespace std;

class XX
{
private:
public:
    int a, b, c;
    XX(int x, int y = 0, int z = 0) : a(x), c(z) {}
    XX(const XX &x)
    {
        a = x.a;
        cout << " 复制构造 " << endl;
    }
    void operator=(const XX &x)
    {
        a = x.a;
        cout << " 赋值运算符 " << endl;
    }
    void as()
    {
        cout << "dddddd" << endl;
        return;
    }
};

int main()
{
    XX c(3);
    int *p = NULL;
    cout << *p << endl;
    return 0;
}
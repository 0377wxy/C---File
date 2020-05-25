
//也可用类编写，但将Derived类的指针强制转换为Base2类型，内存也会重新划分，也会出现问题

#include <iostream>
using namespace std;

class Base1
{
public:
    int x;
    Base1(int a) : x(a) {}
};

class Base2
{
public:
    float y;
    Base2(int b) : y(b) {}
};

class Derived : public Base1, public Base2
{
public:
    Derived(int a, float b) : Base1(a), Base2(b) {}
};

int main()
{
    Derived *pd = new Derived(1, 2.1);
    Base2 *pb = pd;
    cout << pd->y << "  " << pb->y << endl;
    delete pd;
    return 0;
}

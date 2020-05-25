#include <iostream>
using namespace std;

struct Base1
{
    int x;
};
struct Base2
{
    float y;
};
struct Derived : Base1, Base2
{
};

int main()
{
    Derived *pd = new Derived;
    pd->x = 1;
    pd->y = 2.0f;
    void *pv = pd;
    Base2 *pb = static_cast<Base2 *>(pv);
    cout << pd->y << "  " << pb->y << endl;
    delete pb;
    return 0;
}
/*
运行结果：
2  1.4013e-45
结构体指针在强制类型转换时，将指针所指的内存按新的结构体的类型进行了重新划分，所以出现问题
可将22行改为：
Base2 *pb =pd;
24行改为：
delete pd;
可使程序正常
运行结果变为：
2  2
*/
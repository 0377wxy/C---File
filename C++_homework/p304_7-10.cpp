#include <iostream>
using namespace std;

class Object
{
private:
    int weight;

public:
    Object(int a = 0) : weight(a)
    {
        cout << "   Object调用" << endl;
    }
    ~Object()
    {
        cout << "   Object析构" << endl;
    }
    void set_weight(int a)
    {
        weight = a;
    }
    void show_weight()
    {
        cout << "weight  :  " << weight << endl;
    }
};

class Box : public Object
{
private:
    int height, width;

public:
    Box(int a = 0, int b = 0, int c = 0) : Object(a), height(b), width(c)
    {
        cout << "   Box调用" << endl;
    }
    ~Box()
    {
        cout << "   Box析构" << endl;
    }
    void show_Box()
    {
        cout << "height  ：" << height << endl;
        cout << "width   : " << width << endl;
        show_weight();
    }
};

int main()
{
    Object x1(3);
    x1.show_weight();
    cout << "---------------" << endl;
    Box x2(4, 10, 11);
    cout << "---------------" << endl;
    x2.show_Box();
    cout << "---------------" << endl;
    return 0;
}
/*
运行结果：
   Object调用
weight  :  3
---------------
   Object调用
   Box调用
---------------
height  ：10
width   : 11
weight  :  4
---------------
   Box析构
   Object析构
   Object析构
*/
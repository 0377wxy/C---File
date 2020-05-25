#include <iostream>
#include <cmath>
using namespace std;

class Shape
{
private:
    static int num;

public:
    virtual double getArea() = 0;
    virtual double getPerim() = 0;
    static int getNum();
    Shape()
    {
        num++;
    }
};
int Shape::num = 0;
int Shape::getNum()
{
    return num;
}
class Rectangle : public Shape
{
private:
    int we, lo;

public:
    Rectangle(int a, int b) : Shape(), we(a), lo(b) {}
    double getArea()
    {
        return we * lo;
    }
    double getPerim()
    {
        return 2 * (we + lo);
    }
};

class Circle : public Shape
{
private:
    int re;

public:
    Circle(int a) : Shape(), re(a) {}
    double getArea()
    {
        return 3.14 * pow(re, 2);
    }
    double getPerim()
    {
        return 2 * 3.14 * re;
    }
};

int main()
{
    cout << Shape::getNum() << endl;
    Rectangle r1(2, 3);
    cout << "r1" << endl;
    cout << r1.getArea() << "    " << r1.getPerim() << endl;
    Circle c1(4);
    cout << "c1" << endl;
    cout << c1.getArea() << "       " << c1.getPerim() << endl;
    cout << Shape::getNum() << endl;
    return 0;
}

/*
运行结果
0
r1
6    10
c1
50.24       25.12
2
*/
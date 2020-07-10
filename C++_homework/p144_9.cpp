#include <cmath>
#include <iostream>
using namespace std;
class Rectangle
{
private:
    double ax, bx, ay, by;

public:
    Rectangle(double a = 0, double b = 0, double c = 0, double d = 0);
    double area();
};

Rectangle::Rectangle(double a, double b, double c, double d) : ax(a), ay(b), bx(c), by(d) {}
double Rectangle::area()
{
    return fabs((ax - bx) * (ay - by));
}

int main()
{
    Rectangle a1, a2(0, 0, 4, 3), a3(-0.5, -1, 0.5, 1);
    cout << a1.area() << endl;
    cout << a2.area() << endl;
    cout << a3.area() << endl;
}

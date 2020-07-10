#include <iostream>
using namespace std;

class Rectangle
{
private:
    double longth;
    double width;

public:
    Rectangle(double a = 0, double b = 0);
    double area();
};

Rectangle::Rectangle(double a, double b) : longth(a), width(b)
{
}
double Rectangle::area()
{
    return longth * width;
}

int main()
{
    Rectangle a1, a2(2.2, 3.3);
    cout << a1.area() << endl;
    cout << a2.area() << endl;
}
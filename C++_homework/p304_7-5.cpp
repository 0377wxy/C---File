#include <iostream>

using namespace std;

class Shape
{
protected:
    static int shape_num;

public:
    Shape();
    ~Shape()
    {
        cout << "shape  xg" << endl;
    }
};
int Shape::shape_num = 0;
Shape::Shape()
{
    shape_num++;
}
class Rectangle : public Shape
{
protected:
    double length, width;
    static int rec_num;

public:
    Rectangle(double a = 0, double b = 0);
    virtual ~Rectangle()
    {
        cout << "Rectangle   xg" << endl;
    }
    double getArea();
    void shownum();
};
int Rectangle::rec_num = 0;
Rectangle::Rectangle(double a, double b) : length(a), width(b)
{
    rec_num++;
}
double Rectangle::getArea()
{
    return length * width;
}
void Rectangle::shownum()
{
    cout << "---------------------" << endl;
    cout << "   Shape   :" << shape_num << endl;
    cout << "   Rectangle   :" << rec_num << endl;
    cout << "---------------------" << endl;
}

class Circle : public Shape
{
protected:
    double radius;
    static int cir_num;

public:
    Circle(double a = 0);
    double getArea();
    void shownum();
};
Circle::Circle(double a) : radius(a)
{
    cir_num++;
}
int Circle::cir_num = 0;
double Circle::getArea()
{
    return 3.1415 * radius * radius;
}
void Circle::shownum()
{
    cout << "---------------------" << endl;
    cout << "   Shape   :" << shape_num << endl;
    cout << "   Circle   :" << cir_num << endl;
    cout << "---------------------" << endl;
}

class Square : public Rectangle
{
protected:
    static int squ_num;

public:
    Square(double a = 0);
    void shownum();
};
int Square::squ_num = 0;
Square::Square(double a)
{
    length = a;
    width = a;
    squ_num++;
}
void Square::shownum()
{
    cout << "---------------------" << endl;
    cout << "   Shape   :" << shape_num << endl;
    cout << "   Rectangle   :" << rec_num << endl;
    cout << "   Square   :" << squ_num << endl;
    cout << "---------------------" << endl;
}

int main()
{
    Rectangle rec1(4, 2.5);
    cout << "  rec1  :" << rec1.getArea() << endl;
    rec1.shownum();
    Circle cir1(1);
    cout << "  cir1  :" << cir1.getArea() << endl;
    cir1.shownum();
    Square squ1(2.5);
    cout << "  squ1  :" << squ1.getArea() << endl;
    squ1.shownum();
    return 0;
}

/*
运行结果：
  rec1  :10
---------------------
   Shape   :1
   Rectangle   :1
---------------------
  cir1  :3.1415
---------------------
   Shape   :2
   Circle   :1
---------------------
  squ1  :6.25
---------------------
   Shape   :3
   Rectangle   :2
   Square   :1
---------------------
*/
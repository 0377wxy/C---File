//vscode编写，编译器g++

#include <iostream>
#include <cmath>
using namespace std;

class SimpleCircle
{
private:
    double *itsRadius = NULL;
    double const PI;
    static int num;

public:
    SimpleCircle(double radius = 0, double pi = 3.14);
    ~SimpleCircle();
    static int showNum();
    double showRadius() const;
    void setRadius(double radius);
    double showPerimeter() const;
    double showArea() const;
};

SimpleCircle::SimpleCircle(double radius, double pi) : PI(pi)
{
    itsRadius = new double(radius);
    num++;
}
int SimpleCircle::num = 0;
SimpleCircle::~SimpleCircle()
{
    delete itsRadius;
    num--;
    cout << "释放内存" << endl;
}
int SimpleCircle::showNum()
{
    return num;
}
double SimpleCircle::showRadius() const
{
    return *itsRadius;
}
double SimpleCircle::showPerimeter() const
{
    return 2 * PI * (*itsRadius);
}
double SimpleCircle::showArea() const
{
    return PI * pow(*itsRadius, 2);
}
void SimpleCircle::setRadius(double radius)
{
    *itsRadius = radius;
}

int main()
{
    cout << "初始圆的数量 ： " << SimpleCircle::showNum() << endl;
    SimpleCircle r1(1, 3.1415), r2(1);
    cout << "新建两圆后，圆的数量 ：  " << SimpleCircle::showNum() << endl;
    cout << "      r1   "
         << "    r2   " << endl;
    cout << "半径  " << r1.showRadius() << "    " << r2.showRadius() << endl;
    cout << "周长  " << r1.showPerimeter() << "     " << r2.showPerimeter() << endl;
    cout << "面积  " << r1.showArea() << "    " << r2.showArea() << endl;
    cout << endl;
    cout << "改变两圆的半径  " << endl;
    r1.setRadius(2);
    r2.setRadius(1.5);
    cout << "      r1   "
         << "    r2   " << endl;
    cout << "半径  " << r1.showRadius() << "    " << r2.showRadius() << endl;
    cout << "周长  " << r1.showPerimeter() << "     " << r2.showPerimeter() << endl;
    cout << "面积  " << r1.showArea() << "    " << r2.showArea() << endl;

    return 0;
}

/*
运行结果：

初始圆的数量 ： 0
新建两圆后，圆的数量 ：  2
      r1       r2   
半径  1    1
周长  6.283     6.28
面积  3.1415    3.14

改变两圆的半径
      r1       r2
半径  2    1.5
周长  12.566     9.42
面积  12.566    7.065
释放内存
释放内存

*/
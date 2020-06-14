#include <iostream>
#include <cmath>
using namespace std;

class Point
{
private:
    int x, y;
    static int point_num;

public:
    Point();
    Point(int x1, int y1);
    Point(const Point &);
    static int show_point_num();
    int show_x();
    int show_y();
    void change(int x1, int y1);
};
int Point::point_num = 0;
Point::Point()
{
    x = 1;
    y = 1;
    point_num++;
    cout << "调用点构造函数其一" << endl;
}
Point::Point(int x1, int y1) : x(x1), y(y1)
{
    point_num++;
    cout << "调用点构造函数之二" << endl;
}
Point::Point(const Point &i)
{
    x = i.x;
    y = i.y;
    point_num++;
    cout << "调用点构造函数之三" << endl;
}
int Point::show_point_num()
{
    cout << "现在的点个数为 ：  " << point_num << endl;
}
int Point::show_y()
{
    return y;
}
int Point::show_x()
{
    return x;
}
void Point::change(int x1, int y1)
{
    x = x1;
    y = y1;
}

class Line
{
private:
    Point p1, p2;
    double length;
    static int line_num;

public:
    Line(int x1 = 1, int y1 = 1, int x2 = -1, int y2 = -1);
    Line(Point p3, Point p4);
    void show_line();
    void change(Point p3, Point p4);
    void change(int x1, int y1, int x2, int y2);
    void count_length();
    double show_length();
};
int Line::line_num = 0;
Line::Line(int x1, int y1, int x2, int y2)
{
    p1.change(x1, y1);
    p2.change(x2, y2);
    line_num++;
    cout << "调用线构造函数其一" << endl;
    count_length();
}
Line::Line(Point p3, Point p4)
{
    p1 = p3;
    p2 = p4;
    line_num++;
    cout << "调用线构造函数其二" << endl;
    count_length();
}
void Line::show_line()
{
    cout << "point_1  " << p1.show_x() << ',' << p1.show_y() << endl;
    cout << "point_2  " << p2.show_x() << ',' << p2.show_y() << endl;
}
void Line::change(Point p3, Point p4)
{
    p1 = p3;
    p2 = p4;
    count_length();
}
void Line::change(int x1, int y1, int x2, int y2)
{
    p1.change(x1, y1);
    p2.change(x2, y2);
    count_length();
}
void Line::count_length()
{
    length = sqrt(pow(p1.show_x() - p2.show_x(), 2) + pow(p1.show_y() - p2.show_y(), 2));
}
double Line::show_length()
{
    return length;
}

int main()
{
    int a, b;
    cout << "point_1---" << endl;
    cin >> a >> b;
    Point po1(a, b);
    cout << "point_2---" << endl;
    cin >> a >> b;
    Point po2(a, b), po3;
    Line line1(po1, po2);
    line1.show_line();
    cout << line1.show_length() << endl;
    ;
    line1.change(0, 3, 4, 0);
    cout << line1.show_length() << endl;
    return 0;
}
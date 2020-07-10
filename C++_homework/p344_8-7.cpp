#include <iostream>
using namespace std;

class Point
{
private:
    int xx;

public:
    Point(int a = 0) : xx(a) {}
    int show()
    {
        return xx;
    }
    Point &operator++()
    {
        xx++;
        return (*this);
    }
    Point &operator--()
    {
        xx--;
        return (*this);
    }
    Point operator++(int)
    {
        Point a = xx;
        xx++;
        return a;
    }
    Point operator--(int)
    {
        Point a = xx;
        xx--;
        return a;
    }
};

int main()
{
    Point aa(3);
    cout << "      " << aa.show() << endl;
    cout << "aa++    " << (aa++).show() << endl;
    cout << "      " << aa.show() << endl;
    cout << "aa--    " << (aa--).show() << endl;
    cout << "      " << aa.show() << endl;
    cout << "++aa    " << (++aa).show() << endl;
    cout << "      " << aa.show() << endl;
    cout << "--aa    " << (--aa).show() << endl;
    cout << "      " << aa.show() << endl;
    return 0;
}

/*
运行结果
      3
aa++    3
      4
aa--    4
      3
++aa    4
      4
--aa    3
      3
*/
#include <iostream>
using namespace std;

class Counter
{
private:
    int real, image;

public:
    Counter(int a = 0, int b = 0) : real(a), image(b) {}
    Counter &operator+(Counter &a);
    Counter &operator+(int b);
    friend Counter operator+(int a, const Counter &b);
    friend ostream &operator<<(ostream &out, const Counter &a);
};
Counter operator+(int a, const Counter &b)
{
    Counter xx;
    xx.real = b.real + a;
    return xx;
}
Counter &Counter::operator+(Counter &a)
{
    real += a.real;
    image += a.image;
    return (*this);
}
Counter &Counter::operator+(int b)
{
    real += b;
    return (*this);
}
ostream &operator<<(ostream &out, const Counter &a)
{
    out << a.real << '+' << a.image << 'i' << endl;
    return out;
}

int main()
{
    Counter a1(1, 3), a2;
    int a3 = 2;
    cout << a1 + a2;
    cout << a1 + a3;
    cout << a3 + a2;
    return 0;
}

/*
输出结果：
1+3i
3+3i
2+0i
*/
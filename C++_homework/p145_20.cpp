#include <iostream>
#include <iomanip>
using namespace std;
class Complex
{
private:
    double real = 0, image = 0;

public:
    Complex(double a, double b);
    Complex(double a);
    void add(const Complex &x);
    void show();
};

Complex::Complex(double a, double b) : real(a), image(b)
{
}

Complex::Complex(double a) : real(a)
{
}
void Complex::add(const Complex &x)
{
    real += x.real;
    image += x.image;
}
void Complex::show()
{
    cout << real << showpos << image << 'i' << endl;
}

int main()
{
    Complex c1(3, 5);
    Complex c2 = 4.5;
    c1.add(c2);
    c1.show();

    return 0;
}
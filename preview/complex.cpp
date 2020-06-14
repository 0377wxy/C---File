#include <iostream>
using namespace std;
class Complex
{
private:
    int real, image;

public:
    Complex(int a = 1, int b = 1);
    Complex operator+(Complex c);
    friend Complex operator+(int, Complex &);
    friend istream &operator>>(istream &, Complex &);
    friend ostream &operator<<(ostream &, Complex &);
    void show();
};
Complex::Complex(int a, int b) : real(a), image(b) {}
Complex Complex::operator+(Complex c)
{
    Complex temp;
    temp.real = real + c.real;
    temp.image = this->image + c.image;
    return temp;
}
Complex operator+(int a, Complex &c)
{
    Complex temp;
    temp.real = a + c.real;
    temp.image = c.image;
    return temp;
}
void Complex::show()
{
    cout << "---" << real << "--" << image << endl;
}
istream &operator>>(istream &i, Complex &t)
{
    i >> t.real >> t.image;
    return i;
}
ostream &operator<<(ostream &i, Complex &c)
{
    i << c.real << "----" << c.image;
    return i;
}

int main()
{
    Complex x1(3, 5), x2(7, 9), x3, x4;
    cin >> x1;
    x1.show();
    cin >> x2;
    x2.show();
    x3 = 12 + x2;
    cout << x3 << endl;
    x4 = x3 + x2;
    cout << x4 << endl;
    return 0;
}
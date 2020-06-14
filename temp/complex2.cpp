#include <iostream>
#include <fstream>
using namespace  std;

class Complex
{
public:
    Complex(double r = 0, double i = 0):_dReal(r), _dImag(i) {}
    Complex operator+ (const Complex &rhs) const; //成员函数，复数加法
    //友元函数，复数减法
    friend Complex operator- (const Complex &z1, const Complex &z2);
    //友元函数，输出复数
    friend ostream & operator << (ostream &os, const Complex &rhs) ;
private:
    double _dReal;			// 实部
    double _dImag;			// 虚部
};

// 成员函数，复数加法
Complex Complex::operator+(const Complex &rhs) const
{
    Complex z(_dReal+rhs._dReal, _dImag+rhs._dImag);
    return z;	// 返回结果
}

// 友元函数，复数减法
Complex operator-(const Complex &z1, const Complex &z2)
{   // 返回结果:匿名复数对象
    return Complex (z1._dReal-z2._dReal, z1._dImag-z2._dImag);
}

//友元函数，输出复数
ostream & operator << (ostream &os, const Complex &rhs)
{
    if (rhs._dImag < 0) // 虚部为负
        os << rhs._dReal << rhs._dImag << "i" << endl;
    else //虚部非负
        os << rhs._dReal << "+" << rhs._dImag << "i" << endl;
    return os;
}

int main()
{
    Complex z1(2, 3), z2(6, -5), z3;// 定义复数对象
    ofstream  ofs ("\\result.txt"); //定义输出文件流对象ofs

    //后续输出至文件。如ofs替换为cout，则输出至显示器。
    ofs << z1 << z2;     //输出, 等价于operator << (operator << (ofs, z1),z2)
    z3 = z1 + z2;//相"加",  等价于z3 = z1.operator+(z2);
    ofs << z3;           //输出,  等价于operator << (ofs, z3)
    z3 = z1 - z2; //相"减"   等价于z3 = operator- (z1, z2);
    ofs << z3;
}

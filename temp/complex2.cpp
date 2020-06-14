#include <iostream>
#include <fstream>
using namespace  std;

class Complex
{
public:
    Complex(double r = 0, double i = 0):_dReal(r), _dImag(i) {}
    Complex operator+ (const Complex &rhs) const; //��Ա�����������ӷ�
    //��Ԫ��������������
    friend Complex operator- (const Complex &z1, const Complex &z2);
    //��Ԫ�������������
    friend ostream & operator << (ostream &os, const Complex &rhs) ;
private:
    double _dReal;			// ʵ��
    double _dImag;			// �鲿
};

// ��Ա�����������ӷ�
Complex Complex::operator+(const Complex &rhs) const
{
    Complex z(_dReal+rhs._dReal, _dImag+rhs._dImag);
    return z;	// ���ؽ��
}

// ��Ԫ��������������
Complex operator-(const Complex &z1, const Complex &z2)
{   // ���ؽ��:������������
    return Complex (z1._dReal-z2._dReal, z1._dImag-z2._dImag);
}

//��Ԫ�������������
ostream & operator << (ostream &os, const Complex &rhs)
{
    if (rhs._dImag < 0) // �鲿Ϊ��
        os << rhs._dReal << rhs._dImag << "i" << endl;
    else //�鲿�Ǹ�
        os << rhs._dReal << "+" << rhs._dImag << "i" << endl;
    return os;
}

int main()
{
    Complex z1(2, 3), z2(6, -5), z3;// ���帴������
    ofstream  ofs ("\\result.txt"); //��������ļ�������ofs

    //����������ļ�����ofs�滻Ϊcout�����������ʾ����
    ofs << z1 << z2;     //���, �ȼ���operator << (operator << (ofs, z1),z2)
    z3 = z1 + z2;//��"��",  �ȼ���z3 = z1.operator+(z2);
    ofs << z3;           //���,  �ȼ���operator << (ofs, z3)
    z3 = z1 - z2; //��"��"   �ȼ���z3 = operator- (z1, z2);
    ofs << z3;
}

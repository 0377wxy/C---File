#include <iostream>
#include <iomanip>
using namespace std;

int main(void)
{
    /*
    int a;
    double b;
    cout << "请输入" ;
    cin >> a;
    //清空缓存区
    cin.clear();
    cin.sync();
    cin >> b;
    cout << a << b << endl;
    */

    //有效位数
    cout << setprecision(3) << 12.345 << endl;
    //小数位数
    cout << fixed << setprecision(3) << 12.3456 << endl;
    //科学表示法及其小数精度
    cout << scientific << setprecision(3) << 12345.67 << endl;
    //输出宽度,只大不小
    cout << setw(5) << 10 << 20 << endl;
    cout << 10 << setw(5) << 20 << endl;
    //空格填充
    cout << setfill('%') << setw(8) << 10 << 20 << endl;
}
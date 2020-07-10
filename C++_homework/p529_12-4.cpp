#include <iostream>
#include <string>
using namespace std;

class Exception
{
public:
    void show() { cout << "出现问题" << endl; }
};
class OutOfMemory : public Exception
{
private:
    string er;

public:
    OutOfMemory(string aa) : er(aa) {}
    void show_e() { cout << er << endl; }
};
class RangeError : public Exception
{
private:
    string er;

public:
    RangeError(string aa) : er(aa) {}
    void show_e() { cout << er << endl; }
};

int main()
{
    try
    {
        int a[3], n;
        cin >> n;
        if (n > 2)
        {
            throw OutOfMemory("数组内存不足");
        }
        else
        {
            a[n] = 111;
        }
        int m;
        cin >> m;
        if (m > 2)
        {
            throw RangeError("数字不在范围内");
        }
        else
        {
            cout << a[m] << endl;
        }
    }
    catch (OutOfMemory &e)
    {
        e.show();
        e.show_e();
    }
    catch (RangeError &e)
    {
        e.show();
        e.show_e();
    }

    return 0;
}

/*
运行结果 1：
2
4
出现问题
数字不在范围内

运行结果 2：
6
出现问题
数组内存不足

运行结果 3：
2
2
111
*/
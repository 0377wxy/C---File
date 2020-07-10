//vscode编写，编译器g++
#include <iostream>
using namespace std;

int ful()
{
    int *p = new int(5);
    return *p;
}

int *ful2();

int main()
{
    // int a = ful();
    // cout << "the value of a is : " << a;

    int *x = NULL;
    x = ful2();
    cout << " the value of *x is : " << *x;
    delete x;

    return 0;
}

/*
原运行结果： 
the value of a is : 5
问题： p申请的内存没有释放，
函数运行结束后p指针被销毁，p申请的内存无法释放
更改后的运行结果：
the value of *x is : 6
内存得到了释放
*/

//更改函数
int *ful2()
{
    int *p = new int(6);
    return p;
}

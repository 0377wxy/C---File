#include <iostream>
using namespace std;
class Cat
{
private:
    static int num;

public:
    Cat();
    static int numOfCats();
};
Cat::Cat()
{
    num++;
}
int Cat::numOfCats()
{
    return num;
}
int Cat::num = 0;

int main()
{
    cout << Cat::numOfCats() << endl;
    Cat x1, x2;
    cout << Cat::numOfCats() << endl;
    return 0;
}
/* 运行结果：
0
2
*/
#include <iostream>
using namespace std;

class Tree
{
private:
    int ages;

public:
    Tree(int xx = 0);
    void grow(int years);
    int age();
};

Tree::Tree(int xx) : ages(xx) {}
void Tree::grow(int years)
{
    ages += years;
}
int Tree::age()
{
    return ages;
}

int main()
{
    Tree t1, t2(1000);
    t1.grow(200);
    cout << "t1:  " << t1.age() << endl;
    cout << "t2:  " << t2.age() << endl;
}
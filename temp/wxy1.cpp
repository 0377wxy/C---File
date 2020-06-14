#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class student
{
private:
    int age;
    int number;
    char *name;

public:
    student(int ag, int num, char *nm);
    student(const student &st);
    ~student();
    void display();
    student &xx(student a)
    {
        a.age = 1000;
        return a;
    }
};
student::student(int ag, int num, char *nm) : age(ag), number(num), name(nm) {}
student::student(const student &st)
{
    age = st.age;
    number = st.number;
    *name = *(st.name);
}
student::~student()
{
    cout << " 析构 " << endl;
}
void student::display()
{
    cout << " age  " << age << endl;
    cout << " number  " << number << endl;
    cout << " char " << *name << endl;
}

int main()
{
    student x1(2, 122, "wx");
    x1.display();
    student x2(1, 2, "w");
    x2 = x1.xx(x2);
    x2.display();
    return 0;
}
#include <iostream>
#include <fstream>

using namespace std;

class Dog
{
private:
    int age, weight;

public:
    Dog(int ag = 0, int we = 0) : age(ag), weight(we) {}
    int show_age() { return age; }
    int show_weight() { return weight; }
};

int main()
{
    Dog d1(5, 10);
    ofstream op1("tempx2", ios_base::out | ios_base::binary);
    op1.write(reinterpret_cast<char *>(&d1), sizeof(d1));
    cout << d1.show_age() << " " << d1.show_weight() << endl;
    op1.close();
    ifstream op2("tempx2", ios_base::in | ios_base::binary);
    Dog d2;
    op2.read(reinterpret_cast<char *>(&d2), sizeof(d2));
    cout << d2.show_age() << " " << d2.show_weight() << endl;
    op2.close();
    return 0;
}
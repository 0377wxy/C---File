#include <iostream>
#include <cstring>
using namespace std;
class Name
{
private:
    char *ph;
    int size;

public:
    Name(const char *p = "");
    Name(const Name &);
    ~Name();
    Name &operator=(const Name &i);
    friend ostream &operator<<(ostream &, Name &);
};
Name::Name(const char *p)
{
    ph = new char[strlen(p) + 1];
    strcpy(ph, p);
    size = strlen(p);
}
Name::Name(const Name &i)
{
    ph = new char[i.size + 1];
    strcpy(ph, i.ph);
    size = i.size;
}
Name::~Name()
{
    delete[] ph;
    size = 0;
}
Name &Name::operator=(const Name &i)
{
    if (ph == i.ph)
        return *this;
    delete[] ph;
    ph = new char[i.size + 1];
    strcpy(ph, i.ph);
    size = i.size;
    return *this;
}
ostream &operator<<(ostream &i, Name &n)
{
    i << n.ph << "-------" << n.size << endl;
    return i;
}

int main()
{
    Name x1("www"), x2("wanghao"), x3;
    cout << " x1  " << x1;
    cout << " x2  " << x2;
    cout << " x3  " << x3;
    x3 = x1;
    cout << x3;
    return 0;
}
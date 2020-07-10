#include <iostream>
using namespace std;

class Car;

class Boat
{
private:
    double weight = 0;

public:
    friend double getTotalWeight(Boat &a, Car &b);
    Boat(double x) : weight(x) {}
};

class Car
{
private:
    double weight = 0;

public:
    friend double getTotalWeight(Boat &a, Car &b);
    Car(double x) : weight(x) {}
};

double getTotalWeight(Boat &a, Car &b)
{
    return b.weight + a.weight;
}

int main()
{
    Boat x1(12.5);
    Car x2(13.5);
    cout << getTotalWeight(x1, x2) << endl;
}
// 寻找最近点对

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Point
{
public:
    double x, y;
    Point(double a, double b) : x(a), y(b) {}
};

double Divide_and_conquer(vector<Point> X, vector<Point> Y)
{
    if (X.size() > 3)
    {
        double mid_x = X[floor(X.size() / 2)].x;
        int i = 0;
        for (; i < X.size(); i++)
        {
            if (X[i].x == mid_x)
            {
                break;
            }
        }
        vector<Point> XL(X.begin(), X.begin() + i - 1);
        vector<Point> XR(X.begin() + i, X.begin() + X.size() - 1);
        vector<Point> YL, YR;
        for (Point a : Y)
        {
            if (a.x < mid_x)
            {
                YL.push_back(a);
            }
            else
            {
                YR.push_back(a);
            }
        }
        double dis_1 = Divide_and_conquer(XL, YL);
        double dis_2 = Divide_and_conquer(XR, YR);
        double dis = min(dis_1, dis_2);
        for (int i = 0; i < Y.size(); i++)
        {
            if (Y[i].x < mid_x - dis || Y[i].x > mid_x + dis)
            {
                vector<Point>::iterator t = Y.begin() + i;
                Y.erase(t);
            }
        }
        for (int i = 0; i < Y.size(); i++)
        {
            for (int j = i + 1; j < i + 8 && j < Y.size(); j++)
            {
                double temp = sqrt(pow(Y[i].x - Y[j].x, 2) + pow(Y[i].y - Y[j].y, 2));
                if (i != j && dis > temp)
                {
                    dis = temp;
                }
            }
        }
        return dis;
    }
    else
    {
        double dis = 1000000;
        for (int i = 0; i < X.size(); i++)
        {
            for (int j = 0; j < X.size(); j++)
            {
                double temp = sqrt(pow(X[i].x - X[j].x, 2) + pow(X[i].y - X[j].y, 2));
                if (i != j && dis > temp)
                {
                    dis = temp;
                }
            }
        }
        return dis;
    }
}

void Find_the_nearest_point_pair(vector<Point> Q)
{
    vector<Point> X = Q, Y = Q;
    for (int i = 0; i < X.size() - 1; i++)
    {
        for (int j = 0; j < X.size() - 1 - i; j++)
        {
            if (X[j].x > X[j + 1].x)
            {
                Point temp = X[j + 1];
                X[j + 1] = X[j];
                X[j] = temp;
            }
        }
    }
    for (int i = 0; i < Y.size() - 1; i++)
    {
        for (int j = 0; j < Y.size() - 1 - i; j++)
        {
            if (Y[j].y < Y[j + 1].y)
            {
                Point temp = Y[j + 1];
                Y[j + 1] = Y[j];
                Y[j] = temp;
            }
        }
    }
    cout << Divide_and_conquer(X, Y) << endl;
}

int main()
{
    vector<Point> Q;
    Q.push_back(Point(0, 2));
    Q.push_back(Point(0, 6));
    Q.push_back(Point(2, 5));
    Q.push_back(Point(3, 7));
    Q.push_back(Point(4, 2));
    Q.push_back(Point(5, 9));
    Q.push_back(Point(7, 2));
    Q.push_back(Point(7, 4));
    Q.push_back(Point(8, 6));
    Q.push_back(Point(1, -1));
    Q.push_back(Point(2, -5));
    Q.push_back(Point(2, -8));
    Q.push_back(Point(3, -3));
    Q.push_back(Point(4, -1));
    Q.push_back(Point(5, -5));
    Q.push_back(Point(6, -1));
    Q.push_back(Point(6, -6));
    Q.push_back(Point(-2, 1));
    Q.push_back(Point(-3, 4));
    Q.push_back(Point(-3, 8));
    Q.push_back(Point(-4, 2));
    Q.push_back(Point(-5, 6));
    Q.push_back(Point(-6, 1));
    Q.push_back(Point(-6, 4));
    Q.push_back(Point(-1, -2));
    Q.push_back(Point(-1, -5));
    Q.push_back(Point(-3, -4));
    Q.push_back(Point(-4, -1));
    Q.push_back(Point(-4, -8));
    Q.push_back(Point(-5, -4));
    Q.push_back(Point(-7, -2));
    Q.push_back(Point(-7, -6));
    Q.push_back(Point(-8, -4));
    Find_the_nearest_point_pair(Q);
    return 0;
}
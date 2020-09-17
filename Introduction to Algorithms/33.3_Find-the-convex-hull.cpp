// 寻找凸包

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

//Graham扫描法

bool cmp(Point a, Point b, Point p0)
{
    double c = (a.x - p0.x) * (b.y - p0.y) - (a.y - p0.y) * (b.x - p0.x);
    if (c < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int partiion(vector<Point> &vec, int left, int right, Point p0)
{
    Point compare = vec[right];
    int l = left, r = left;
    for (; r < right; r++)
    {
        if (cmp(vec[r], compare, p0))
        {
            Point temp = vec[l];
            vec[l] = vec[r];
            vec[r] = temp;
            l++;
        }
    }
    Point temp = vec[l];
    vec[l] = vec[right];
    vec[right] = temp;

    return l;
}

void quick_sort(vector<Point> &vec, int l, int r, Point p0)
{
    if (l < r)
    {
        int q = partiion(vec, l, r, p0);
        quick_sort(vec, l, q - 1, p0);
        quick_sort(vec, q + 1, r, p0);
    }
}

void Graham_scan(vector<Point> Q)
{
    Point p0(999999, 999999);
    // 选择p0
    for (Point p : Q)
    {
        if (p.y < p0.y || p.y == p0.y && p.x < p0.x)
        {
            p0 = p;
        }
    }
    for (int i = 0; i < Q.size(); i++)
    {
        if (Q[i].x == p0.x && Q[i].y == p0.y)
        {
            swap(Q[i], Q[0]);
            break;
        }
    }
    // 排序
    quick_sort(Q, 1, Q.size() - 1, p0);
    // 去除同角度近点
    for (int i = 1; i < Q.size() - 1; i++)
    {
        while ((Q[i].x - p0.x) * (Q[i + 1].y - p0.y) - (Q[i].y - p0.y) * (Q[i + 1].x - p0.x) == 0 && i + 1 < Q.size())
        {
            if (pow(Q[i].x - p0.x, 2) + pow(Q[i].y - p0.y, 2) <
                pow(Q[i + 1].x - p0.x, 2) + pow(Q[i + 1].y - p0.y, 2))
            {
                vector<Point>::iterator i1 = Q.begin() + i;
                Q.erase(i1);
            }
            else
            {
                vector<Point>::iterator i1 = Q.begin() + i + 1;
                Q.erase(i1);
            }
        }
    }
    if (Q.size() < 2)
    {
        cout << "convex hull is empty" << endl;
    }
    else
    {
        vector<Point> S;
        S.push_back(Q[0]);
        S.push_back(Q[1]);
        S.push_back(Q[2]);
        for (int i = 3; i < Q.size(); i++)
        {
            while ((S[S.size() - 1].x - S[S.size() - 2].x) * (Q[i].y - S[S.size() - 2].y) -
                       (S[S.size() - 1].y - S[S.size() - 2].y) * (Q[i].x - S[S.size() - 2].x) >
                   0)
            {
                S.pop_back();
            }
            S.push_back(Q[i]);
        }
        for (int i = 0; i < S.size(); i++)
        {
            cout << S[i].x << "  " << S[i].y << endl;
        }
    }
}

int main()
{
    vector<Point> vec;
    vec.push_back(Point(1, 0));
    vec.push_back(Point(4, 0));
    vec.push_back(Point(0, 5));
    vec.push_back(Point(4, 2));
    vec.push_back(Point(2, 2));
    vec.push_back(Point(1, 3));
    vec.push_back(Point(7, 1));
    vec.push_back(Point(4, 3));
    vec.push_back(Point(6, 3));
    vec.push_back(Point(2, 1));
    vec.push_back(Point(4, 1));
    vec.push_back(Point(-3, 5));
    vec.push_back(Point(-4, 2));
    vec.push_back(Point(-2, -2));
    Graham_scan(vec);
    return 0;
}
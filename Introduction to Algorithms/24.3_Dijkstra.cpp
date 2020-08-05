// 单源最短路径_Dijkstra算法

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class Edge
{
private:
    int num;
    string key;
    int weight;

public:
    Edge(int u, string k, int w = 0)
    {
        num = u;
        key = k;
        weight = w;
    }
    friend class Figure;
};

class Point
{
    friend class Figure;

private:
    string key;
    string color;
    int father;
    bool in_remain = true;
    int dis = 1000000;

public:
    Point(string k)
    {
        key = k;
        color = "white";
        father = -1;
    }
};

class Figure
{
private:
    map<string, int> key_n;
    vector<Point> points;
    vector<int> topological;
    map<int, vector<Edge>> figure;

public:
    static int time;
    void add_Point(string k)
    {
        points.push_back(Point(k));
        key_n.insert(pair<string, int>(k, points.size() - 1));
        figure.insert(pair<int, vector<Edge>>(points.size() - 1, vector<Edge>()));
    }
    void add_Edge(string k1, string k2, int w = 0)
    {
        figure[key_n[k1]].push_back(Edge(key_n[k2], k2, w));
    }
    void relax(int a, Edge &e)
    {
        if (points[e.num].dis > points[a].dis + e.weight)
        {
            points[e.num].dis = points[a].dis + e.weight;
            points[e.num].father = a;
        }
    }
    void dijkstra(string k)
    {
        points[key_n[k]].dis = 0;
        int m = 0;
        for (int i = 0; i < points.size(); i++)
        {
            for (int j = 0; j < points.size(); j++)
            {
                if (points[j].in_remain == true)
                {
                    m = j;
                    break;
                }
            }
            for (int j = 0; j < points.size(); j++)
            {
                if (points[j].dis < points[m].dis && points[j].in_remain == true)
                {
                    m = j;
                }
            }
            points[m].in_remain = false;
            for (Edge &e : figure[m])
            {
                relax(m, e);
            }
        }
    }
};
int Figure::time = 0;
int main()
{

    Figure fig;
    fig.add_Point("s");
    fig.add_Point("t");
    fig.add_Point("x");
    fig.add_Point("y");
    fig.add_Point("z");

    fig.add_Edge("s", "t", 10);
    fig.add_Edge("s", "y", 5);
    fig.add_Edge("t", "x", 1);
    fig.add_Edge("t", "y", 2);
    fig.add_Edge("x", "z", 4);
    fig.add_Edge("y", "x", 9);
    fig.add_Edge("y", "z", 2);
    fig.add_Edge("y", "t", 3);
    fig.add_Edge("z", "x", 6);
    fig.add_Edge("z", "s", 7);
    fig.dijkstra("s");
    return 0;
}
// 单源最短路径_Bellman-Ford算法

#include <iostream>
#include <vector>
#include <map>
#include <string>
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

class Edge_Q
{
private:
    int a, b, weight;

public:
    Edge_Q(int x, int y, int w)
    {
        a = x;
        b = y;
        weight = w;
    }
    friend class Figure;
};

class Point
{
    friend class Figure;

private:
    string key;
    int dis;
    string color;
    int father;

public:
    Point(string k)
    {
        key = k;
        color = "white";
        father = -1;
        dis = 1000000;
    }
};

class Figure
{
private:
    map<string, int> key_n;
    vector<Point> points;
    vector<Edge_Q> edges;
    map<int, vector<Edge>> figure;

    void relax(Edge_Q e)
    {
        if (points[e.b].dis > points[e.a].dis + e.weight)
        {
            points[e.b].dis = points[e.a].dis + e.weight;
            points[e.b].father = e.a;
        }
    }

public:
    void add_Point(string k)
    {
        points.push_back(Point(k));
        key_n.insert(pair<string, int>(k, points.size() - 1));
        figure.insert(pair<int, vector<Edge>>(points.size() - 1, vector<Edge>()));
    }
    void add_Edge(string k1, string k2, int w = 0)
    {
        figure[key_n[k1]].push_back(Edge(key_n[k2], k2, w));
        // figure[key_n[k2]].push_back(Edge(key_n[k1], k1, w));
        edges.push_back(Edge_Q(key_n[k1], key_n[k2], w));
    }
    bool bellman_ford(string k)
    {
        points[key_n[k]].dis = 0;
        for (int i = 0; i < points.size(); i++)
        {
            for (Edge_Q &e : edges)
            {
                relax(e);
            }
        }
        for (Edge_Q &e : edges)
        {
            if (points[e.b].dis > points[e.a].dis + e.weight)
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    Figure fig;
    fig.add_Point("s");
    fig.add_Point("t");
    fig.add_Point("x");
    fig.add_Point("y");
    fig.add_Point("z");

    fig.add_Edge("s", "t", 6);
    fig.add_Edge("s", "y", 7);
    fig.add_Edge("t", "x", 5);
    fig.add_Edge("t", "y", 8);
    fig.add_Edge("t", "z", -4);
    fig.add_Edge("x", "t", -2);
    fig.add_Edge("y", "x", -3);
    fig.add_Edge("y", "z", 9);
    fig.add_Edge("z", "x", 7);
    fig.add_Edge("z", "s", 2);
    cout << fig.bellman_ford("s") << endl;
    return 0;
}
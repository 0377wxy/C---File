// 深度优先搜索

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
    int start = 0;
    int end = 0;

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

    void DFS(string k)
    {
        for (Point &u : points)
        {
            if (u.color == "white")
            {
                DFS_visit(u);
            }
        }
    }
    void DFS_visit(Point &u)
    {
        time++;
        u.start = time;
        u.color = "gray";
        for (Edge v : figure[key_n[u.key]])
        {
            if (points[v.num].color == "white")
            {
                DFS_visit(points[v.num]);
            }
        }
        u.color = "black";
        time++;
        u.end = time;
    }
};
int Figure::time = 0;
int main()
{

    Figure fig;
    fig.add_Point("u");
    fig.add_Point("v");
    fig.add_Point("w");
    fig.add_Point("x");
    fig.add_Point("y");
    fig.add_Point("z");
    fig.add_Edge("u", "x");
    fig.add_Edge("u", "v");
    fig.add_Edge("x", "v");
    fig.add_Edge("v", "y");
    fig.add_Edge("y", "x");
    fig.add_Edge("w", "y");
    fig.add_Edge("w", "z");
    fig.add_Edge("z", "z");
    fig.DFS("u");

    return 0;
}
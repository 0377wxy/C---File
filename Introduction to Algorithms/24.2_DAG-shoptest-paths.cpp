// 有向无环图中的单源最短路径问题

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
    void topological_sort()
    {
        DFS(points[0].key);
        topological = vector<int>(points.size() * 2 + 1, -1);
        for (Point v : points)
        {
            topological[v.end] = key_n[v.key];
        }
        for (vector<int>::iterator i = topological.begin(); i != topological.end();)
        {
            if (*i == -1)
            {
                topological.erase(i);
            }
            else
            {
                i++;
            }
        }
        reverse(topological.begin(), topological.end());
        for (int i : topological)
        {
            cout << points[i].key << "  ";
        }
        cout << endl;
    }
    void relax(int a, Edge &e)
    {
        if (points[e.num].dis > points[a].dis + e.weight)
        {
            points[e.num].dis = points[a].dis + e.weight;
            points[e.num].father = e.num;
        }
    }
    void DAG_shoptest_paths(string k)
    {
        points[key_n[k]].dis = 0;
        topological_sort();
        for (int i : topological)
        {
            for (Edge &e : figure[i])
            {
                relax(i, e);
            }
        }
    }
};
int Figure::time = 0;
int main()
{

    Figure fig;
    fig.add_Point("r");
    fig.add_Point("s");
    fig.add_Point("t");
    fig.add_Point("x");
    fig.add_Point("y");
    fig.add_Point("z");
    fig.add_Edge("r", "s", 5);
    fig.add_Edge("r", "t", 3);
    fig.add_Edge("s", "x", 6);
    fig.add_Edge("s", "t", 2);
    fig.add_Edge("t", "x", 7);
    fig.add_Edge("t", "y", 4);
    fig.add_Edge("t", "z", 2);
    fig.add_Edge("x", "y", -1);
    fig.add_Edge("x", "z", 1);
    fig.add_Edge("y", "z", -2);
    fig.DAG_shoptest_paths("s");

    return 0;
}
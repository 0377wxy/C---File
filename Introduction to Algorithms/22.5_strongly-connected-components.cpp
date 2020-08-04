// 强连通分量

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
    int d = 0;
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
    vector<Edge_Q> edges;
    map<int, vector<Edge>> figure;
    vector<int> stack;

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

        edges.push_back(Edge_Q(key_n[k1], key_n[k2], w));
    }
    void SCC()
    {
        Figure reverse;
        for (Point p : points)
        {
            reverse.add_Point(p.key);
        }
        for (Edge_Q e : edges)
        {
            reverse.add_Edge(points[e.b].key, points[e.a].key);
        }
        reverse.DFS();
        for (int i = reverse.stack.size() - 1; i >= 0; i--)
        {
            Point &u = points[reverse.stack[i]];
            if (u.color == "white")
            {
                DFS_visit(u);
                while (!stack.empty())
                {
                    cout << points[stack.back()].key << "  ";
                    stack.pop_back();
                }
                cout << endl;
            }
        }
    }

    void DFS()
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
        stack.push_back(key_n[u.key]);
        time++;
        u.end = time;
    }
};
int Figure::time = 0;
int main()
{
    /*
    Figure fig;
    fig.add_Point("r");
    fig.add_Point("v");
    fig.add_Point("s");
    fig.add_Point("w");
    fig.add_Point("t");
    fig.add_Point("x");
    fig.add_Point("u");
    fig.add_Point("y");
    fig.add_Edge("v", "r");
    fig.add_Edge("r", "s");
    fig.add_Edge("w", "x");
    fig.add_Edge("w", "t");
    fig.add_Edge("t", "u");
    fig.add_Edge("x", "y");
    fig.add_Edge("x", "u");
    fig.add_Edge("y", "u");
    fig.add_Edge("s", "w");
    fig.add_Edge("t", "x");
    fig.BFS("s");
    */

    /*
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
    */
    Figure fig;
    fig.add_Point("a");
    fig.add_Point("b");
    fig.add_Point("c");
    fig.add_Point("d");
    fig.add_Point("e");
    fig.add_Point("f");
    fig.add_Point("g");
    fig.add_Point("h");
    fig.add_Edge("a", "b");
    fig.add_Edge("b", "c");
    fig.add_Edge("b", "e");
    fig.add_Edge("c", "d");
    fig.add_Edge("c", "g");
    fig.add_Edge("d", "c");
    fig.add_Edge("d", "h");
    fig.add_Edge("h", "h");
    fig.add_Edge("e", "a");
    fig.add_Edge("e", "f");
    fig.add_Edge("f", "g");
    fig.add_Edge("g", "f");
    fig.add_Edge("g", "h");
    fig.SCC();
    return 0;
}
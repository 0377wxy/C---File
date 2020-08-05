// 拓扑排序

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
    void topological_sort()
    {
        DFS(points[0].key);
        vector<int> res(points.size() * 2 + 1, -1);
        for (Point v : points)
        {
            res[v.end] = key_n[v.key];
        }
        for (vector<int>::iterator i = res.begin(); i != res.end();)
        {
            if (*i == -1)
            {
                res.erase(i);
            }
            else
            {
                i++;
            }
        }
        reverse(res.begin(), res.end());
        for (int i : res)
        {
            cout << points[i].key << "  ";
        }
        cout << endl;
    }
};
int Figure::time = 0;
int main()
{

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
    fig.add_Point("i");
    fig.add_Edge("a", "b");
    fig.add_Edge("a", "h");
    fig.add_Edge("b", "h");
    fig.add_Edge("b", "c");
    fig.add_Edge("c", "f");
    fig.add_Edge("d", "c");
    fig.add_Edge("d", "e");
    fig.add_Edge("e", "f");
    fig.add_Edge("g", "h");
    fig.topological_sort();

    return 0;
}
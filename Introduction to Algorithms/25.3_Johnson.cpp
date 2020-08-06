// 所有节点对的最短路径算法-Johnson算法

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
    bool in_remain = true;

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

    void relax_bellman_ford(Edge_Q e)
    {
        if (points[e.b].dis > points[e.a].dis + e.weight)
        {
            points[e.b].dis = points[e.a].dis + e.weight;
            points[e.b].father = e.a;
        }
    }
    void relax_dijkstra(int a, Edge &e)
    {
        if (points[e.num].dis > points[a].dis + e.weight)
        {
            points[e.num].dis = points[a].dis + e.weight;
            points[e.num].father = a;
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
                relax_bellman_ford(e);
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
    void dijkstra(string k)
    {
        points[key_n[k]].dis = 0;
        points[key_n[k]].father = -1;
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
                relax_dijkstra(m, e);
            }
        }
    }
    void johnson()
    {
        add_Point("N");
        for (Point &p : points)
        {
            add_Edge("N", p.key, 0);
        }
        if (bellman_ford("N"))
        {
            for (int i = 0; i < points.size(); i++)
            {
                for (Edge &e : figure[i])
                {
                    e.weight = e.weight + points[i].dis - points[e.num].dis;
                }
            }
            vector<vector<int>> D(points.size(), vector<int>(points.size(), 111111));
            vector<vector<int>> F(points.size(), vector<int>(points.size(), -1));
            for (Point &p : points)
            {
                for (Point &p1 : points)
                {
                    p1.dis = 1000000;
                    p1.in_remain = true;
                }
                dijkstra(p.key);
                for (Point &p1 : points)
                {
                    D[key_n[p.key]][key_n[p1.key]] = p1.dis;
                    F[key_n[p.key]][key_n[p1.key]] = p1.father;
                }
            }
            int n = points.size();
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << D[i][j] << "    ";
                }
                cout << endl;
            }
            cout << "------------------------" << endl;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << F[i][j] << "    ";
                }
                cout << endl;
            }
        }
        else
        {
            cout << "error" << endl;
        }
    }
};

int main()
{
    Figure fig;
    fig.add_Point("1");
    fig.add_Point("2");
    fig.add_Point("3");
    fig.add_Point("4");
    fig.add_Point("5");

    fig.add_Edge("1", "2", 3);
    fig.add_Edge("1", "5", -4);
    fig.add_Edge("2", "5", 7);
    fig.add_Edge("2", "4", 1);
    fig.add_Edge("3", "2", 4);
    fig.add_Edge("4", "3", -5);
    fig.add_Edge("4", "1", 2);
    fig.add_Edge("5", "4", 6);

    fig.johnson();
    return 0;
}
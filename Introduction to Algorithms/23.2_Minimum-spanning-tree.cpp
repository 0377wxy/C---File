// 最小生成树-Kruskal算法与prim算法

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
    int min_weight = 100000; // 最小生成树 用

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

public:
    static int time;
    void add_Point(string k)
    {
        points.push_back(Point(k));
        key_n.insert(pair<string, int>(k, points.size() - 1));
        figure.insert(pair<int, vector<Edge>>(points.size() - 1, vector<Edge>()));
        points[points.size() - 1].father = points.size() - 1;
    }
    void add_Edge(string k1, string k2, int w = 0)
    {
        figure[key_n[k1]].push_back(Edge(key_n[k2], k2, w));
        figure[key_n[k2]].push_back(Edge(key_n[k1], k1, w));
        edges.push_back(Edge_Q(key_n[k1], key_n[k2], w));
    }
    void BFS(string k)
    {
        vector<int> Q;
        Q.push_back(key_n[k]);
        points[key_n[k]].color = "gray";
        while (Q.size() > 0)
        {
            int u = Q[0];
            for (Edge v : figure[u])
            {
                if (points[v.num].color == "white")
                {
                    points[v.num].color = "gray";
                    points[v.num].d = points[u].d + 1;
                    points[v.num].father = u;
                    Q.push_back(v.num);
                }
            }
            Q.erase(Q.begin());
            points[u].color = "black";
        }
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
    void edge_nondecreasing_order()
    {
        sort(edges.begin(), edges.end(), [](Edge_Q a, Edge_Q b) -> bool { return a.weight < b.weight; });
    }
    int find_farher(Point a) // 最小生成树算法——MST_kruskal用
    {
        if (a.father != key_n[a.key])
        {
            return find_farher(points[a.father]);
        }
        else
        {
            return a.father;
        }
    }
    void MST_kruskal()
    {
        edge_nondecreasing_order();
        vector<Edge_Q> res;
        for (Edge_Q e : edges)
        {
            if (find_farher(points[e.a]) != find_farher(points[e.b]))
            {
                res.push_back(e);
                points[e.b].father = points[e.a].father;
            }
        }
        for (Edge_Q e : res)
        {
            cout << points[e.a].key << "--" << points[e.b].key << endl;
        }
    }
    void MST_prim()
    {
        vector<Point> Q = points;
        points[0].min_weight = 0;
        for (int j = 0; j < points.size(); j++)
        {
            vector<Point>::iterator m = Q.begin();
            for (vector<Point>::iterator i = Q.begin(); i != Q.end(); i++)
            {
                if (i->min_weight <= m->min_weight)
                {
                    m = i;
                }
            }
            for (Edge e : figure[key_n[m->key]])
            {
                if (Q[e.num].min_weight != 11111 && e.weight < Q[e.num].min_weight)
                {
                    points[e.num].father = key_n[m->key];
                    Q[e.num].min_weight = e.weight;
                }
            }
            m->min_weight = 11111;
        }
    }
};

int Figure::time = 0;
int main()
{
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
    fig.add_Edge("a", "b", 4);
    fig.add_Edge("a", "h", 8);
    fig.add_Edge("b", "h", 11);
    fig.add_Edge("b", "c", 8);
    fig.add_Edge("c", "f", 4);
    fig.add_Edge("c", "d", 7);
    fig.add_Edge("c", "i", 2);
    fig.add_Edge("d", "e", 9);
    fig.add_Edge("d", "f", 14);
    fig.add_Edge("e", "f", 10);
    fig.add_Edge("f", "g", 2);
    fig.add_Edge("g", "h", 1);
    fig.add_Edge("g", "i", 6);
    fig.add_Edge("h", "i", 7);
    fig.MST_prim();
    return 0;
}
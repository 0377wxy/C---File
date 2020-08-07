// 最大流问题 - Ford-Fulkerson方法

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
    int capacity;
    int flow = 0;

public:
    Edge(int u, string k, int c = 0)
    {
        num = u;
        key = k;
        capacity = c;
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
    map<int, vector<Edge>> residual;

public:
    static int time;
    void add_Point(string k)
    {
        points.push_back(Point(k));
        key_n.insert(pair<string, int>(k, points.size() - 1));
        figure.insert(pair<int, vector<Edge>>(points.size() - 1, vector<Edge>()));
        residual.insert(pair<int, vector<Edge>>(points.size() - 1, vector<Edge>()));
    }
    void add_Edge(string k1, string k2, int c = 0)
    {
        figure[key_n[k1]].push_back(Edge(key_n[k2], k2, c));
        residual[key_n[k1]].push_back(Edge(key_n[k2], k2, c));
    }
    bool BFS(string k, string t)
    {
        for (Point &p : points)
        {
            p.color = "white";
            p.father = -1;
        }
        vector<int> Q;
        Q.push_back(key_n[k]);
        points[key_n[k]].color = "gray";
        while (Q.size() > 0)
        {
            int u = Q[0];
            for (Edge v : residual[u])
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
        return points[key_n[t]].father != -1;
    }
    void ford_fulkerson(string s, string t)
    {
        while (BFS(s, t))
        {
            vector<int> paths;
            int p = key_n[t];
            while (points[p].father != -1)
            {
                paths.push_back(p);
                p = points[p].father;
            }
            paths.push_back(key_n[s]);
            reverse(paths.begin(), paths.end());
            int path_capacity = 9999999;
            for (int i = 0; i < paths.size() - 1; i++)
            {
                for (Edge &e : residual[paths[i]])
                {
                    if (e.num == paths[i + 1])
                    {
                        if (e.capacity < path_capacity)
                        {
                            path_capacity = e.capacity;
                            break;
                        }
                    }
                }
            }
            for (int i = 0; i < paths.size() - 1; i++)
            {
                bool w = false;
                int front = 0;
                int behind = 0;
                for (Edge &e : figure[paths[i]])
                {
                    if (e.num == paths[i + 1])
                    {
                        e.flow += path_capacity;
                        front = e.capacity - e.flow;
                        behind = e.flow;
                        w = true;
                        break;
                    }
                }
                if (!w)
                {
                    for (Edge &e : figure[paths[i + 1]])
                    {
                        if (e.num == paths[i])
                        {
                            e.flow -= path_capacity;

                            front = e.flow;
                            behind = e.capacity - e.flow;
                            break;
                        }
                    }
                }
                vector<Edge>::iterator j = residual[paths[i]].begin();
                for (; j != residual[paths[i]].end(); j++)
                {
                    if (j->num == paths[i + 1])
                    {
                        if (front != 0)
                        {
                            j->capacity = front;
                        }
                        else
                        {
                            residual[paths[i]].erase(j);
                        }
                        break;
                    }
                }
                if (j == residual[paths[i]].end() && front != 0)
                {
                    residual[paths[i]].push_back(Edge(paths[i + 1], points[paths[i + 1]].key, front));
                }
                j = residual[paths[i + 1]].begin();
                for (; j != residual[paths[i + 1]].end(); j++)
                {
                    if (j->num == paths[i])
                    {
                        if (behind != 0)
                        {
                            j->capacity = behind;
                        }
                        else
                        {
                            residual[paths[i + 1]].erase(j);
                        }
                        break;
                    }
                }
                if (j == residual[paths[i + 1]].end() && behind != 0)
                {
                    residual[paths[i + 1]].push_back(Edge(paths[i], points[paths[i]].key, behind));
                }
            }
        }
    }
};

int main()
{
    Figure fig;
    fig.add_Point("s");
    fig.add_Point("t");
    fig.add_Point("1");
    fig.add_Point("2");
    fig.add_Point("3");
    fig.add_Point("4");
    fig.add_Edge("s", "1", 16);
    fig.add_Edge("s", "2", 13);
    fig.add_Edge("1", "3", 12);
    fig.add_Edge("2", "1", 4);
    fig.add_Edge("2", "4", 14);
    fig.add_Edge("3", "t", 20);
    fig.add_Edge("3", "2", 9);
    fig.add_Edge("4", "3", 7);
    fig.add_Edge("4", "t", 4);
    fig.ford_fulkerson("s", "t");
    return 0;
}
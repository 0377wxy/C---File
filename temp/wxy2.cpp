#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Node
{             //记录节点位置
    int x, y; //记录坐标
    int num;  //记录节点编号
};

int m, n;
vector<vector<int>> ma;                     //ector套vector记录矩阵
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1}; //方向数组
stack<Node> s;                              //模拟运行栈

bool OK(int x, int y)
{ //判断坐标xy是否在矩阵中
    return x >= 0 && y >= 0 && x < m && y < n;
}

int main()
{
    int hc;
    cin >> m >> n;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> ma[i][j];
            cout << "!";
        }
    }
    //////
    int countt = 0;
    Node now;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (ma[i][j])
            {
                countt++; //记录连通块数量
                s.push(Node{i, j, ma[i][j]});
                ma[i][j] = 0;
                while (!s.empty())
                { //通过类似bfs的方法，使用先进后出的顺序。
                    now = s.top();
                    for (int dd = 0; dd < 4; dd++)
                    { //枚举方向
                        int xx = now.x + dir[i][0];
                        int yy = now.y + dir[i][1];
                        if (OK(xx, yy) && ma[xx][yy] == now.num)
                        { //如果符合条件，推入栈
                            s.push(Node{xx, yy, ma[xx][yy]});
                            ma[xx][yy] = 0; //标记已经到达这个点
                        }
                    }
                }
            }
        }
    }
    cout << countt << endl;
}
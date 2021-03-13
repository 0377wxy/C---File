#include <iostream>
using namespace std;
int dir[4][2] = {0, 1,
                 0, -1,
                 1, 0,
                 -1, 0};
class Node
{
public:
    int a, b;
};
class Stack
{
public:
    Node *p;
    int num;
    Stack()
    {
        p = new Node[300];
        num = 0;
    }
    ~Stack()
    {
        delete p;
    }
    void push(int x, int y)
    {
        p[num].a = x;
        p[num].b = y;
        num++;
    }
    Node *back()
    {
        return p + num - 1;
    }
    void pop()
    {
        num--;
    }
};

int main()
{
    int m, n;
    cout << " 行列 ：" << endl;
    cin >> m >> n;
    int con[15][15];
    int use[15][15] = {0};
    int res = 0;
    Stack st;
    for (int i = 0; i <= n + 1; i++)
    {
        use[0][i] = 1;
        use[m + 1][i] = 1;
    }
    for (int j = 0; j <= m + 1; j++)
    {
        use[j][0] = 1;
        use[j][n + 1] = 1;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> con[i][j];
        }
    }

    int x, y;
    Node *p;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (use[i][j] == 0)
            {
                st.push(i, j);
            LOOP:
                while (st.num != 0)
                {
                    p = st.back();
                    use[p->a][p->b] = 1;
                    for (int k = 0; k < 4; k++)
                    {
                        x = p->a + dir[k][0];
                        y = p->b + dir[k][1];

                        if (use[x][y] == 0 && con[p->a][p->b] == con[x][y])
                        {
                            st.push(x, y);
                            goto LOOP;
                        }
                    }
                    st.pop();
                }
                res++;
            }
        }
    }
    cout << res << endl;
    return 0;
}

/*
4 3
1 2 2
1 3 2
3 3 1
2 2 1
*/
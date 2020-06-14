#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

//点
class CPoint
{
public:
    int x, y;
    CPoint(int x = 0, int y = 0) : x(x), y(y) {}
    friend double getdis(CPoint a, CPoint b);
    friend istream &operator>>(istream &inp, CPoint &pp);
};
istream &operator>>(istream &inp, CPoint &pp)
{
    cin >> pp.x >> pp.y;
    return inp;
}

double getdis(CPoint a, CPoint b) //求两个点之间的距离
{
    double res;
    res = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    return res;
}
//基类：形状
class CShape
{
public:
    virtual bool hitin(CPoint pos) = 0;
    virtual ~CShape()
    {
        cout << "    xx     " << endl;
    }
};
//派生类：矩形
class CRectangle : public CShape
{
public:
    CPoint pos; //左上角的点
    int width;
    int height;
    CRectangle(CPoint pos, int height, int width) : height(height), width(width), pos(pos) {}
    bool hitin(CPoint hitp);
};

bool CRectangle::hitin(CPoint hitp) //判断是否点在这个方形里面
{
    int xp = pos.x;
    int yp = pos.y;
    int xx = hitp.x;
    int yy = hitp.y;
    int xb = xp + width;
    int yb = yp + height;
    return xx >= xp && yy >= yp && xx <= xb && yy <= yb;
}
//派生类：圆
class CCircle : public CShape
{
public:
    CPoint pos; //圆心
    double r;
    CCircle(CPoint pos, double r) : r(r), pos(pos) {}
    bool hitin(CPoint hitp);
};

bool CCircle::hitin(CPoint hitp) //检测是否点在这个圆里面
{
    return getdis(hitp, pos) <= r;
}
//基类：UI控件
class UIControl
{
public:
    CShape *p_shape;
    bool hittest(CPoint pos);
    void setshape(CShape *);
    virtual void Clicked() = 0;
    virtual ~UIControl()
    {
        delete p_shape;
    }
};

void UIControl::setshape(CShape *inpshape)
{
    p_shape = inpshape;
}

bool UIControl::hittest(CPoint pos)
{
    return p_shape->hitin(pos);
}
//派生类：菜单
class CMenu : public UIControl
{
public:
    string name;
    CMenu(string str);
    virtual void Clicked();
};

CMenu::CMenu(string str) : name(str) {} //构造函数，输入字符串构造控件

void CMenu::Clicked()
{
    cout << "menu-" << name << " Clicked" << endl;
}
//派生类：按钮
class CButton : public UIControl
{
    string name;

public:
    CButton(string str);
    virtual void Clicked();
};
CButton::CButton(string str) : name(str) {}

void CButton::Clicked()
{
    cout << "button-" << name << " Clicked" << endl;
}

int main()
{
    int n;
    vector<UIControl *> vt;
    string typ, namee;
    cin >> n;
    UIControl *px;
    for (int i = 0; i < n; i++)
    {
        cin >> typ;
        if (typ == "menu")
        { //菜单类
            cin >> namee;
            px = new CMenu(namee);
        }
        else if (typ == "button")
        { //按钮类
            cin >> namee;
            px = new CButton(namee);
        }
        cin >> typ;
        CPoint xx;
        double rr;
        int ww, hh;
        CShape *px2;
        if (typ == "rectangle")
        { //矩形的情况
            cin >> xx >> hh >> ww;
            px2 = new CRectangle(xx, hh, ww);
        }
        else if (typ == "circle")
        { //圆形的情况
            cin >> xx >> rr;
            px2 = new CCircle(xx, rr);
        }
        px->setshape(px2);
        //cout<<px->name<<endl;
        vt.push_back(px);
    }
    string hc;
    int siz = vt.size();
    while (cin >> hc)
    {
        bool flag = 0;
        CPoint inp;
        cin >> inp;
        for (int i = siz - 1; i >= 0; i--)
        {
            if (vt[i]->hittest(inp))
            {
                vt[i]->Clicked();
                flag = 1;
                break;
            }
        }
        if (!flag)
            cout << "none hit" << endl;
    }
    while (vt.empty())
    { //释放内存
        px = vt.back();
        delete px;
        vt.pop_back();
    }
}

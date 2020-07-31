// van Emde Boas 树

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Node
{
private:
    int u = 0;
    int Min = -1;
    int Max = -1;
    Node *summary = NULL;
    vector<Node *> cluster;

    int high(int x)
    {
        return floor(x / pow(2, floor(log2(u) / 2)));
    }
    int low(int x)
    {
        return x % int(pow(2, floor(log2(u) / 2)));
    }
    int index(int x, int y)
    {
        if (y == -1)
        {
            return -1;
        }
        else
        {
            return x * pow(2, floor(log2(u) / 2)) + y;
        }
    }

public:
    Node(int ux)
    {
        u = ux;
        cluster = vector<Node *>(pow(2, ceil(log2(u) / 2)), NULL);
        if (u > 2)
        {
            summary = new Node(pow(2, ceil(log2(u) / 2)));
            for (Node *&x : cluster)
            {
                x = new Node(floor(sqrt(u)));
            }
        }
    }
    int VEB_minimum()
    {
        return Min;
    }
    int VEB_maximum()
    {
        return Max;
    }
    void VEB_empty_insert(int x)
    {
        Min = x;
        Max = x;
    }
    void VEB_insert(int x)
    {
        if (Min == -1)
        {
            VEB_empty_insert(x);
        }
        else
        {
            if (x < Min)
            {
                int temp = x;
                x = Min;
                Min = temp;
            }
            if (u > 2)
            {
                if (cluster[high(x)]->Min == -1)
                {
                    summary->VEB_insert(high(x));
                    cluster[high(x)]->VEB_empty_insert(low(x));
                }
                else
                {
                    cluster[high(x)]->VEB_insert(low(x));
                }
            }
            if (x > Max)
            {
                Max = x;
            }
        }
    }
    bool VEB_member(int x)
    {
        if (x == Min || x == Max)
        {
            return true;
        }
        else if (u == 2)
        {
            return false;
        }
        else
        {
            return cluster[high(x)]->VEB_member(low(x));
        }
    }
    int VEB_successor(int x) //后继
    {
        if (u == 2)
        {
            if (x == 0 && Max == 1)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        else if (Min != -1 && x < Min)
        {
            return Min;
        }
        else
        {
            int max_low = cluster[high(x)]->VEB_maximum();
            if (max_low != -1 && low(x) < max_low)
            {
                int offest = cluster[high(x)]->VEB_successor(low(x));
                return index(high(x), offest);
            }
            else
            {
                int succ_cluster = summary->VEB_successor(high(x));
                if (succ_cluster == -1)
                {
                    return -1;
                }
                else
                {
                    int offset = cluster[succ_cluster]->VEB_minimum();
                    return index(succ_cluster, offset);
                }
            }
        }
    }
    int VEB_predecessor(int x) //前驱
    {
        if (u == 2)
        {
            if (x == 1 && Min == 0)
            {
                return 0;
            }
            else
            {
                return -1;
            }
        }
        else if (Max != -1 && x > Max)
        {
            return Max;
        }
        else
        {
            int min_low = cluster[high(x)]->VEB_minimum();
            if (min_low != -1 && low(x) > min_low)
            {
                int offest = cluster[high(x)]->VEB_predecessor(low(x));
                return index(high(x), offest);
            }
            else
            {
                int pred_cluster = summary->VEB_predecessor(high(x));
                if (pred_cluster == -1)
                {
                    if (Min != -1 && x > Min)
                    {
                        return Min;
                    }
                    else
                    {
                        return -1;
                    }
                }
                else
                {
                    int offset = cluster[pred_cluster]->VEB_maximum();
                    return index(pred_cluster, offset);
                }
            }
        }
    }
    int VEB_delete(int x)
    {
        if (Min == Max)
        {
            Min = -1;
            Max = -1;
        }
        else if (u == 2)
        {
            if (x == 0)
            {
                Min = 1;
            }
            else
            {
                Min = 0;
            }
            Max = Min;
        }
        else
        {
            if (x == Min)
            {
                int first_cluster = summary->VEB_minimum();
                x = index(first_cluster, cluster[first_cluster]->Min);
                Min = x;
            }
            cluster[high(x)]->VEB_delete(low(x));
            if (cluster[high(x)]->Min == -1)
            {
                summary->VEB_delete(high(x));
                if (x == Max)
                {
                    int summary_max = summary->Max;
                    if (summary_max == -1)
                    {
                        Max = Min;
                    }
                    else
                    {
                        Max = index(summary_max, cluster[summary_max]->Max);
                    }
                }
            }
            else if (x == Max)
            {
                Max = index(high(x), cluster[high(x)]->Max);
            }
        }
    }
};

int main()
{

    Node *VEB = new Node(16);
    //VEB->VEB_insert(2);
    VEB->VEB_insert(3);
    VEB->VEB_insert(15);
    VEB->VEB_insert(4);
    VEB->VEB_insert(5);
    cout << VEB->VEB_member(4) << endl;
    cout << VEB->VEB_member(7) << endl;
    cout << VEB->VEB_successor(4) << endl;
    cout << VEB->VEB_predecessor(5) << endl;
    VEB->VEB_delete(3);
    cout << VEB->VEB_member(3) << endl;
    return 0;
}
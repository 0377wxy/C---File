#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Item
{
public:
    int value = 0;
    int weight = 0;
    Item(int a, int b) : value(b), weight(a) {}
};
void fff(vector<Item> &tr, int loc[5][21], int max_m)
{
    for (int i = 1; i <= max_m; i++)
    {
        for (int j = 1; j < tr.size(); j++)
        {
            if (i < tr[j].weight)
            {
                loc[j][i] = loc[j - 1][i];
            }
            else
            {
                loc[j][i] = max(loc[j - 1][i], loc[j - 1][i - tr[j].weight] + tr[j].value);
            }
            cout << loc[j][i] << "   ";
        }
        cout << endl;
    }
}
int main()
{
    vector<Item> tr;
    tr.push_back(Item(0, 0));
    tr.push_back(Item(2, 3));
    tr.push_back(Item(3, 4));
    tr.push_back(Item(4, 8));
    tr.push_back(Item(5, 8));
    tr.push_back(Item(9, 10));

    int max_m = 20;
    int Loc[6][21];
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            Loc[i][j] = 0;
        }
    }

    fff(tr, Loc, max_m);
    cout << Loc[5][20] << endl;
    return 0;
}
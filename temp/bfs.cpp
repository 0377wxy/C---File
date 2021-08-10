// 农夫过河

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <bitset>
using namespace std;

int main()
{
    unsigned act[4] = {8, 12, 10, 9};
    vector<pair<int, int>> st;
    queue<pair<int, int>> qu;
    qu.push(make_pair(0, 0));
    unsigned fr, fr_ele, temp;
    pair<int, int> te_pair;
    int f = 1;
    while (f)
    {

        te_pair = qu.front();
        fr = te_pair.second;
        qu.pop();
        st.push_back(te_pair);
        for (int i = 0; i < 4; i++)
        {
            temp = fr & act[i];
            if (temp == 0 || temp == act[i])
                temp = fr ^ act[i];
            else
                continue;

            if (bool(temp & 0b1000) == bool(temp & 0b0010) || ((bool(temp & 0b1000) == bool(temp & 0b0100)) & (bool(temp & 0b1000) == bool(temp & 0b0001))))
            {
                qu.push(make_pair(st.size() - 1, temp));
                if (temp == 15)
                {
                    f = 0;
                    te_pair = make_pair(st.size() - 1, temp);
                    break;
                }
            }
        }
    }

    cout << "--" << endl;

    do
    {
        cout << bitset<4>(te_pair.second) << endl;
        te_pair = st[te_pair.first];
    } while (te_pair.second);
    cout << bitset<4>(0) << endl;
    return 0;
}
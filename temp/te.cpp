#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int wei[100001], sa[100001];
    int n, sb[100001];
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> wei[i];
        }
        sa[0] = wei[0];
        sb[0] = 0;
        sa[1] = wei[1];
        sb[1] = wei[0];
        for (int i = 2; i < n; i++)
        {
            sa[i] = max(sa[i - 2] + wei[i], wei[i] + sb[i - 1]);
            sb[i] = max(sa[i - 1], sb[i - 1]);
        }
        cout << max(sa[n - 1], sb[n - 1]) << endl;
    }
    return 0;
}
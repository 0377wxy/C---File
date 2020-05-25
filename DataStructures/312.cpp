#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool palchecker(string aString)
{
    vector<char> deque;
    for (char x : aString)
    {
        deque.push_back(x);
    }
    bool stillEquall = true;
    while (deque.size() > 1 && stillEquall)
    {
        if (deque.back() != deque.front())
        {
            stillEquall = false;
        }
        deque.pop_back();
        deque.erase(deque.begin(), deque.begin() + 1);
    }
    return stillEquall;
}

int main()
{
    string x1 = "asdfdsa";
    string x2 = "qwer";
    cout << palchecker(x1) << endl;
    cout << palchecker(x2) << endl;
    return 0;
}
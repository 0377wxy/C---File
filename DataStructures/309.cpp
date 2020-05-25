#include <iostream>
#include <string>
#include <vector>
using namespace std;

string hotPotato(vector<string> namelist, int num)
{
    while (namelist.size() > 1)
    {
        for (int i = 0; i < num; i++)
        {
            string temp = namelist.back();
            namelist.pop_back();
            namelist.insert(namelist.begin(), temp);
        }
        namelist.pop_back();
    }
    return namelist.back();
}

int main()
{
    vector<string> x1;
    x1.push_back("a");
    x1.push_back("b");
    x1.push_back("c");
    x1.push_back("d");
    x1.push_back("e");
    cout << hotPotato(x1, 2) << endl;
    return 0;
}
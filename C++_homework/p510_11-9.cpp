#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
int main()
{
    ifstream in("xxx.txt");
    ofstream out("xxxa.txt");
    string line;
    int lineNumber = 1;
    while (getline(in, line))
    {
        out << setw(4) << lineNumber++ << " " << line << endl;
    }

    in.close();
    out.close();

    return 0;
}
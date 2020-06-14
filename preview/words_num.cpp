#include <iostream>
using namespace std;
int main()
{
    string str1, str2;
    long long word = 0;
    int num = 0;
    while (1)
    {
        getline(cin, str1);
        if (str1[0] == '#')
            break;
        str1.erase(str1.find_first_of(' '), str1.find_first_not_of(' '));
        str1.erase(str1.find_last_not_of(' ') + 1);
        str1 = " " + str1 + " ";
        for (int i = 0; i < str1.size(); i++)
        {
            if (word == 0 && str1[i] != ' ')
            {

                int word_end = 0;
                word_end = str1.find_first_of(' ', i);
                str2 = " " + str1.substr(i, word_end - i) + " ";
                if (str1.find(str2) == i - 1)
                {
                    num++;
                }
            }
            if (str1[i] == ' ')
                word = 0;
            else
                word = 1;
        }
        cout << num << endl;
        num = 0;
    }
    return 0;
}
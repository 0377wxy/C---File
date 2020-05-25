#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

string infixToPostfix(string infixexper)
{
    map<char, int> prec;
    prec['*'] = 3;
    prec['/'] = 3;
    prec['+'] = 2;
    prec['-'] = 2;
    prec['('] = 1;

    vector<char> opStack;
    string postfixList;
    for (char token : infixexper)
    {
        string chers = "0123456789ABCDEFGHJKLMO";
        if (chers.find(token) != string::npos)
            postfixList.push_back(token);
        else if (token == '(')
            opStack.push_back(token);
        else if (token == ')')
        {
            char topToken = opStack.back();
            opStack.pop_back();
            while (topToken != ')')
            {
                postfixList.push_back(topToken);
                topToken = opStack.back();
                opStack.pop_back();
            }
        }
        else
        {
            while (opStack.empty() == false && (prec[opStack.back()] >= prec[token]))
            {
                postfixList.push_back(opStack.back());
                opStack.pop_back();
            }
            opStack.push_back(token);
        }
    }
    while (opStack.empty() != true)
    {
        postfixList.push_back(opStack.back());
        opStack.pop_back();
    }
    return postfixList;
}

int main()
{
    string xx;
    xx = "1+2*3";
    cout << infixToPostfix(xx) << endl;
    return 0;
}
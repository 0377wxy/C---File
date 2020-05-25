#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
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

int doMath(char op, int op1, int op2)
{
    if (op == '*')
        return op1 * op2;
    if (op == '/')
        return op1 / op2;
    if (op == '+')
        return op1 + op2;
    else
        return op1 - op2;
}

int postFixEval(string postFixExpr)
{
    vector<int> Stake1;
    for (char token : postFixExpr)
    {
        string chars = "0123456789";
        if (chars.find(token) != string::npos)
        {
            stringstream temp1;
            int a1;
            temp1 << token;
            temp1 >> a1;
            Stake1.push_back(a1);
        }
        else
        {
            int operand2 = Stake1.back();
            Stake1.pop_back();
            int operand1 = Stake1.back();
            Stake1.pop_back();
            int result = doMath(token, operand1, operand2);
            Stake1.push_back(result);
        }
    }
    return Stake1.back();
}

int main()
{
    string xx;
    xx = "1+2*3";
    cout << postFixEval(infixToPostfix(xx)) << endl;
    return 0;
}
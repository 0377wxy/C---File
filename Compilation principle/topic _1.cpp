#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <utility>

using namespace std;

// 状态定义
#define ID 1
#define DE 2
#define OP 3
#define NUM 4

int id_staus(char &cur, string &str, vector<vector<pair<string, string>>> &res, int &cur_r, vector<string> &error);
int de_staus(char &cur, string &str, vector<vector<pair<string, string>>> &res, int &cur_r, vector<string> &error);
int op_staus(char &cur, string &str, vector<vector<pair<string, string>>> &res, int &cur_r, vector<string> &error);
int num_staus(char &cur, string &str, vector<vector<pair<string, string>>> &res, int &cur_r, vector<string> &error);
void print(vector<string> &ve);

int main()
{
    // 读文件
    ifstream in("Compilation principle\\text_all.txt", ios::out | ios::in);
    if (!in.is_open())
    {
        cerr << "open file failed!" << endl;
        exit(-1);
    }
    // 结果存放
    vector<vector<pair<string, string>>> result;
    vector<string> error;
    //初始化状态
    int cur_status = 1;
    int new_status = 1;
    //读取字符存放
    string cur_row = "";
    string cur_str = "";

    int cur_r = -1;
    while (getline(in, cur_row))
    {
        cur_r++;
        vector<pair<string, string>> t1;
        result.push_back(t1);
        cur_row += ' ';
        for (int i = 0; i < cur_row.size(); i++)
        {
            switch (cur_status)
            {
            case ID:
                new_status = id_staus(cur_row[i], cur_str, result, cur_r, error);
                break;
            case DE:
                new_status = de_staus(cur_row[i], cur_str, result, cur_r, error);
                break;
            case OP:
                new_status = op_staus(cur_row[i], cur_str, result, cur_r, error);
                break;
            case NUM:
                new_status = num_staus(cur_row[i], cur_str, result, cur_r, error);
                break;
            }
            if (cur_status != new_status)
            {
                cur_status = new_status;
                switch (cur_status)
                {
                case ID:
                    new_status = id_staus(cur_row[i], cur_str, result, cur_r, error);
                    break;
                case DE:
                    new_status = de_staus(cur_row[i], cur_str, result, cur_r, error);
                    break;
                case OP:
                    new_status = op_staus(cur_row[i], cur_str, result, cur_r, error);
                    break;
                case NUM:
                    new_status = num_staus(cur_row[i], cur_str, result, cur_r, error);
                    break;
                }
            }
        }
    }

    in.close();

    for (int i = 0; i <= cur_r; i++)
    {
        cout << i + 1 << " row : ";
        for (int j = 0; j < result[i].size(); j++)
        {
            //cout << "< " << result[i][j].first << " , " << result[i][j].second << " >  ";
            cout << "<" << result[i][j].first << "," << result[i][j].second << "> ";
        }
        cout << endl;
    }
    for (int i = 0; i < error.size(); i++)
    {
        cout << error[i] << endl;
    }
    return 0;
}

int id_staus(char &cur, string &str, vector<vector<pair<string, string>>> &res, int &cur_r, vector<string> &error)
{
    static char de[] = {',', ';', '[', ']', '{', '}', '(', ')'};
    static char op[] = {'+', '-', '*', '/', '%', '=', '!', '<', '>', '&', '|'};
    static string id[] = {"if", "else", "break", "continue", "return", "int", "main", "const", "void", "while"};
    int clear_f = 0;
    // 是否转到 分隔符
    for (int i = 0; i < 8; i++)
    {
        if (cur == de[i])
        {
            clear_f = DE;
        }
    }
    //是否转到 运算符
    for (int i = 0; i < 11; i++)
    {
        if (cur == op[i])
        {
            clear_f = OP;
        }
    }
    //是否因空格结束当前字符串
    if (cur == ' ')
    {
        clear_f = DE;
    }
    //决定 状态转换
    if (clear_f != 0)
    {
        //结束当前字符串
        int f = 0;
        for (int i = 0; i < 10; i++)
        {
            if (str == id[i])
            {
                res[cur_r].push_back(make_pair("KEY", str));
                f = 1;
            }
        }
        if (f == 0 && str != "")
        {
            res[cur_r].push_back(make_pair("ID", str));
            if (str[0] >= '0' && str[0] <= '9')
            {
                string te = "error : " + to_string(cur_r) + " row , illegal identifier < " + str + " >";
                error.push_back(te);
            }
        }
        str = "";
        //跳转
        return clear_f;
    }
    //不跳转 处理当前字符
    str += cur;
    return ID;
}

int de_staus(char &cur, string &str, vector<vector<pair<string, string>>> &res, int &cur_r, vector<string> &error)
{
    static char de[] = {',', ';', '[', ']', '{', '}', '(', ')'};
    static char op[] = {'+', '-', '*', '/', '%', '=', '!', '<', '>', '&', '|'};
    int clear_f = 0;

    //是否转到 运算符
    for (int i = 0; i < 11; i++)
    {
        if (cur == op[i])
        {
            clear_f = OP;
        }
    }
    //是否转到 立即数
    if (cur >= '0' && cur <= '9')
    {
        clear_f = NUM;
    }
    // 是否转到 标识符
    if (cur >= 'a' && cur <= 'z' || cur >= 'A' && cur <= 'Z')
    {
        clear_f = ID;
    }
    //是否因空格结束当前字符串
    if (cur == ' ')
    {
        clear_f = ID;
    }
    //决定 状态转换
    if (clear_f != 0)
    {
        //结束当前字符串
        if (str != "")
            res[cur_r].push_back(make_pair("DE", str));
        str = "";
        //跳转
        return clear_f;
    }
    if (str != "")
    {
        res[cur_r].push_back(make_pair("DE", str));
        str = "";
    }

    str += cur;
    return DE;
}
int op_staus(char &cur, string &str, vector<vector<pair<string, string>>> &res, int &cur_r, vector<string> &error)
{
    static char de[] = {',', ';', '[', ']', '{', '}', '(', ')'};
    static char op[] = {'+', '-', '*', '/', '%', '=', '!', '<', '>', '&', '|'};
    int clear_f = 0;

    //是否转到 立即数
    if (cur >= '0' && cur <= '9')
    {
        clear_f = NUM;
    }
    // 是否转到 标识符
    if (cur >= 'a' && cur <= 'z' || cur >= 'A' && cur <= 'Z')
    {
        clear_f = ID;
    }
    // 是否转到 分隔符
    for (int i = 0; i < 8; i++)
    {
        if (cur == de[i])
        {
            clear_f = DE;
        }
    }
    //是否因空格结束当前字符串
    if (cur == ' ')
    {
        clear_f = OP;
    }

    //决定 状态转换
    if (clear_f != 0)
    {
        //结束当前字符串
        /*
        char old_c = str.back();
        if ((old_c == '=' || old_c == '!' || old_c == '<' || old_c == '>') && cur_r == '=' ||
            old_c == '&' && cur_r == '&' ||
            old_c == '|' && cur_r == '|')
        */
        if (str != "")
        {
            res[cur_r].push_back(make_pair("OP", str));
        }
        str = "";
        //跳转
        return clear_f;
    }
    str += cur;
    return OP;
}

int num_staus(char &cur, string &str, vector<vector<pair<string, string>>> &res, int &cur_r, vector<string> &error)
{
    static char de[] = {',', ';', '[', ']', '{', '}', '(', ')'};
    static char op[] = {'+', '-', '*', '/', '%', '=', '!', '<', '>', '&', '|'};
    int clear_f = 0;

    // 是否转到 分隔符
    for (int i = 0; i < 8; i++)
    {
        if (cur == de[i])
        {
            clear_f = DE;
        }
    }
    //是否转到 运算符
    for (int i = 0; i < 11; i++)
    {
        if (cur == op[i])
        {
            clear_f = OP;
        }
    }
    // 是否转到 标识符（获得出错的标识符）
    if (cur >= 'a' && cur <= 'z' || cur >= 'A' && cur <= 'Z')
    {
        return ID;
    }
    //是否因空格结束当前字符串
    if (cur == ' ')
    {
        clear_f = ID;
    }

    //决定 状态转换
    if (clear_f != 0)
    {
        if (str != "")
        {
            res[cur_r].push_back(make_pair("NUM", str));
            if (str[0] == '0' && str.size() > 1)
            {
                string te = "error : " + to_string(cur_r) + " row , illegal decimal  < " + str + " >";
                error.push_back(te);
            }
        }

        str = "";
        //跳转
        return clear_f;
    }
    str += cur;
    return NUM;
}
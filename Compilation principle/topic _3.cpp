#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

string end_c[] = {"id", "+", "-", "/", "*", "(", ")", "~"};
string no_end_c[] = {"E", "E`", "T", "T`", "F", "A", "M"};

bool is_end_char(string &te);
void find_frist(vector<pair<string, vector<string>>> &G, map<string, vector<string>> &FRIST, string &tar_c, vector<string> &tar_vec);
void find_follow(vector<pair<string, vector<string>>> &G, map<string, vector<string>> &FOLLOW, map<string, vector<string>> &FRIST);
void find_select(vector<pair<string, vector<string>>> &G, map<string, vector<string>> &FOLLOW,
                 map<string, vector<string>> &FRIST, vector<vector<string>> &SELECT);
void cout_set(map<string, vector<string>> &FOLLOW, map<string, vector<string>> &FRIST, vector<vector<string>> &SELECT);
void analysis(vector<string> &tar_str, map<pair<string, string>, int> &ANA_TABLE, vector<pair<string, vector<string>>> &G);

int main()
{
    // 初始化文法
    vector<pair<string, vector<string>>> G;
    G.resize(12);
    G[0] = make_pair("E", vector<string>{"T", "E`"});
    G[1] = make_pair("E`", vector<string>{"A", "T", "E`"});
    G[2] = make_pair("E`", vector<string>{"~"});
    G[3] = make_pair("T", vector<string>{"F", "T`"});
    G[4] = make_pair("T`", vector<string>{"M", "F", "T`"});
    G[5] = make_pair("T`", vector<string>{"~"});
    G[6] = make_pair("F", vector<string>{"(", "E", ")"});
    G[7] = make_pair("F", vector<string>{"id"});
    G[8] = make_pair("A", vector<string>{"+"});
    G[9] = make_pair("A", vector<string>{"-"});
    G[10] = make_pair("M", vector<string>{"*"});
    G[11] = make_pair("M", vector<string>{"/"});

    // 读入
    vector<string> tar_str;
    string token;
    while (getline(cin, token, ' '))
    {
        if (token[1] == 'I')
        {
            tar_str.push_back("id");
        }
        if (token[1] == 'O')
        {
            tar_str.push_back(string(1, token[4]));
        }
    }
    tar_str.push_back("$");

    // 输出转换后的字符串
    cout << "converted string  :  ";
    for (int i = 0; i < tar_str.size(); i++)
    {
        cout << tar_str[i] << " ";
    }
    cout << endl;

    // 计算frist集
    map<string, vector<string>> FRIST;
    for (int i = 0; i < 8; i++)
    {
        FRIST[end_c[i]] = vector<string>{end_c[i]};
    }
    for (int i = 6; i >= 0; i--)
    {
        vector<string> te;
        find_frist(G, FRIST, no_end_c[i], te);
        FRIST[no_end_c[i]] = te;
    }

    // 计算follow集
    map<string, vector<string>> FOLLOW;
    for (int i = 6; i >= 0; i--)
    {
        FOLLOW[no_end_c[i]] = vector<string>{};
    }
    FOLLOW["E"].push_back("$");
    find_follow(G, FOLLOW, FRIST);
    find_follow(G, FOLLOW, FRIST);

    // 计算select集
    vector<vector<string>> SELECT;
    find_select(G, FOLLOW, FRIST, SELECT);

    // 输出三个集合
    cout_set(FOLLOW, FRIST, SELECT);

    // 构建分析表
    map<pair<string, string>, int> ANA_TABLE;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < SELECT[i].size(); j++)
        {
            ANA_TABLE[make_pair(G[i].first, SELECT[i][j])] = i;
        }
    }

    // 分析过程
    analysis(tar_str, ANA_TABLE, G);

    return 0;
}

void analysis(vector<string> &tar_str, map<pair<string, string>, int> &ANA_TABLE, vector<pair<string, vector<string>>> &G)
{
    int wight = tar_str.size() * 1.5;
    vector<string> ST;
    ST.push_back("$");
    ST.push_back("E");
    int pos = 0;
    int j = 1;
    cout << setiosflags(ios::right) << setw(2) << 0 << " : ";
    string te;
    for (int i = 0; i < pos; i++)
    {
        te += tar_str[i];
    }
    cout << setiosflags(ios::left) << setw(wight) << te << "  ";
    te = "";
    for (int i = ST.size() - 1; i >= 0; i--)
    {
        te += ST[i];
    }
    cout << setiosflags(ios::right) << setw(wight) << te << "  ";
    te = "";
    for (int i = pos; i < tar_str.size(); i++)
    {
        te += tar_str[i];
    }
    cout << setiosflags(ios::right) << setw(wight) << te << "  " << endl;

    while (ST.back() != "$")
    {
        int f = 0;
        int order;
        // 匹配
        if (is_end_char(ST.back()))
        {
            if (ST.back() == tar_str[pos])
            {
                ST.pop_back();
                pos++;
                f = 1;
            }
            else
            {
                cout << "string illegal " << endl;
                return;
            }
        }
        else //输出
        {
            string te = ST.back();
            ST.pop_back();
            if (ANA_TABLE.find(make_pair(te, tar_str[pos])) == ANA_TABLE.end())
            {
                cout << "string illegal " << endl;
                return;
            }
            order = ANA_TABLE[make_pair(te, tar_str[pos])];
            for (int i = G[order].second.size() - 1; i >= 0; i--)
            {
                ST.push_back(G[order].second[i]);
            }
            if (ST.back() == "~")
            {
                ST.pop_back();
            }
        }
        // 打印结果
        cout << setiosflags(ios::right) << setw(2) << j << " : ";
        cout << resetiosflags(ios::right);
        te = "";
        for (int i = 0; i < pos; i++)
        {
            te += tar_str[i];
        }
        cout << setiosflags(ios::left) << setw(wight) << te << "  ";
        te = "";
        for (int i = ST.size() - 1; i >= 0; i--)
        {
            te += ST[i];
        }
        cout << setiosflags(ios::right) << setw(wight) << te << "  ";
        te = "";
        for (int i = pos; i < tar_str.size(); i++)
        {
            te += tar_str[i];
        }
        cout << setiosflags(ios::right) << setw(wight) << te << "   ";
        if (f == 0) // 输出情况
        {
            cout << "out:  ";
            cout << setw(2) << G[order].first << " -> ";
            for (int i = 0; i < G[order].second.size(); i++)
            {
                cout << G[order].second[i];
            }
            cout << endl;
        }
        else // 匹配情况
        {
            cout << "match: " << tar_str[pos - 1] << endl;
        }
        j++;
    }
    cout << endl;
    cout << "Analysis complete" << endl;
}

// 计算frist集
void find_frist(vector<pair<string, vector<string>>> &G, map<string, vector<string>> &FRIST, string &tar_c, vector<string> &tar_vec)
{
    for (int i = 0; i < G.size(); i++)
    {
        if (G[i].first == tar_c)
        {
            int f = 0;
            for (int j = 0; j < G[i].second.size(); j++)
            {
                string te = G[i].second[j];
                tar_vec.insert(tar_vec.end(), FRIST[te].begin(), FRIST[te].end());
                if (FRIST[te].back() != "~")
                {
                    f = 1;
                    break;
                }
                else
                {
                    tar_vec.pop_back();
                }
            }
            if (f == 0)
            {
                tar_vec.push_back("~");
            }
        }
    }
    sort(tar_vec.begin(), tar_vec.end());
    tar_vec.erase(unique(tar_vec.begin(), tar_vec.end()), tar_vec.end());
}

// 计算follow集
void find_follow(vector<pair<string, vector<string>>> &G, map<string, vector<string>> &FOLLOW, map<string, vector<string>> &FRIST)
{
    for (int i = 11; i >= 0; i--)
    {
        for (int j = 0; j < G[i].second.size(); j++)
        {
            string te = G[i].second[j];

            if (!is_end_char(te) && te != "~")
            {
                int f = 0;
                for (int k = j + 1; k < G[i].second.size(); k++)
                {
                    string te2 = G[i].second[k];
                    FOLLOW[te].insert(FOLLOW[te].end(), FRIST[te2].begin(), FRIST[te2].end());
                    if (FOLLOW[te].back() != "~")
                    {
                        f = 1;
                        break;
                    }
                    else
                    {
                        FOLLOW[te].pop_back();
                    }
                }
                if (f == 0 && te != G[i].first)
                {
                    FOLLOW[te].insert(FOLLOW[te].end(), FOLLOW[G[i].first].begin(), FOLLOW[G[i].first].end());
                }
                sort(FOLLOW[te].begin(), FOLLOW[te].end());
                FOLLOW[te].erase(unique(FOLLOW[te].begin(), FOLLOW[te].end()), FOLLOW[te].end());
                f = 1;
            }
        }
    }
}

// 计算select集
void find_select(vector<pair<string, vector<string>>> &G, map<string, vector<string>> &FOLLOW,
                 map<string, vector<string>> &FRIST, vector<vector<string>> &SELECT)
{
    for (int i = 0; i < 12; i++)
    {
        vector<string> vec;
        string te = G[i].second[0];
        vec.insert(vec.end(), FRIST[te].begin(), FRIST[te].end());
        if (vec.back() == "~")
        {
            vec.pop_back();
            vec.insert(vec.end(), FOLLOW[G[i].first].begin(), FOLLOW[G[i].first].end());
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        SELECT.push_back(vec);
    }
}

// 输出 FRIST 与 FOLLOW 与 SELECT集
void cout_set(map<string, vector<string>> &FOLLOW,
              map<string, vector<string>> &FRIST, vector<vector<string>> &SELECT)
{
    cout << endl;
    cout << "------------------" << endl;
    cout << "FRIST : " << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << setw(4) << no_end_c[i] << " :  ";
        for (int j = 0; j < FRIST[no_end_c[i]].size(); j++)
        {
            cout << setw(2) << FRIST[no_end_c[i]][j] << "  ";
        }
        cout << endl;
    }
    cout << "------------------" << endl;
    cout << "FOLLOW : " << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << setw(4) << no_end_c[i] << " :  ";
        for (int j = 0; j < FOLLOW[no_end_c[i]].size(); j++)
        {
            cout << setw(2) << FOLLOW[no_end_c[i]][j] << "  ";
        }
        cout << endl;
    }
    cout << "------------------" << endl;
    cout << "SELECT : " << endl;
    for (int i = 0; i < 12; i++)
    {
        cout << i << " : ";

        for (int j = 0; j < SELECT[i].size(); j++)
        {
            cout << setw(2) << SELECT[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "------------------" << endl;
    cout << endl;
}

// 是否是终结符号
bool is_end_char(string &te)
{
    for (int i = 0; i < 7; i++)
    {
        if (te == end_c[i])
        {
            return true;
        }
    }
    return false;
}

//  <ID,a1> <OP,/> <ID,a2> <OP,*> <ID,a3> <OP,+> <ID,a4> <OP,-> <ID,a5> <OP,-> <ID,a6> <OP,/> <ID,a7>
//  <ID,a2> <OP,*> <ID,a3> <OP,+> <ID,a4>

//  <ID,a2> <OP,*> <ID,a3> <OP,+> <OP,+> <ID,a4>
//  <ID,a2> <OP,*> <ID,a3>  <ID,a4>
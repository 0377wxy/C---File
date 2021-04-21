#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#define DATA_NUM 500
#define DATA_PRA 350
#define FL 1
// #define ALPHA 2
using namespace std;

int main()
{
    vector<vector<double>> data;
    vector<double> value;
    vector<string> name;
    // 读取数据
    ifstream temp;
    temp.open("D:\\Program_file\\C-File\\homework\\Chapter-1\\housing.txt", ios::in);
    if (temp.is_open() == 0)
        return 0;
    string temp_s;
    vector<double> temp_v;
    double temp_d;
    name.push_back("x0");
    for (int i = 1; i < 15; i++)
    {
        temp >> temp_s;
        name.push_back(temp_s);
    }
    for (int i = 0; i < DATA_NUM + 1; i++)
    {
        data.push_back(temp_v);
        data[i].push_back(1);
        for (int j = 0; j < 13; j++)
        {
            temp >> temp_d;
            data[i].push_back(temp_d);
        }
        temp >> temp_d;
        value.push_back(temp_d);
    }
    temp.close();
    cout << "----读取完成----" << endl;

    //求x,y的平均值

    double value_ave;
    for (int i = 0; i < DATA_NUM; i++)
    {
        value_ave += value[i];
    }
    value_ave = value_ave / DATA_NUM;

    vector<double> data_ave(14);
    for (int i = 0; i < DATA_NUM; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            data_ave[j] += data[i][j];
        }
    }
    for (int i = 0; i < 14; i++)
    {
        data_ave[i] = data_ave[i] / DATA_NUM;
    }

    //求皮尔逊相关系数

    vector<double> r2(14);
    vector<double> r3(14);
    vector<double> r(14);
    vector<double> r1(14);
    for (int i = 0; i < DATA_NUM; i++)
    {
        for (int j = 1; j < 14; j++)
        {
            r1[j] += (data[i][j] - data_ave[j]) * (value[i] - value_ave);

            r2[j] += (data[i][j] - data_ave[j]) * (data[i][j] - data_ave[j]);
            r3[j] += (value[i] - value_ave) * (value[i] - value_ave);
        }
    }

    for (int j = 1; j < 14; j++)
    {
        r[j] = r1[j] / (sqrt(r2[j]) * sqrt(r3[j]));
    }

    for (int i = 1; i < 14; i++)
    {
        cout << name[i] << " : " << r[i] << endl;
    }
    cout << "----相关系数计算完成----" << endl;
    // 挑选相关性高的四个因素
    r[0] = 1;
    int flag_r[5] = {0};
    for (int i = 1; i < 5; i++)
    {
        double mi = 0;
        int f = 0;
        for (int j = 1; j < 14; j++)
        {
            if (fabs(r[j]) > fabs(mi) && fabs(r[j]) < fabs(r[flag_r[i - 1]]))
            {

                mi = r[j];
                f = j;
            }
        }
        flag_r[i] = f;
    }
    r[0] = 0;
    for (int i = 0; i < 5; i++)
    {
        cout << name[flag_r[i]] << " : " << r[flag_r[i]] << endl;
    }
    cout << "----x挑选完成-----" << endl;
    vector<double> data_min(14);
    vector<double> data_max(14);
    for (int i = 0; i < 14; i++)
    {
        data_min[i] = INT_MAX;
        data_max[i] = INT_MIN;
    }
    for (int i = 0; i < DATA_NUM; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            if (data[i][j] > data_max[j])
            {
                data_max[j] = data[i][j];
            }
            if (data[i][j] < data_min[j])
            {
                data_min[j] = data[i][j];
            }
        }
    }
    for (int i = 0; i < DATA_NUM; i++)
    {
        for (int j = 1; j < 14; j++)
        {
            if (fabs(data[i][j] - data_ave[j]) < (data_max[j] - data_min[j]) / 8)
            {
                data[i][j] = data_ave[j];
            }
            data[i][j] = (data[i][j] - data_min[j]) / (data_max[j] - data_min[j]);
        }
    }
    cout << "----归一化完成----" << endl;

    // 梯度下降
    double weight[14];
    double weight_sum[14];
    double value_te[DATA_NUM] = {0};
    int n = 200;
    double ALPHA = 0.1;
    double rmse_t, rmse_t2;

    for (; ALPHA < 1; ALPHA += 0.05)
    {
        for (n = 3; n < 1200; n = n + 100)
        {

            for (int i = 0; i < 14; i++)
            {
                weight[i] = 1;
            }
            for (int i = 0; i < DATA_NUM; i++)
            {
                value_te[i] = 0;
            }
            int m = n;
            while (m--)
            {
                for (int i = 0; i < 14; i++)
                {
                    weight_sum[i] = 0;
                }
                for (int i = 0; i < DATA_PRA; i++)
                {
                    value_te[i] = 0;
                    for (int j = 0; j < 5; j++)
                    {
                        value_te[i] += weight[flag_r[j]] * data[i][flag_r[j]];
                    }
                    for (int j = 0; j < 5; j++)
                    {
                        weight_sum[flag_r[j]] += (value_te[i] - value[i]) * data[i][flag_r[j]];
                    }
                }
                for (int i = 0; i < 5; i++)
                {
                    weight[flag_r[i]] = weight[flag_r[i]] - ALPHA * weight_sum[flag_r[i]] / DATA_PRA;
                }
                /*

                if (m % 8 == 0)
                {
                    for (int i = 1; i < 5; i++)
                    {
                        cout << weight[flag_r[i]] << " ";
                    }
                    cout << endl;
                }

            }
            
            for (int i = 0; i < 14; i++)
            {
                cout << weight[i] << " ";
            }
            cout << endl;
            cout << "----训练结束----" << endl;
            */
            }
            rmse_t = 0;

            for (int i = 0; i < DATA_NUM - DATA_PRA; i++)
            {
                rmse_t2 = 0;
                for (int j = 0; j < 5; j++)
                {

                    rmse_t2 += weight[flag_r[j]] * data[i + DATA_PRA][flag_r[j]];
                }
                rmse_t = pow(rmse_t2 - value[i + DATA_PRA], 2);
            }
            cout << sqrt(rmse_t / (DATA_NUM - DATA_PRA)) << "  ";
        }
        cout << endl;
        for (int i = 0; i < 5; i++)
        {
            cout << weight[flag_r[i]] << " ";
        }
        cout << endl;
    }

    return 0;
}
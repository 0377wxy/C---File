
#include <iostream>
#include <vector>

#include <time.h>
using namespace std;

class Car
{
public:
    int num;
    time_t Time_of_arrival;
    time_t Storage_time;
    Car *next; // 仅在等待队列中使用
    Car(int n)
    {
        num = n;
        time(&Time_of_arrival);
        next = NULL;
    }
};

class Waiting_queue
{
public:
    Car *start;
    Car *end;
    int num;
    Waiting_queue()
    {
        start = NULL;
        end = NULL;
        num = 0;
    }
};

void Vehicle_arrived(vector<Car *> &garage, Waiting_queue *wait, int n) // 表示车辆到达情况
{
    int temp_num;
    cout << "请输入车牌号  到达时间(不必输入)" << endl;
    cin >> temp_num;                 // 读入车辆信息
    Car *temp_c = new Car(temp_num); // 创建车的对象

    if (garage.size() < n) // 库不满
    {
        temp_c->Storage_time = temp_c->Time_of_arrival; // 设置入库时间
        garage.push_back(temp_c);                       // 入库
    }
    else // 库满
    {
        if (wait->num == 0) // 无车等待
        {
            wait->start = temp_c;
            wait->end = temp_c;
        }
        else // 有车等待
        {
            wait->end->next = temp_c;
            wait->end = wait->end->next;
        }
        wait->num++;
    }
}

void Vehicle_leaving(vector<Car *> &garage, Waiting_queue *wait, int nu) // 车辆离开
{
    Car *temp = garage.back();
    vector<Car *> temp_garage;

    while (temp->num != nu) // 在目标车辆之后的车辆必须先退出停车场让路
    {
        temp_garage.push_back(temp);
        garage.pop_back();
        temp = garage.back();
    }
    time_t t;
    time(&t);

    cout << "车牌号  停车时长" << endl;
    cout << temp->num << " " << difftime(t, temp->Storage_time) << "s  "
         << "费用： " << 0.1 * difftime(t, temp->Storage_time) << endl;
    garage.pop_back();

    while (temp_garage.size() != 0) // 目标车辆之后的车辆停回停车场中
    {
        garage.push_back(temp_garage.back());
        temp_garage.pop_back();
    }

    if (wait->num != 0) // 若车在等待，则第一辆入库
    {
        wait->start->Storage_time = t;
        garage.push_back(wait->start);
        wait->start = wait->start->next;
        wait->num--;
    }
}

void show_Waiting_situation(vector<Car *> &garage, Waiting_queue *wait) // 显示出停车场内及便道上的停车情况
{
    Car *temp = wait->start;
    cout << "便道上的等待情况：" << endl;
    cout << "车牌号  到达时间 " << endl;
    while (temp != NULL)
    {
        cout << temp->num << " " << ctime(&(temp->Time_of_arrival)) << endl;
        temp = temp->next;
    }
    cout << "车库内的情况：" << endl;
    cout << "车牌号  到达时间 入库时间" << endl;
    for (int i = 0; i < garage.size(); i++)
    {
        cout << garage[i]->num << " " << ctime(&(garage[i]->Time_of_arrival)) << " " << ctime(&(garage[i]->Storage_time)) << endl;
    }
}

int main()
{
    cout << "请输入车库大小" << endl;
    int n; // 车库大小；
    cin >> n;

    vector<Car *> garage;
    Waiting_queue *wait = new Waiting_queue();

    int f;
    while (1)
    {
        cout << "请输入请求功能(1:车辆到达；2:车辆离开；3:停车情况；4:退出系统)" << endl;
        cin >> f;
        if (f == 1)
        {
            Vehicle_arrived(garage, wait, n);
        }
        else if (f == 2)
        {
            cout << "请输入出库的车牌号" << endl;
            int a;
            cin >> a;
            Vehicle_leaving(garage, wait, a);
        }
        else if (f == 3)
        {
            show_Waiting_situation(garage, wait);
        }
        else
        {
            break;
        }
    }
    return 0;
}
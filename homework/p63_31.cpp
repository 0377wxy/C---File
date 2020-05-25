#include <iostream>
using namespace std;

struct Time
{
    int year, month, day, hour, minute, second;
};
int main()
{
    cout << "请输入：年 月 日 时 分 秒 （相互间有空格）" << endl;
    Time time;
    cin >> time.year >> time.month >> time.day >> time.hour >> time.minute >> time.second;
    cout << time.year << "年" << time.month << "月" << time.day << "日" << time.hour << "时" << time.minute << "分" << time.second << "秒" << endl;
    return 0;
}
#include <iostream>
TabNine::sem
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;
int main()
{
    vector<int> text;
    istream_iterator<int> is(cin); //绑定标准输入装置
    istream_iterator<int> eof;     //定义输入结束位置
    copy(is, eof, back_inserter(text));
    sort(text.begin(), text.end());
    cout << text.size() << endl;
    ostream_iterator<int> os(cout, ", "); //绑定标准输出装置
    copy(text.begin(), text.end(), os);
    
    return 0;
}
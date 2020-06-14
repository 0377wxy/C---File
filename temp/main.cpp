#include <iostream>
#include <cstring>
using	namespace	std;

class	CString
{
public :
    CString (); //无参构造，构造空串
    CString (const char *str); //传统字符串构造
    ~CString () //析构函数，释放字符串占用的资源
    {
        delete [] m_pBuffer;
    }
    CString (const CString &rhs); //拷贝构造
    CString (CString &&rhs) noexcept; //移动构造
    CString & operator = (const CString &rhs); //赋值运算符重载
    CString & operator = (CString &&rhs) noexcept; //移动赋值

    friend ostream & operator << (ostream &out, const CString &rhs);  //插入运算符重载
    friend	CString operator + (const CString &S1, const CString &S2); //字符串连接
    CString   substr (int start, int len); //取子串
    char& operator [] (int index);  //下标运算符，可用于左值
    const char& operator [] (int index) const; //下标运算符，只能可用于右值
    operator const char * () const; //转换运算符
private :
    explicit CString (int length)  //构造函数，便于＋、取子串等运算
    {
        m_pBuffer = new char [length +1];
        m_length = length;
    }
    char	*m_pBuffer;  //存放字符串内容
    int		m_length;    //字符串长度，便于＋运算；也可不设置
};

//无参构造，构造空串
CString::CString ()
{
    m_length = 0;
    m_pBuffer = new char [1];
    m_pBuffer [0] = '\0';
}

//传统字符串构造
CString::CString (const char *str)
{
    m_length = strlen (str);
    m_pBuffer = new char [m_length +1];
    strcpy (m_pBuffer, str);
}

//拷贝构造
CString::CString (const CString &rhs) : m_pBuffer (NULL)
{
    m_length = rhs.m_length ;
    m_pBuffer = new char [m_length +1];
    strcpy (m_pBuffer, rhs.m_pBuffer);
}

CString::CString (CString &&rhs) noexcept//移动构造
{
    m_length = rhs.m_length ;
    m_pBuffer = rhs.m_pBuffer;
    rhs.m_pBuffer = NULL; //rhs资源已转移，不可在析构时释放、
}

//赋值运算符重载
CString & CString::operator = (const CString &rhs)
{
    CString   tmp (rhs);
    swap (m_pBuffer, tmp.m_pBuffer);
    swap (m_length, tmp.m_length);

    return *this;  //返回当前对象引用，便于连续赋值
}

CString & CString::operator = (CString &&rhs) noexcept//移动赋值
{
    //利用STLswap交换2个对象值，当前对象原资源交rhs析构时释放
    swap (m_pBuffer, rhs.m_pBuffer);
    swap (m_length, rhs.m_length);
    return *this;
}
//取子串
CString   CString::substr (int start, int len)
{
    CString	tempStr (len);
    strncpy (tempStr.m_pBuffer, m_pBuffer+start, len);
    tempStr.m_pBuffer [len] = '\0';
    return tempStr;
}

//插入运算符重载
ostream & operator << (ostream &out, const CString &rhs)
{
    out << rhs.m_pBuffer;
    return out;
}

//字符串连接
CString operator + (const CString &S1, const CString &S2)
{
    CString	tempStr (S1.m_length + S2.m_length);
    strcpy (tempStr.m_pBuffer, S1.m_pBuffer);
    strcat (tempStr.m_pBuffer, S2.m_pBuffer );
    return tempStr;
}

//下标运算符，只能可用于右值
const char& CString::operator [] (int index) const
{
    if (index < 0 || index > m_length)
    {
        static	char	c;
        return c;
    }
    return m_pBuffer [index];
}

//下标运算符，可用于左值
char& CString::operator [] (int index)
{
    if (index < 0 || index > m_length)
    {
        static	char	c;
        return c;
    }
    return m_pBuffer [index];
}

//转换运算符
CString::operator const char * () const
{
    return	m_pBuffer;
}

//测试用例，命令解释器
int main()
{
    char	bufs1 [256], bufs2 [256];

    cin >> bufs1 >> bufs2;
    CString	s [4] {CString (bufs1), CString (bufs2)};

    char  op;
    int	i,j,k,l,pos;

    while (cin>> op)
    {
        switch (op)
        {
        case 'P':
            cin >> i;
            cout << s [i-1] << endl;
            break;
        case 'A':
            cin >> i >> j;
            s [j-1] = s[i-1];
            break;
        case 'C':
            cin >> i >> j >> k;
            s [k-1] = s [i-1] + s[j-1];
            break;
        case 'F':
            cin >> i >> pos >> l >> k ;
            s [k-1] = s [i-1].substr (pos, l);
            break;
        }
    }
}

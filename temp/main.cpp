#include <iostream>
#include <cstring>
using	namespace	std;

class	CString
{
public :
    CString (); //�޲ι��죬����մ�
    CString (const char *str); //��ͳ�ַ�������
    ~CString () //�����������ͷ��ַ���ռ�õ���Դ
    {
        delete [] m_pBuffer;
    }
    CString (const CString &rhs); //��������
    CString (CString &&rhs) noexcept; //�ƶ�����
    CString & operator = (const CString &rhs); //��ֵ���������
    CString & operator = (CString &&rhs) noexcept; //�ƶ���ֵ

    friend ostream & operator << (ostream &out, const CString &rhs);  //�������������
    friend	CString operator + (const CString &S1, const CString &S2); //�ַ�������
    CString   substr (int start, int len); //ȡ�Ӵ�
    char& operator [] (int index);  //�±����������������ֵ
    const char& operator [] (int index) const; //�±��������ֻ�ܿ�������ֵ
    operator const char * () const; //ת�������
private :
    explicit CString (int length)  //���캯�������ڣ���ȡ�Ӵ�������
    {
        m_pBuffer = new char [length +1];
        m_length = length;
    }
    char	*m_pBuffer;  //����ַ�������
    int		m_length;    //�ַ������ȣ����ڣ����㣻Ҳ�ɲ�����
};

//�޲ι��죬����մ�
CString::CString ()
{
    m_length = 0;
    m_pBuffer = new char [1];
    m_pBuffer [0] = '\0';
}

//��ͳ�ַ�������
CString::CString (const char *str)
{
    m_length = strlen (str);
    m_pBuffer = new char [m_length +1];
    strcpy (m_pBuffer, str);
}

//��������
CString::CString (const CString &rhs) : m_pBuffer (NULL)
{
    m_length = rhs.m_length ;
    m_pBuffer = new char [m_length +1];
    strcpy (m_pBuffer, rhs.m_pBuffer);
}

CString::CString (CString &&rhs) noexcept//�ƶ�����
{
    m_length = rhs.m_length ;
    m_pBuffer = rhs.m_pBuffer;
    rhs.m_pBuffer = NULL; //rhs��Դ��ת�ƣ�����������ʱ�ͷš�
}

//��ֵ���������
CString & CString::operator = (const CString &rhs)
{
    CString   tmp (rhs);
    swap (m_pBuffer, tmp.m_pBuffer);
    swap (m_length, tmp.m_length);

    return *this;  //���ص�ǰ�������ã�����������ֵ
}

CString & CString::operator = (CString &&rhs) noexcept//�ƶ���ֵ
{
    //����STLswap����2������ֵ����ǰ����ԭ��Դ��rhs����ʱ�ͷ�
    swap (m_pBuffer, rhs.m_pBuffer);
    swap (m_length, rhs.m_length);
    return *this;
}
//ȡ�Ӵ�
CString   CString::substr (int start, int len)
{
    CString	tempStr (len);
    strncpy (tempStr.m_pBuffer, m_pBuffer+start, len);
    tempStr.m_pBuffer [len] = '\0';
    return tempStr;
}

//�������������
ostream & operator << (ostream &out, const CString &rhs)
{
    out << rhs.m_pBuffer;
    return out;
}

//�ַ�������
CString operator + (const CString &S1, const CString &S2)
{
    CString	tempStr (S1.m_length + S2.m_length);
    strcpy (tempStr.m_pBuffer, S1.m_pBuffer);
    strcat (tempStr.m_pBuffer, S2.m_pBuffer );
    return tempStr;
}

//�±��������ֻ�ܿ�������ֵ
const char& CString::operator [] (int index) const
{
    if (index < 0 || index > m_length)
    {
        static	char	c;
        return c;
    }
    return m_pBuffer [index];
}

//�±����������������ֵ
char& CString::operator [] (int index)
{
    if (index < 0 || index > m_length)
    {
        static	char	c;
        return c;
    }
    return m_pBuffer [index];
}

//ת�������
CString::operator const char * () const
{
    return	m_pBuffer;
}

//�������������������
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

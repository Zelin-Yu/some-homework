#include <iostream>
#include <string>

using namespace std;

/*
大浮点数类(只支持非负数)
存储大浮点数,定义加法操作,格式化输出
*/
class BigFloat
{
private:
	string integer;		//整数部分
	string decimal;		//小数部分

	/*
	对齐,即在较短的串上补0,方便加法操作
	参数为待对齐的字符串和需要补0的个数
	*/
	string align(string s, int n)
	{
		for (int i = 0; i < n; i++)
		{
			s += '0';
		}

		return s;
	}

	/*
	字符串转置
	*/
	string reverse(string s)
	{
		int len = s.length();
		for (int i = 0; i < len / 2; i++)
		{
			char t = s[i];
			s[i] = s[len - 1 - i];
			s[len - 1 - i] = t;
		}

		return s;
	}

	/*
	浮点数加法的辅助函数,对字符串从低位向高位加(下标小端为低位)
	参数为加数和进位(默认为0)
	返回结果
	*/
	string add(string a, string b, int carry = 0)
	{
		string result;
		int len = a.length();
		for (int i = 0; i < len; i++)
		{
			char c1 = a[i] - '0', c2 = b[i] - '0';
			int r = c1 + c2 + carry;
			if (r >= 10)
			{
				result += r - 10 + '0';
				carry = 1;
			}
			else
			{
				result += r + '0';
				carry = 0;
			}
		}

		if (carry == 1)
		{
			result += '1';
		}

		return result;
	}

	/*
	浮点数加法的辅助函数,小数部分相加
	参数为第二个加数的小数部分
	*/
	string addDecimal(string bd)
	{
		int len1 = decimal.length(), len2 = bd.length();
		string d = decimal;

		//先补0
		if (len1 > len2)
		{
			bd = align(bd, len1 - len2);
		}
		else
		{
			d = align(decimal, len2 - len1);
		}

		//再转置
		bd = reverse(bd);
		d = reverse(d);

		//相加之后再转置过来
		return reverse(add(d, bd));
	}

	/*
	浮点数加法的辅助函数,整数部分相加
	参数为第二个加数的整数部分和来自小数部分加法进位
	*/
	string addInteger(string bi, int carry)
	{
		int len1 = integer.length(), len2 = bi.length();
		string i = integer;

		//先转置
		i = reverse(i);
		bi = reverse(bi);

		//再补0
		if (len1 > len2)
		{
			bi = align(bi, len1 - len2);
		}
		else
		{
			i = align(i, len2 - len1);
		}

		//相加之后再转置过来
		return reverse(add(i, bi, carry));
	}

public:
	
	/*
	分别将整数部分和小数部分作为构造函数参数
	*/
	BigFloat(string i, string d)
	{
		integer = i;
		decimal = d;
	}

	/*
	将整个浮点数作为参数
	*/
	BigFloat(string f)
	{
		size_t pos = f.find('.');
		if (pos == string::npos)
		{
			integer = f;
			decimal = "0";		//若没有小数点,小数部分为0
		}
		else
		{
			integer = f.substr(0, pos);
			decimal = f.substr(pos + 1);
		}
	}

	~BigFloat() { }

	/*
	加法函数 重载+
	*/
	BigFloat operator+(BigFloat &b)
	{
		int len1 = decimal.length(), len2 = b.decimal.length();
		int maxLen = len1 > len2 ? len1 : len2;
		string d = addDecimal(b.decimal);

		//小数部分相加
		//如果结果比较长加数长，说明小数部分有进位
		int carry = 0;
		if (d.length() > maxLen)
		{
			carry = 1;
			d = d.substr(1);
		}

		//去除小数部分尾部多余0(若为0,则留一个)
		int index;
		for (index = d.length() - 1; index > 0; index--)
		{
			if (d[index] != '0')
			{
				break;
			}
		}
		d = d.substr(0, index + 1);

		//整数部分相加
		string i = addInteger(b.integer, carry);

		return BigFloat(i, d);
	}

	//重载<<
	friend ostream &operator<<(ostream &out, BigFloat f);

	//friend ostream &operator<<(ostream &out, BigFloat &f);
};

ostream &operator<<(ostream &out, BigFloat f)
{
	out << f.integer;

	//判断是否有小数部分
	if (f.decimal != "0")
	{
		out << '.' << f.decimal;
	}

	return out;
}

int main()
{
	string f1, f2;
	cin >> f1 >> f2;
	BigFloat a(f1), b(f2);
	cout << a + b << endl;

	return 0;
}

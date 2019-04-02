#include <iostream>
#include <string>

using namespace std;

/*
�󸡵�����(ֻ֧�ַǸ���)
�洢�󸡵���,����ӷ�����,��ʽ�����
*/
class BigFloat
{
private:
	string integer;		//��������
	string decimal;		//С������

	/*
	����,���ڽ϶̵Ĵ��ϲ�0,����ӷ�����
	����Ϊ��������ַ�������Ҫ��0�ĸ���
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
	�ַ���ת��
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
	�������ӷ��ĸ�������,���ַ����ӵ�λ���λ��(�±�С��Ϊ��λ)
	����Ϊ�����ͽ�λ(Ĭ��Ϊ0)
	���ؽ��
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
	�������ӷ��ĸ�������,С���������
	����Ϊ�ڶ���������С������
	*/
	string addDecimal(string bd)
	{
		int len1 = decimal.length(), len2 = bd.length();
		string d = decimal;

		//�Ȳ�0
		if (len1 > len2)
		{
			bd = align(bd, len1 - len2);
		}
		else
		{
			d = align(decimal, len2 - len1);
		}

		//��ת��
		bd = reverse(bd);
		d = reverse(d);

		//���֮����ת�ù���
		return reverse(add(d, bd));
	}

	/*
	�������ӷ��ĸ�������,�����������
	����Ϊ�ڶ����������������ֺ�����С�����ּӷ���λ
	*/
	string addInteger(string bi, int carry)
	{
		int len1 = integer.length(), len2 = bi.length();
		string i = integer;

		//��ת��
		i = reverse(i);
		bi = reverse(bi);

		//�ٲ�0
		if (len1 > len2)
		{
			bi = align(bi, len1 - len2);
		}
		else
		{
			i = align(i, len2 - len1);
		}

		//���֮����ת�ù���
		return reverse(add(i, bi, carry));
	}

public:
	
	/*
	�ֱ��������ֺ�С��������Ϊ���캯������
	*/
	BigFloat(string i, string d)
	{
		integer = i;
		decimal = d;
	}

	/*
	��������������Ϊ����
	*/
	BigFloat(string f)
	{
		size_t pos = f.find('.');
		if (pos == string::npos)
		{
			integer = f;
			decimal = "0";		//��û��С����,С������Ϊ0
		}
		else
		{
			integer = f.substr(0, pos);
			decimal = f.substr(pos + 1);
		}
	}

	~BigFloat() { }

	/*
	�ӷ����� ����+
	*/
	BigFloat operator+(BigFloat &b)
	{
		int len1 = decimal.length(), len2 = b.decimal.length();
		int maxLen = len1 > len2 ? len1 : len2;
		string d = addDecimal(b.decimal);

		//С���������
		//�������Ƚϳ���������˵��С�������н�λ
		int carry = 0;
		if (d.length() > maxLen)
		{
			carry = 1;
			d = d.substr(1);
		}

		//ȥ��С������β������0(��Ϊ0,����һ��)
		int index;
		for (index = d.length() - 1; index > 0; index--)
		{
			if (d[index] != '0')
			{
				break;
			}
		}
		d = d.substr(0, index + 1);

		//�����������
		string i = addInteger(b.integer, carry);

		return BigFloat(i, d);
	}

	//����<<
	friend ostream &operator<<(ostream &out, BigFloat f);

	//friend ostream &operator<<(ostream &out, BigFloat &f);
};

ostream &operator<<(ostream &out, BigFloat f)
{
	out << f.integer;

	//�ж��Ƿ���С������
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

#include <iostream>
#include <string>

using namespace std;

//���ȼ����壬���ȼ����������
//_L:���ϣ�ͬ��������ߵ�����
enum priority
{
	ADD, ADD_L, MUL, MUL_L
};

/*
��ȡ��׺���ʽ
�Ӻ���ǰ,���õ������opʱ,�ݹ��ȡ�����ӱ��ʽ�������
subExp = leftExp op rightExp���ӱ��ʽ��Ҫ�ȼ���,��()��
�Ƿ��ȼ���ͨ�����ȼ��ж�:�ݹ��ϲ�ı��ʽop'���ȼ���op��ͼ�()��
����һ�ɲ���()
����:��׺���ʽ(����,��ΪҪ�ı�)����ǰ���ȼ�(���Ǽ������ӱ��ʽ����_L)
������׺���ʽ
*/
string exp(string &postfixExp, int priority = 0)
{
	int len = postfixExp.length();
	char op = postfixExp[len - 1];
	postfixExp = postfixExp.substr(0, len - 1);	//�����ȥ����ĩһ���ַ�

	string rightExp, leftExp, subExp;
	switch (op)
	{
	case '+':
	case '-':
		rightExp = exp(postfixExp, ADD_L);
		leftExp = exp(postfixExp, ADD);
		subExp = leftExp + op + rightExp;
		if (priority > ADD)
		{
			return '(' + subExp + ')';
		}
		return subExp;

	case '*':
	case '/':
		rightExp = exp(postfixExp, MUL_L);
		leftExp = exp(postfixExp, MUL);
		subExp = leftExp + op + rightExp;
		if (priority > MUL)
		{
			return '(' + subExp + ')';
		}
		return subExp;

	default:
		string num;
		num += op;
		//���־����ӱ��ʽ
		return num;
		break;
	}
}

int main()
{
	string postfixExp;
	cin >> postfixExp;
	cout << exp(postfixExp) << endl;

	return 0;
}
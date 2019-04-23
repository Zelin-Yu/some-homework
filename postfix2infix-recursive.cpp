#include <iostream>
#include <string>

using namespace std;

//优先级定义，优先级大的先运算
//_L:左结合，同级运算左边的先算
enum priority
{
	ADD, ADD_L, MUL, MUL_L
};

/*
获取中缀表达式
从后往前,当得到运算符op时,递归获取左右子表达式，结果是
subExp = leftExp op rightExp。子表达式若要先计算,加()。
是否先计算通过优先级判断:递归上层的表达式op'优先级比op大就加()。
数字一律不加()
参数:后缀表达式(引用,因为要改变)，当前优先级(若是计算右子表达式传入_L)
返回中缀表达式
*/
string exp(string &postfixExp, int priority = 0)
{
	int len = postfixExp.length();
	char op = postfixExp[len - 1];
	postfixExp = postfixExp.substr(0, len - 1);	//处理后去掉最末一个字符

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
		//数字就是子表达式
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

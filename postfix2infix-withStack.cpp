#include <iostream>
#include <string>

using namespace std;

//优先级定义，优先级大的先运算
//数字视为优先级最高
enum priority
{
	ADD, MUL, NUM
};

//栈中的节点，保存表达式以及运算优先级
//可以给表达式加()
struct Node
{
	string exp;
	int priority;
	Node *next;

	Node()
	{
		next = NULL;
	}

	/*加()*/
	void addParentheses()
	{
		exp = '(' + exp + ')';
	}
};

//栈
//主要操作是入栈和出栈
struct Stack
{
	Node *end;
	Node *top;

	Stack()
	{
		end = new Node;   //end节点无意义,只是方便操作
		top = end;
	}

	~Stack()
	{
		Node *p = top;
		while (!isEmpty())
		{
			top = top->next;
			delete p;
			p = top;
		}
		delete end;
	}

	bool isEmpty()
	{
		return top == end;
	}

	/*入栈*/
	void push(Node *node)
	{
		node->next = top;
		top = node;
	}

	/*出栈*/
	Node* pop()
	{
		if (isEmpty())
		{
			return NULL;
		}
		Node *p = top;
		top = top->next;
		return p;
	}
};

int main()
{
	string postfixExp;
	cin >> postfixExp;
	Stack *exps = new Stack;		//表达式栈

	int len = postfixExp.length();
	for (int i = 0; i < len; i++)
	{
		char op = postfixExp[i];
		if (op == '+' || op == '-' || op == '*' || op == '/')
		{
			int pri;
			if (op == '+' || op == '-')
			{
				pri = ADD;
			}
			else
			{
				pri = MUL;
			}
			Node *rightExp = exps->pop();
			if (rightExp->priority <= pri)
			{
				rightExp->addParentheses();
			}
			Node *leftExp = exps->pop();
			if (leftExp->priority < pri)
			{
				leftExp->addParentheses();
			}
			Node *subExp = new Node;
			subExp->exp = leftExp->exp + op + rightExp->exp;
			subExp->priority = pri;	//更新运算优先级
			//新表达式入栈
			exps->push(subExp);

			//释放
			delete leftExp;
			delete rightExp;
		}
		else
		{
			//数字是一个表达式,直接入栈
			Node *t = new Node;
			t->exp += postfixExp[i];
			t->priority = NUM;
			exps->push(t);
		}
	}

	//最终结果在栈底
	cout << exps->pop()->exp << endl;			//内存泄漏警告

	delete exps;

	return 0;
}

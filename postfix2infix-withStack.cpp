#include <iostream>
#include <string>

using namespace std;

//���ȼ����壬���ȼ����������
//������Ϊ���ȼ����
enum priority
{
	ADD, MUL, NUM
};

//ջ�еĽڵ㣬������ʽ�Լ��������ȼ�
//���Ը����ʽ��()
struct Node
{
	string exp;
	int priority;
	Node *next;

	Node()
	{
		next = NULL;
	}

	/*��()*/
	void addParentheses()
	{
		exp = '(' + exp + ')';
	}
};

//ջ
//��Ҫ��������ջ�ͳ�ջ
struct Stack
{
	Node *end;
	Node *top;

	Stack()
	{
		end = new Node;   //end�ڵ�������,ֻ�Ƿ������
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

	/*��ջ*/
	void push(Node *node)
	{
		node->next = top;
		top = node;
	}

	/*��ջ*/
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
	Stack *exps = new Stack;		//���ʽջ

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
			subExp->priority = pri;	//�����������ȼ�
			//�±��ʽ��ջ
			exps->push(subExp);

			//�ͷ�
			delete leftExp;
			delete rightExp;
		}
		else
		{
			//������һ�����ʽ,ֱ����ջ
			Node *t = new Node;
			t->exp += postfixExp[i];
			t->priority = NUM;
			exps->push(t);
		}
	}

	//���ս����ջ��
	cout << exps->pop()->exp << endl;			//�ڴ�й©����

	delete exps;

	return 0;
}

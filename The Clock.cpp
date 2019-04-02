#include <iostream>
#include <string>

using namespace std;

const int MAX_MOVES = 9;
const int MAX_STEPS = 5;
const int MAX_REPEATS = 3;

/*
9���ƶ����У�ÿ�������������ֱ�ʾ��Ӱ�����(��˳����)
-1��ʾû�в���
*/
int moves[MAX_MOVES][MAX_STEPS] =
{
	{ 0, 1, 3, 4, -1 },
	{ 0, 1, 2, -1, -1 } ,
	{ 1, 2, 4, 5, -1 },
	{ 0, 3, 6, -1, -1 },
	{ 1, 3, 4, 5, 7 },
	{ 2, 5, 8, -1, -1 },
	{ 3, 4, 6, 7, -1 },
	{ 6, 7, 8, -1, -1 },
	{ 4, 5, 7, 8, -1 }
};

/*
�������ڶ�ά�����е��±�
*/
int getX(int index)
{
	return index / 3;
}

int getY(int index)
{
	return index % 3;
}

/*
ʵʩһ���ƶ�����
*/
void moveOnce(int status[][3], int move[])
{
	for (int i = 0; i < MAX_STEPS && move[i] != -1; i++)
	{
		int x = getX(move[i]), y = getY(move[i]);
		status[x][y]++;
		status[x][y] %= 4;
	}
}

/*
��src���Ƶ�dest��
*/
void copy(int src[][3], int dest[][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			dest[i][j] = src[i][j];
		}
	}
}

/*
������Ƿ�ԭ
*/
bool check(int status[][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (status[i][j] != 0)
			{
				return false;
			}
		}
	}

	return true;
}

/*
�Ƚ��ַ��������ؽ϶�(�ȳ������ֵ����С)�Ĵ�
���ڱȽϵ�ǰ������Ž�
*/
string compare(string newStr, string oldStr)
{
	if (newStr.length() < oldStr.length()
		|| (newStr.length() == oldStr.length() && newStr < oldStr))
	{
		return newStr;
	}
	else
	{
		return oldStr;
	}
}

/*
�������п��ܵĽ⣬�������Ž�
����Ϊ�ӵĳ�ʼ״̬,��ǰ��,��ǰ���Ž�,�ݹ���
����ȫ�����Ž�
*/
string moveClock(int status[][3], string result, string solution, int step)
{
	//���Ƶ�ǰ״̬���ڵݹ���һ��
	int t[3][3];
	copy(status, t);
	string str = result;

	//ÿһ�����п���ѡ��ʵʩ0~3��
	for (int i = 0; i < MAX_REPEATS + 1; i++)
	{
		if (i != 0)
		{
			str += step + '0';
			moveOnce(t, moves[step]);
		}

		//��֦�Լ�����
		if (check(t))
		{
			return compare(str, solution);
		}

		//�����ǵݹ����һ���������µݹ�
		if (step != MAX_MOVES - 1)
		{
			string newSolution = moveClock(t, str, solution, step + 1);
			//4�ֽ������������
			solution = compare(newSolution, solution);
		}
	}

	return solution;
}

int main()
{
	int status[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> status[i][j];
		}
	}

	string solution;
	for (int i = 0; i < MAX_MOVES * MAX_REPEATS; i++)
	{
		solution += MAX_MOVES + '0';
	}

	solution = moveClock(status, "", solution, 0);

	//��ʽ�����
	//���û�����Ž���߳�ʼ״̬���Ѹ�ԭ,�����
	if (solution[0] != MAX_MOVES + '0')
	{
		int len = solution.length();
		for (int i = 0; i < len; i++)
		{
			cout << solution[i] - '0' + 1 << ' ';
		}
	}
	cout << endl;

	return 0;
}
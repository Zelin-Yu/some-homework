#include <iostream>
#include <string>

using namespace std;

const int MAX_MOVES = 9;
const int MAX_STEPS = 5;
const int MAX_REPEATS = 3;

/*
9个移动序列，每个序列中用数字表示受影响的钟(按顺序编号)
-1表示没有操作
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
计算钟在二维数组中的下标
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
实施一个移动序列
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
将src复制到dest中
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
检查钟是否复原
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
比较字符串，返回较短(等长返回字典序较小)的串
用于比较当前解和最优解
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
遍历所有可能的解，返回最优解
参数为钟的初始状态,当前解,当前最优解,递归层次
返回全局最优解
*/
string moveClock(int status[][3], string result, string solution, int step)
{
	//复制当前状态用于递归下一层
	int t[3][3];
	copy(status, t);
	string str = result;

	//每一个序列可以选择实施0~3次
	for (int i = 0; i < MAX_REPEATS + 1; i++)
	{
		if (i != 0)
		{
			str += step + '0';
			moveOnce(t, moves[step]);
		}

		//剪枝以及出口
		if (check(t))
		{
			return compare(str, solution);
		}

		//当不是递归最后一步，再往下递归
		if (step != MAX_MOVES - 1)
		{
			string newSolution = moveClock(t, str, solution, step + 1);
			//4种解决方案中择优
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

	//格式化输出
	//如果没有最优解或者初始状态就已复原,不输出
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
#include <iostream>
#include <string>

const int MAX_N = 100;
const int MAX_STEPS = 10000;

enum
{
	NORTH, EAST, SOUTH, WEST
};

struct Robot
{
	//位置和面向方向
	int x, y;
	int direction;

	void init()
	{
		if (y == 0)
		{
			direction = NORTH;
		}
		else
		{
			direction = SOUTH;
		}
	}

	/*移动后的新位置*/
	void nextPos(int &newx, int &newy)
	{
		newx = x;
		newy = y;
		switch (direction)
		{
		case NORTH:
			newx--;
			break;
		case EAST:
			newy++;
			break;
		case SOUTH:
			newx++;
			break;
		case WEST:
			newy--;
			break;
		default:
			break;
		}
	}

	/*测试是否可以前进*/
	bool isMovable(char maze[][MAX_N], int N)
	{
		int newx, newy;
		nextPos(newx, newy);
		if (newx >= 0 && newx < N
			&& newy >= 0 && newy < N
			&& maze[newx][newy] == '.')
		{
			return true;
		}
		return false;
	}

	/*返回代表移动方向的字符*/
	char moveDirection()
	{
		switch (direction)
		{
		case NORTH:
			return 'N';
		case EAST:
			return 'E';
		case SOUTH:
			return 'S';
		case WEST:
			return 'W';
		default:
			break;
		}
	}

	/*左转*/
	void turnLeft()
	{
		direction = (direction + 3) % 4;
	}

	/*右转*/
	void turnRight()
	{
		direction = (direction + 1) % 4;
	}

	/*前进,前进后如果有必要,左转*/
	void goForward(char maze[][MAX_N], int N)
	{
		int newx, newy;
		nextPos(newx, newy);
		x = newx;
		y = newy;
		//若左边不靠墙，需要转向左边
		switch (direction)
		{
		case NORTH:
			if (y - 1 >= 0 && maze[x][y - 1] == '.')
			{
				turnLeft();
			}
			break;
		case EAST:
			if (x - 1 >= 0 && maze[x - 1][y] == '.')
			{
				turnLeft();
			}
			break;
		case SOUTH:
			if (y + 1 < N && maze[x][y + 1] == '.')
			{
				turnLeft();
			}
			break;
		case WEST:
			if (x + 1 < N && maze[x + 1][y] == '.')
			{
				turnLeft();
			}
			break;
		default:
			break;
		}
	}
};

using namespace std;

int main()
{
	Robot Edison;
	int T;
	cin >> T;

	for (int testCase = 0; testCase < T; testCase++)
	{
		cout << "Case #" << testCase + 1 << ": ";

		int N;
		cin >> N;
		char maze[MAX_N][MAX_N];
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> maze[i][j];
			}
		}
		int sx, sy, ex, ey;
		cin >> sx >> sy >> ex >> ey;

		//初始化
		ex--;
		ey--;
		Edison.x = sx - 1;
		Edison.y = sy - 1;
		Edison.init();

		string path;
		int step = 0;
		while (step < MAX_STEPS)
		{
			//找到出口
			if (Edison.x == ex && Edison.y == ey)
			{
				break;
			}

			//在不能前进时转动直到可以前进
			int turnTimes = 0;
			while (!Edison.isMovable(maze, N))
			{
				if (turnTimes == 3)  //转三次都不能行动说明被困住
				{
					break;
				}
				//前面不能走，肯定能往右转
				Edison.turnRight();
				turnTimes++;
			}
			if (!Edison.isMovable(maze, N))
			{
				break;
			}
			else	//记录路径，更改状态
			{
				path += Edison.moveDirection();
				Edison.goForward(maze, N);
				step++;
			}
		}
		//一开始就不能移动或者移动超过最大步数
		if (step == 0 || step == MAX_STEPS)
		{
			cout << "Edison ran out of energy." << endl;
		}
		//成功找到出口
		else
		{
			cout << step << endl << path << endl;
		}
	}
}
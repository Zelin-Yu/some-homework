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
	//λ�ú�������
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

	/*�ƶ������λ��*/
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

	/*�����Ƿ����ǰ��*/
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

	/*���ش����ƶ�������ַ�*/
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

	/*��ת*/
	void turnLeft()
	{
		direction = (direction + 3) % 4;
	}

	/*��ת*/
	void turnRight()
	{
		direction = (direction + 1) % 4;
	}

	/*ǰ��,ǰ��������б�Ҫ,��ת*/
	void goForward(char maze[][MAX_N], int N)
	{
		int newx, newy;
		nextPos(newx, newy);
		x = newx;
		y = newy;
		//����߲���ǽ����Ҫת�����
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

		//��ʼ��
		ex--;
		ey--;
		Edison.x = sx - 1;
		Edison.y = sy - 1;
		Edison.init();

		string path;
		int step = 0;
		while (step < MAX_STEPS)
		{
			//�ҵ�����
			if (Edison.x == ex && Edison.y == ey)
			{
				break;
			}

			//�ڲ���ǰ��ʱת��ֱ������ǰ��
			int turnTimes = 0;
			while (!Edison.isMovable(maze, N))
			{
				if (turnTimes == 3)  //ת���ζ������ж�˵������ס
				{
					break;
				}
				//ǰ�治���ߣ��϶�������ת
				Edison.turnRight();
				turnTimes++;
			}
			if (!Edison.isMovable(maze, N))
			{
				break;
			}
			else	//��¼·��������״̬
			{
				path += Edison.moveDirection();
				Edison.goForward(maze, N);
				step++;
			}
		}
		//һ��ʼ�Ͳ����ƶ������ƶ����������
		if (step == 0 || step == MAX_STEPS)
		{
			cout << "Edison ran out of energy." << endl;
		}
		//�ɹ��ҵ�����
		else
		{
			cout << step << endl << path << endl;
		}
	}
}
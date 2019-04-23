#include <iostream>
#include <string>

const int MAX_M = 50;
const int MAX_N = 50;

int wall[MAX_M][MAX_N];
bool visited[MAX_M][MAX_N];

//���Ͽ�ʼ˳ʱ�룬����仯�͸÷����ϵ�ǽ����ֵ
int shift[4][2] =
{
	{ 0, -1 }, { -1, 0 }, { 0, 1 }, { 1, 0 }
};

int direction[4] = { 1, 2, 4, 8 };

using namespace std;

/*�ݹ�������ͨ�ķ��䣬���ط������*/
int retrieve(int i, int j)
{
	int size = 1;	//���������СΪ1
	visited[i][j] = true;
	//���Ͽ�ʼ˳ʱ������
	for (int k = 0; k < 4; k++)
	{
		int x = i + shift[k][0], y = j + shift[k][1];
		//���ж��Ƿ���ǽ����������Խ��
		if ((wall[i][j] & direction[k]) == 0 && !visited[x][y])
		{
			size += retrieve(i + shift[k][0], j + shift[k][1]);
		}
	}

	return size;
}

int main()
{
	int M, N;
	cin >> M >> N;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> wall[i][j];
		}
	}

	int roomNum = 0, maxSize = 0;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (!visited[i][j])
			{
				roomNum++;
				int size = retrieve(i, j);
				maxSize = size > maxSize ? size : maxSize;
			}
		}
	}

	cout << roomNum << endl << maxSize << endl;

	return 0;
}
#include <iostream>
#include <string>

using namespace std;

const int MAX_FILE_NUM = 1500;

/*���ļ��������ֵ������flie[]*/
void addFile(string file[], int num, string name)
{
	int i;
	for (i = 0; i < num; i++)
	{
		if (name < file[i])
		{
			break;
		}
	}
	for (int j = num; j > i; j--)
	{
		file[j] = file[j - 1];
	}
	file[i] = name;
}

/*�ݹ��ӡ�ļ���νṹ*/
void printFileMap(int step = 0)
{
	if (step == 0)
	{
		cout << "ROOT" << endl;
	}

	string name;				//������
	string file[MAX_FILE_NUM];	//�����ǰ����Ŀ¼,��Ÿ�Ŀ¼�µ��ļ�
	int num = 0;				//��ǰĿ¼���ļ�����

	while (true)
	{
		cin >> name;
		switch (name[0])
		{
		case 'f':			//�ļ��������ŵ�������
			addFile(file, num, name);
			num++;
			break;

		case 'd':			//Ŀ¼,����ݹ���һ��
			for (int i = 0; i < step + 1; i++)
			{
				cout << "|     ";
			}
			cout << name << endl;
			printFileMap(step + 1);
			break;

		case ']':
		case '*':
			//(��)Ŀ¼����,��ӡ���ڸ�Ŀ¼���ļ�,�ص��ݹ��ϲ�
			for (int i = 0; i < num; i++)
			{
				for (int j = 0; j < step; j++)
				{
					cout << "|     ";
				}
				cout << file[i] << endl;
			}
			if (name[0] == '*')
			{
				cout << endl;
			}
			return;

		default:
			break;
		}
	}
}

int main()
{
	int i = 1;
	while (true)
	{
		cout << "DATA SET " << i << ':' << endl;

		printFileMap();

		cin.get(); //������ĩ�س�
		if (cin.peek() == '#')    //C������getchar()��ungetc()ʵ��
		{
			break;
		}

		i++;
	}
}
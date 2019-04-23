#include <iostream>
#include <string>

using namespace std;

const int MAX_FILE_NUM = 1500;

/*将文件按名字字典序放入flie[]*/
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

/*递归打印文件层次结构*/
void printFileMap(int step = 0)
{
	if (step == 0)
	{
		cout << "ROOT" << endl;
	}

	string name;				//输入行
	string file[MAX_FILE_NUM];	//如果当前处理目录,存放该目录下的文件
	int num = 0;				//当前目录下文件个数

	while (true)
	{
		cin >> name;
		switch (name[0])
		{
		case 'f':			//文件，按序存放到数组中
			addFile(file, num, name);
			num++;
			break;

		case 'd':			//目录,进入递归下一层
			for (int i = 0; i < step + 1; i++)
			{
				cout << "|     ";
			}
			cout << name << endl;
			printFileMap(step + 1);
			break;

		case ']':
		case '*':
			//(根)目录结束,打印属于该目录的文件,回到递归上层
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

		cin.get(); //处理行末回车
		if (cin.peek() == '#')    //C可以用getchar()和ungetc()实现
		{
			break;
		}

		i++;
	}
}
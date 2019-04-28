#include <iostream>
#include <cstring>	//<string.h>

const int MAX_BRANCH_NUM = 26;
const int MAX_INPUT_LINES = 1000;
const int MAX_CHAR_NUM = 20;

typedef struct TrieNode
{
	int count;				//记录多少个字符串经过该节点
	TrieNode *children[MAX_BRANCH_NUM];
}Trie;

void InitNode(TrieNode *node)
{
	node->count = 0;
	memset(node->children, NULL, MAX_BRANCH_NUM * sizeof(TrieNode*));
}

/*
插入字符串，检查每个字符，若存在，计数+1;否则新插入一个节点
*/
void Insert(Trie *root, const char *str)
{
	TrieNode *p = root;

	for (int i = 0; str[i] != '\0'; i++)
	{
		int index = str[i] - 'a';           //字母节点按字典序排列
		if (p->children[index] == NULL)
		{
			p->children[index] = (TrieNode *)malloc(sizeof(TrieNode));
			InitNode(p->children[index]);
		}
		p = p->children[index];
		p->count++;
	}
}

void Destroy(Trie *root)
{
	if (root == NULL)
	{
		return;
	}

	for (int i = 0; i < MAX_BRANCH_NUM; i++)
	{
		Destroy(root->children[i]);
	}

	free(root);
}

/*
寻找最短前缀，只需从上到下找到第一个计数为1的节点(或者到达字符串末尾)，然后返回路径上的子串
*/
void FindPrefix(Trie *root, const char *src, char *prefix)
{
	Trie *p = root;

	for (int i = 0; src[i] != '\0'; i++)	//字符串到达末尾退出循环，筛除1.重复字符串的情况;2.单词本身是另一个单词前缀的情况
	{
		int index = src[i] - 'a';
		if (p->children[index] == NULL)    //字符串不在树中的情况(此题不存在)
		{
			prefix[0] = '\0';
			break;
		}

		p = p->children[index];
		prefix[i] = src[i];
		if (p->count == 1)
		{
			break;
		}
	}
}

using namespace std;

int main()
{
	Trie *root = (Trie *)malloc(sizeof(Trie));
	InitNode(root);

	char inputLine[MAX_INPUT_LINES][MAX_CHAR_NUM + 1];
	int lines = 0;
	while (cin >> inputLine[lines])
	{
		Insert(root, inputLine[lines]);         //构建树
		lines++;
	}

	for (int i = 0; i < lines; i++)
	{
		char prefix[MAX_CHAR_NUM + 1] = { '\0' };
		FindPrefix(root, inputLine[i], prefix);
		cout << inputLine[i] << ' ' << prefix << endl;
	}

	Destroy(root);

	return 0;
}
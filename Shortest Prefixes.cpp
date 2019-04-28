#include <iostream>
#include <cstring>	//<string.h>

const int MAX_BRANCH_NUM = 26;
const int MAX_INPUT_LINES = 1000;
const int MAX_CHAR_NUM = 20;

typedef struct TrieNode
{
	int count;				//��¼���ٸ��ַ��������ýڵ�
	TrieNode *children[MAX_BRANCH_NUM];
}Trie;

void InitNode(TrieNode *node)
{
	node->count = 0;
	memset(node->children, NULL, MAX_BRANCH_NUM * sizeof(TrieNode*));
}

/*
�����ַ��������ÿ���ַ��������ڣ�����+1;�����²���һ���ڵ�
*/
void Insert(Trie *root, const char *str)
{
	TrieNode *p = root;

	for (int i = 0; str[i] != '\0'; i++)
	{
		int index = str[i] - 'a';           //��ĸ�ڵ㰴�ֵ�������
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
Ѱ�����ǰ׺��ֻ����ϵ����ҵ���һ������Ϊ1�Ľڵ�(���ߵ����ַ���ĩβ)��Ȼ�󷵻�·���ϵ��Ӵ�
*/
void FindPrefix(Trie *root, const char *src, char *prefix)
{
	Trie *p = root;

	for (int i = 0; src[i] != '\0'; i++)	//�ַ�������ĩβ�˳�ѭ����ɸ��1.�ظ��ַ��������;2.���ʱ�������һ������ǰ׺�����
	{
		int index = src[i] - 'a';
		if (p->children[index] == NULL)    //�ַ����������е����(���ⲻ����)
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
		Insert(root, inputLine[lines]);         //������
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
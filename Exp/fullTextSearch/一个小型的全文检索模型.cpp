#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

typedef int Status;
#define LINESIZE 80	 //设一行字符数为80
#define MAXKEYLEN 26 //关键字的长度
#define MAXNUM 100	 //统计单词的最大数
typedef struct
{
	char *ch;	//关键字
	int num;	//关键字的长度
	char *info; //关键字有关信息
} KeysType;		//关键字类型

typedef enum
{
	LEAF,
	BRANCH
} NodeKind; //结点种类：{叶子，分支}

typedef struct DLTNode
{
	char symbol;
	struct DLTNode *next; //指向兄弟结点的指针
	NodeKind kind;		  //结点标志
	union
	{
		struct DLTNode *first; //分支结点的孩子链指针
		struct
		{
			int idx; //叶子结点的Count数组下标指针
			KeysType infoptr;
		};
	};
} DLTNode, *DLTree;	 //双链树类型

char line[LINESIZE]; //用于缓存文章中每行的字符串

struct Count
{
	int times;
	KeysType info;
} Count[MAXNUM];

int NUM = 0; //记录整个文章的单词总数

char ch1[17][100] = {"a", "an", "the", "them", "there", "here", "they", "are", "that", "this", "those", "what", "which", "why", "then", "and", "these"};

void InitTree(DLTree &root)
{
	//初始化键树
	root = new DLTNode;
	root->next = NULL;
	root->first = NULL;
} 

Status Insert_DLTree(DLTree &root, KeysType K, int &n)
{
	//指针root所指双链树中已含n个关键字，若不存在和K相同的关键字，
	//则将关键字K插入到双链树中相应位置，树中关键字个数n增1且返回TRUE；..
	//否则不再插入返回FALSE
	DLTree p = root->first, f = root, pre, s;
	int j = 0;
	while (p && j < K.num)
	{ //在键树中进行查找
		pre = NULL;
		while (p && p->symbol < K.ch[j])
		{ //查找和K.ch[j]相同的结点
			pre = p;
			p = p->next;
		}
		if (p && p->symbol == K.ch[j])
		{
			f = p;
			p = p->first;
			j++;
		} //找到后进入键树的下一层，即查找和K.ch[j+1]相同的结点
		else
		{ //没有找到和K.ch[j]相同的结点，插入K.ch[j]
			s = new DLTNode;
			s->kind = BRANCH;
			s->symbol = K.ch[j++];
			if (pre)
				pre->next = s;
			else
				f->first = s;
			s->next = p;
			s->first = NULL;
			p = s;
			break;
		}
	}
	if (p && j == K.num && p->first && p->first->kind == LEAF)
		return false;
	else
	{ //键树中已存在相同前缀的单词，插入由剩余字符构成的单支树
		while (j <= K.num)
		{
			s = new DLTNode;
			s->next = NULL;
			if (p)
			{
				s->next = p->next;
				p->first = s;
				p = s;
			}
			else
			{
				f->first = s;
				p = s;
			}
			if (j < K.num)
			{
				s->kind = BRANCH;
				s->symbol = K.ch[j++];
				s->first = NULL;
			}
			else
			{
				s->symbol = '$';
				s->kind = LEAF;
				n++;
				s->idx = n;
				s->infoptr.ch = Count[s->idx].info.ch = K.ch;
				s->infoptr.info = Count[s->idx].info.info = K.info;
				s->infoptr.num = Count[s->idx].info.num = K.num;
				Count[s->idx].times = 0;
				j++;
			}
		}
		return true;
	}
} 

void CreateDLTree(DLTree &T, KeysType *key, int &n)
{
	//建立键树模型
	for (int i = 0; i <= 16; i++)
	{
		key[i].ch = ch1[i];
		key[i].info = NULL;
		key[i].num = strlen(key[i].ch);
	}
	key[0].info = (char *)"indefinite article.";											// a
	key[1].info = (char *)"indefinite articles.";											// an
	key[2].info = (char *)"definite article.";												// the
	key[3].info = (char *)"personal pronoun";												// them
	key[4].info = (char *)"adv. of place and direction";									// there
	key[5].info = (char *)"to this point or place";											// here
	key[6].info = (char *)"pronoun";														// they
	key[7].info = (char *)"v.i. joining subject & predicate";								// are
	key[8].info = (char *)"adj. & pron.";													// that
	key[9].info = (char *)"adj. & pron.";													// this
	key[10].info = (char *)"adj. & pron.";													// those
	key[11].info = (char *)"adj. & pron.,asking for a selection from an indefinite number"; // what
	key[12].info = (char *)"adj. & pron.,asking for a selection from two or a group";		// which
	key[13].info = (char *)"adj. & int.,for what reason,with what purpose";					// why
	key[14].info = (char *)"adv.,at what time";												// then
	key[15].info = (char *)"conj.,connecting words";										// and
	key[16].info = (char *)"adj. & pron.";													// these
	for (int i = 0; i <= 16; i++)
		Insert_DLTree(T, key[i], n); //建立键树模型
}

Status Search_DLTree(DLTree rt, int j, int &k)
{
	//若line中从第j个字符起长度为k的子串和指针rt所指向双链树中单词相同，
	//则数组Count中相应分量增1，并返回TRUE，否则返回FALSE
	DLTree p;
	int found;
	k = 0;
	found = false;
	p = rt->first; // p指向双链树中的第一棵子树的树根
	while (p && !found)
	{
		while (p && p->symbol < line[j + k])
			p = p->next;
		if (!p || p->symbol > line[j + k])
			break; //在键树的第k+1层上匹配失败
		else
		{ //继续匹配
			p = p->first;
			k++;
			if (p->kind == LEAF)
			{ //找到一个单词
				if (!(line[j + k] >= 'a' && line[j + k] <= 'z') || (line[j + k] >= 'A' && line[j + k] <= 'Z'))
				{
					Count[p->idx].times++; //统计数组对应元素加1
					found = true;
				} //若键树中含有"commit"，文本行中为commit则为找到，若为committing则为没找到
			}
		}
	}
	return found;
}

void setmatch(DLTree root, char *line, FILE *f)
{
	//统计以root为根指针的键树中，各关键字在本文本串line中重复出现的次数，
	//并将其累加到统计数组Count中去
	unsigned i = 0;
	int k; //若查找成功，返回的k为所查找的关键字长度
	while (fgets(line, LINESIZE, f) != NULL)
	{
		cout << line;
		i = 0;
		while (i <= strlen(line))
		{ // LINESIZE
			if (!Search_DLTree(root, i, k))
			{
				if (((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= '0' && line[i] <= '9')) && !((line[i + 1] >= 'a' && line[i + 1] <= 'z') || (line[i + 1] >= 'A' && line[i + 1] <= 'Z') || (line[i + 1] >= '0' && line[i + 1] <= '9')))
					NUM++; //单词总数加1
				i++;	   //若查找不成功，则从下一个字符开始查找
			}			   // if
			else
			{
				i += k; //查找成功，继续在文本串中的第i+k-1个字符开始查找
				NUM++;
			}
		}
	}
}

void Input(FILE *&f)
{
	char fname[30];
	cout << "please input the file name:";
	cin >> fname; //输入文件名
	if ((f = fopen(fname, "r")) == NULL)
	{ //输入错误文件名, 无法打开
		cout << "Can NOT open the file!" << endl;
		exit(1);
	}
} // Input

void output(int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (Count[i].times)
		{
			cout << Count[i].info.ch << " : ";
			if (Count[i].info.info)
				cout << Count[i].info.info << endl;
			cout << float(Count[i].times) / float(NUM) << " in the sentence." << endl;
		} //输出文章中含有键树中的关键字及有关解释，出现频率。即：该关键字出现次数/文章单词总数
	}
}
int main()
{
	FILE *f;
	Input(f);
	DLTree T;
	InitTree(T);
	KeysType *key = (KeysType *)malloc(sizeof(KeysType));
	int n;
	CreateDLTree(T, key, n);
	setmatch(T, line, f);
	output(n);
	return 0;
}

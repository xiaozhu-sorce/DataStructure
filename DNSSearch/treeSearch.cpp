#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

//树的基本数据结构
typedef struct Node {
	char a[20];//存放域名
	char IP[20];//根结点存放IP
	struct Node *left;
	struct Node *right;
} Node;

int count = 0;

//数据保存在相同目录下的text.txt文件下;
Node *createTree(Node *bt, FILE *fp) {
	char a[20];
	//从fp打开的文件中读取格式化输入
	if (fscanf(fp, "%s ",a) != EOF) {
		//base case
		if (a[0] == '#')
			bt = NULL;
		else {
			bt = (Node *)malloc(sizeof(Node));

			//存放域名
			strcpy(bt->a, a);

			//判读是否为叶子结点 --- 也就是判断域名开始是否为www,bbs,ftp
			if (strcmp(a, "www") == 0 || strcmp(a, "bbs") == 0 || strcmp(a, "ftp") == 0 ) {
				fscanf(fp, "%s ", a);
				strcpy(bt->IP, a);
			}

			//后序遍历递归构造树
			bt->left = createTree(bt->left, fp);
			bt->right = createTree(bt->right, fp);
		}
	}
	return bt;
}

Node *addIP(Node *bt, char splitStr[4][20], int i, char ip[20]) {
	if (bt != NULL && strcmp(bt->a, splitStr[i]) == 0) {
		if (i == 0) {
			puts(bt->IP);
			return bt;
		}
		bt->left = addIP(bt->left, splitStr, --i, ip);
	} else {
		if (bt == NULL) {
			if (i == -1) {
				return bt;
			}

			bt = (Node *)malloc(sizeof(Node));
			bt->right = NULL;
			bt->left = NULL;

			strcpy(bt->a, splitStr[i]);

			if (strcmp(splitStr[i], "www") == 0 || strcmp(splitStr[i], "bbs") == 0 || strcmp(splitStr[i], "ftp") == 0 ) {
				strcpy(bt->IP, ip);
			}
			bt->left = addIP(bt->left, splitStr, --i, ip);
		} else
			bt->right = addIP(bt->right, splitStr, i, ip);
	}
	return bt;
}

//将写好的数据写入文件
void renew(Node *bt, FILE *fp) {
	if (bt == NULL) {
		fprintf(fp, "# ");
	} else {
		fprintf(fp, "%s ", bt->a);
		if (strcmp(bt->a, "www") == 0 || strcmp(bt->a, "bbs") == 0 || strcmp(bt->a, "ftp") == 0 ) {
			fprintf(fp, "%s ", bt->IP);
		}
		renew(bt->left, fp);
		renew(bt->right, fp);
	}
}

//i为有几个分割出来的子字符串
void serchIP(Node *bt, char splitStr[4][20], int i) {

	if (bt != NULL && strcmp(bt->a, splitStr[i]) == 0) {
		if (i == 0) {
			puts(bt->IP);
			return;
		}
		serchIP(bt->left, splitStr, --i);

	} else {
		if (bt == NULL) {
			cout << "找不到服务器或发生 DNS 错误" << endl;
			return;
		}
		serchIP(bt->right, splitStr, i);
	}
}

int main() {
	printf("欢迎使用IP查询!\n");
	char str[80];
	char ip[20];
	char *token;
	char ifNext = 'y';
	int selection;
	char splitStr[4][20];

	Node *bt;
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	fp1 = fopen("text.txt", "r");
	bt = createTree(bt, fp1);
	fp2 = fopen("text.txt", "w");

	//renew(bt);
	while (ifNext != 'n') {
		cout << "请选择功能：1:增加网址; 2:查询网址; 3:退出系统" << endl;
		cin >> selection;
		getchar();

		if (selection == 3) {
			renew(bt, fp2);
			exit(0);
		}

		printf("请输入地址：");
		cin >> str;
		getchar();

		int i = 0;
		//将输入的字符串进行分解，分解字符串 str 为一组字符串，"."为分隔符。
		token = strtok(str, ".");

		while (token != NULL) {
			strcpy(splitStr[i], token);
			i++;
			//继续获得分割的str的下一个子字符串
			token = strtok(NULL, ".");
		}

		switch (selection) {
			case 1:
				cout << "请输入ip：";
				cin >> ip;
				getchar();
				bt = addIP(bt, splitStr, --i, ip);
				break;
			case 2:
				serchIP(bt, splitStr, --i);
				break;
		}
		printf("是否继续？y/n\n");
		cin >> ifNext;
		getchar();
	}
	
	renew(bt, fp2);
	fclose(fp2);
	fclose(fp1);
	printf("谢谢使用");
}
/*
可查询的数据如下所示：
www.baidu.com 220.181.27.5
www.google.com 66.249.89.104
www.microsoft.com 207.46.20.60
www.whitehouse.gov 64.215.166.127
www.nasa.gov 210.254.57.56
www.lenovo.com.cn 219.239.195.11
www.sina.com.cn 218.30.13.51
www.ustc.edu.cn 202.38.64.2
bbs.ustc.edu.cn 202.38.64.3
www.pku.edu.cn 162.105.129.12
bbs.pku.edu.cn 162.105.204.150
www.tsinghua.edu.cn 166.111.4.100
ftp.tsinghua.edu.cn 166.111.8.229
www.beijing.gov.cn 210.73.64.10
www.shanghai.gov.cn 61.129.65.58
www.xiaozhu-sorce.github.io 123.123.123
*/
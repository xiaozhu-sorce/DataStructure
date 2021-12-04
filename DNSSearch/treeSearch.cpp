#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct app {
	char a[20];
	struct app *left;
	struct app *right;
	char b[20];
} app;
int cout = 0;

//数据保存在相同目录下的text.txt文件下;
app *jianshu(app *bt, FILE *fp) {
	char a[20];
	if (fscanf(fp, "%s ", &a) != EOF) {
		if (a[0] == '#')
			bt = NULL;
		else {
			bt = (app *)malloc(sizeof(app));
			strcpy(bt->a, a);
			if (strcmp(a, "www") == 0 || strcmp(a, "bbs") == 0 || strcmp(a, "ftp") == 0 ) {
				fscanf(fp, "%s ", &a);
				strcpy(bt->b, a);
			}
			bt->left = jianshu(bt->left, fp);
			bt->right = jianshu(bt->right, fp);
		}
	}
	return bt;
}

app *tianjia(app *bt, char fenge[4][20], int i, char ip[20]) {
	/*puts(fenge[i]);
	puts(bt->a);
	printf("%d", i);*/
	if (bt != NULL && strcmp(bt->a, fenge[i]) == 0) {
		if (i == 0) {
			puts(bt->b);
			return bt;
		}
		bt->left = tianjia(bt->left, fenge, --i, ip);
	} else {
		if (bt == NULL) {
			if (i == -1) {
				return bt;
			}
			bt = (app *)malloc(sizeof(app));
			bt->right = NULL;
			bt->left = NULL;
			strcpy(bt->a, fenge[i]);
			if (strcmp(fenge[i], "www") == 0 || strcmp(fenge[i], "bbs") == 0 || strcmp(fenge[i], "ftp") == 0 ) {
				strcpy(bt->b, ip);
			}
			bt->left = tianjia(bt->left, fenge, --i, ip);
		} else
			bt->right = tianjia(bt->right, fenge, i, ip);
	}
	return bt;
}

void qianxu(app *bt, FILE *fp) {
	if (bt == NULL) {
		fprintf(fp, "# ");
	} else {
		fprintf(fp, "%s ", bt->a);
		if (strcmp(bt->a, "www") == 0 || strcmp(bt->a, "bbs") == 0 || strcmp(bt->a, "ftp") == 0 ) {
			fprintf(fp, "%s ", bt->b);
		}
		qianxu(bt->left, fp);
		qianxu(bt->right, fp);
	}
}

void jiediangeshu(app *bt, char fenge[4][20], int i) {
	/*for (i; i >= 0; i--) {
		puts(fenge[i]);
	}*/
	//puts(bt->a);
	//puts(fenge[i]);
	if (bt != NULL && strcmp(bt->a, fenge[i]) == 0) {
		if (i == 0) {
			puts(bt->b);
			return;
		}
		jiediangeshu(bt->left, fenge, --i);

	} else {
		if (bt == NULL) {
			printf("找不到服务器或发生 DNS 错误");
			return;
		}
		jiediangeshu(bt->right, fenge, i);
	}
}

int main() {
	printf("欢迎使用IP查询!\n");
	char str[80];
	char ip[20];
	char *token;
	char ju = 'y';
	int xuan;
	char fenge[4][20];
	int flag = 0;
	app *bt;
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	fp1 = fopen("text.txt", "r");
	bt = jianshu(bt, fp1);
	fp2 = fopen("text.txt", "w");
	//qianxu(bt);
	while (ju != 'n') {
		printf("请选择功能：1，增加网址；2，查询网址;3,退出系统\n");
		scanf("%d", &xuan);
		getchar();
		if (xuan == 3) {
			qianxu(bt, fp2);
			exit(0);
		}
		printf("请输入地址：");
		scanf("%s", &str);
		getchar();
		int i = 0;
		token = strtok(str, ".");
		while (token != NULL) {
			strcpy(fenge[i], token);
			i++;
			token = strtok(NULL, ".");
		}
		switch (xuan) {
			case 1:
				printf("请输入ip：");
				scanf("%s", &ip);
				getchar();
				bt = tianjia(bt, fenge, --i, ip);
				break;
			case 2:
				jiediangeshu(bt, fenge, --i);
				break;
		}
		printf("是否继续？y/n\n");
		scanf("%c", &ju);
		//qianxu(bt, fp2);
		getchar();
	}
	qianxu(bt, fp2);
	fclose(fp2);
	fclose(fp1);
	printf("谢谢使用");
}
/*
测试数据
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
*/


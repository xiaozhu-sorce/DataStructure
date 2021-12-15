#include "base.h"
#include "data.h"
#include "fileFunc.cpp"

#define MAX_TOKEN 20 // token最长数目
char passwd[MAX_TOKEN] = {0};
Status flag = true;

//需要输入token时候关闭和开启回显
char *GetPasswd()
{
        char c;
        int i = 0;
        int len = MAX_TOKEN - 1;
        system("stty -echo");
        while ((c = getchar()) != '\n')
        {
                passwd[i] = c;
                i++;
                if (i >= len)
                {
                        break;
                }
        }
        system("stty echo");

        return passwd;
}

//打开文件的基本操作
void OpenFile()
{
        Status s = TRUE;
        int k;
        InitString(T[0]);
        // cout<<"确认开始请点击enter键";
        while (getchar() == '\n' && s)
        {
                system("clear");
                cout << "请选择:<<endl" << endl;
                cout << "1.打开文件(新或旧)\t2.显示文件内容" << endl;
                cout << "3.插入行\t4.删除行" << endl;
                cout << "5.拷贝行\t6.修改行" << endl;
                cout << "7.查找字符串\t8.替换字符串" << endl;
                cout << "9.存盘退出\t0.放弃编辑" << endl;
                cin >> k;
                switch (k)
                {
                case 1:
                        Open();
                        break;
                case 2:
                        List();
                        break;
                case 3:
                        Insert();
                        break;
                case 4:
                        Delete();
                        break;
                case 5:
                        Copy();
                        break;
                case 6:
                        Modify();
                        break;
                case 7:
                        Search();
                        break;
                case 8:
                        Replace();
                        break;
                case 9:
                        Save();
                default:
                        s = FALSE;
                }
                fflush(stdin);
                cout << "确认请点击enter键。";
        }
}

void manage()
{
        Status fl = TRUE;
        int k;
        char *token = NULL;

        fflush(stdin);
        cout << "为确认您是否为管理员，请输入token:";
        token = GetPasswd();

        if (strcmp(token, "1") == 0)
        {
                LinkList La;
                InitList(La);                      //初始化链表
                strcpy(filename, "comInMall.txt"); //打开的文件名称
                Open();                            //打开文件
                getInfo_Mall(La);                  //把从文件中读取的数据重新存放到链表中
                showList_Mall(La);                 //用链表的形式展示
                cout << "确认请点击enter键。";

                while (getchar() == '\n' && fl)
                {
                        system("clear");
                        List();
                        cout << "----------------------------------------------------------------------------------------------" << endl;
                        cout << "1.下架商品\t2.补货\t3.进货\t4.修改商品信息\t5.模糊查询商品信息\t6.确认修改\t其他按键自动退出" << endl;
                        cout << "----------------------------------------------------------------------------------------------" << endl;
                        cin >> k;
                        switch (k)
                        {
                        case 1:
                                Delete();
                                break;
                        case 2:
                                Modify();
                                break;
                        case 3:
                                Insert();
                                break;
                        case 4:
                                Modify();
                                break;
                        case 5:
                                Search();
                                break;
                        case 6:
                                Save();
                                break;
                        default:
                                fl = FALSE;
                        }
                        fflush(stdin);
                        cout << "确认请点击enter键。";
                }
        }
        else
        {
                cout << "很遗憾，您的token输入错误。" << endl;
                flag = true;
        }
}

//根据文件内容打印发票（某个客人的商品清单）
void Print(LinkList &La)
{
        time_t t;
        struct tm *lt;
        time(&t);
        lt = localtime(&t);

        cout << "以下为您的购物小票" << endl;
        printf("当前时间:%d/%d/%d %d:%d:%d", lt->tm_year + 1900, 1 + lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);

        InitList(La);
        getInfo_Cart(La);
        showList_Cart(La);
}

//打开文件conInCus.txt。列出超市内部可以供应的商品。
void shopping()
{
        int a, b;
        printf("*********************************************************\n");
        printf("                欢迎进入超市信息管理系统\n");
        printf("*********************************************************\n");
        InitString(T[0]);

        LinkList La;
        InitList(La); //初始化链表

        strcpy(filename, "comInCus.txt");
        Open();           //打开文件
        getInfo_Cus(La);  //把从文件中读取的数据重新存放到链表中
        showList_Cus(La); //用链表的形式展示
        Save();           //将T字符串清空

        strcpy(filename, "cart.txt");
        Open();
        while (1)
        {
                Buy();
                cout << "您是否要继续购买商品？(继续购买输入1，否则输入2)" << endl;
                cin >> a;
                if (a == 2)
                {
                        cout << "请问您是否确认需要购买一下商品" << endl;
                        List();
                        cout << "确认请输入Enter键，撤销输入任意字符" << endl;
                        fflush(stdin);
                        if (getchar() == '\n')
                        {
                                Print(La);
                                Save();
                        }
                        cout << "谢谢惠顾!" << endl;
                        break;
                }
        }
}

int main()
{
        int identity;
        while (flag)
        {
                flag = false;
                cout << "请选择您的身份(1.店内工作人员    2.顾客):";
                cin >> identity;
                if (identity == 1)
                {
                        manage();
                }
                else if (identity == 2)
                {
                        shopping();
                }
                else
                {
                        cout << "输入有误，请重新输入。" << endl;
                        flag = true;
                }
        }
        return 0;
}
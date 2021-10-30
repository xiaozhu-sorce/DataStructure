#include"base.h"
#include"data.h"
#include"fileFunc.cpp"

#define MAX_TOKEN 20 //token最长数目

void OpenFile()
{
        Status s=TRUE;
        int k;
        InitString(T[0]);
        // cout<<"确认开始请点击enter键";
        while(getchar()=='\n' && s)
        {
                system("clear");
                cout<<"请选择:1.打开文件(新或旧) 2.显示文件内容\n";
                cout<<"        3.插入行 4.删除行 5.拷贝行 6.修改行\n";
                cout<<"        7.查找字符串    8.替换字符串\n"; 
                cout<<"        9.存盘退出      0.放弃编辑\n";
                cin>>k;
                switch(k)
                {
                        case 1: Open();
                                break;
                        case 2: List();
                                break;
                        case 3: Insert();
                                break;
                        case 4: Delete();
                                break;
                        case 5: Copy();
                                break;
                        case 6: Modify();
                                break;
                        case 7: Search();
                                break;
                        case 8: Replace();
                                break;
                        case 9: Save();
                        default: s=FALSE;
                }
                fflush(stdin);
                cout<<"确认请点击enter键。"; 
        }
}

void manage()
{
        char token[MAX_TOKEN];
        cout<<"为确认您是否为管理员，请输入token";
        cin>>token;
        if(strcmp(token,"20211026") == 0){
                strcpy(filename,"comInMall.txt");
                OpenFile();
        }
}

//打开文件conInCus.txt。列出超市内部可以供应的商品。
void shopping()
{       
        cout<<"\t欢迎来到十月奇迹超市"<<endl;
        InitString(T[0]);
        strcpy(filename,"comInCus.txt");
        Open();
        List();
        Save();//将T字符串清空
        strcpy(filename,"cart.txt");
        Open();
        List();
        cout<<"以上为超市供应物品，请根据商品进行按需选购。"<<endl;
        
}

int main()
{
        // Status flag = true;
        // int identity;
        // while(flag)
        // {
        //         flag = false;
        //         cout<<"请选择您的身份(1.店内工作人员    2.顾客)：";
        //         cin >> identity;
        //         if(identity == 1)
        //         {
        //                 manage();
        //         }else if(identity == 2)
        //         {
        //                 shopping();
        //         }else
        //         {s
        //                 cout<<"输入有误，请重新输入。"<<endl;
        //                 flag = true;
        //         }
        // }

        LinkList La;
        InitList(La);
        strcpy(filename,"comInMall.txt");
        Open();
        List();
        getInfo(La);
        showList(La);
        return 0;
}
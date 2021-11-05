#include"base.h"
#include"data.h"
#include"fileFunc.cpp"

#define MAX_TOKEN 20 //token最长数目
char passwd[MAX_TOKEN] = {0};  
Status flag = true;
    
//需要输入token时候关闭和开启回显
char *GetPasswd()  
{  
    char c;  
    int i = 0;  
    int len = MAX_TOKEN-1;  
    system("stty -echo");   
    while ((c=getchar())!='\n')  
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

void OpenFile()
{
        Status s=TRUE;
        int k;
        InitString(T[0]);
        // cout<<"确认开始请点击enter键";
        while(getchar()=='\n' && s)
        {
                system("clear");
                cout<<"请选择:<<endl"<<endl;
                cout<<"1.打开文件(新或旧)\t2.显示文件内容"<<endl;
                cout<<"3.插入行\t4.删除行"<<endl;
                cout<<"5.拷贝行\t6.修改行"<<endl;
                cout<<"7.查找字符串\t8.替换字符串"<<endl; 
                cout<<"9.存盘退出\t0.放弃编辑"<<endl;
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
        int k; 
        char *token = NULL;

        fflush(stdin);
        cout<<"为确认您是否为管理员，请输入token:";
        token = GetPasswd(); 

        if(strcmp(token,"1") == 0)
        {
                LinkList La;
                InitList(La);//初始化链表
                strcpy(filename,"comInMall.txt");//打开的文件名称
                Open();//打开文件
                getInfo(La);//把从文件中读取的数据重新存放到链表中
                showList(La);//用链表的形式展示

                system("clear");
                cout<<"请选择:"<<endl;
                cout<<"1.下架商品\t\t2.补货"<<endl;
                cout<<"3.进货\t\t\t4.修改商品信息"<<endl;
                cout<<"5.模糊查询商品信息\t6.放弃修改"<<endl;
                cin>>k;
                switch(k)
                {
                        case 1: Delete();
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
                        default: ;
                }
        }else
        {
                cout<<"很遗憾，您的token输入错误。"<<endl;
                flag = true;
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
        int identity;
        while(flag)
        {
                flag = false;
                cout<<"请选择您的身份(1.店内工作人员    2.顾客)：";
                cin >> identity;
                if(identity == 1)
                {
                        manage();
                }else if(identity == 2)
                {
                        shopping();
                }else
                {
                        cout<<"输入有误，请重新输入。"<<endl;
                        flag = true;
                }
        }
        return 0;
}
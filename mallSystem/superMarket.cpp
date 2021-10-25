#include"linkFunc.cpp"
#include"fileFunc.cpp"

void OpenFile()
{
        Status s=TRUE;
        int k;
        InitString(T[0]);
        cout<<"确认开始请点击enter键";
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

int main()
{
        Status flag = true;
        int identity;
        while(flag)
        {
                flag = false;
                cout<<"请选择您的身份：(1.店内工作人员    2.顾客)";
                cin >>identity;
                if(identity == 1)
                {

                }else if(identity == 2)
                {

                }else
                {
                        cout<<"输入有误，请重新输入。";
                        flag = true;
                }
        }
        OpenFile();
        return 0;
}
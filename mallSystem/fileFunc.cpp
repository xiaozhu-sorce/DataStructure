#include"stringFunc.cpp"
#include"linkFunc.cpp"
#define MAX_LEN 30 // 文件最大行数
#define LINE_LEN 75 // 每行字符数最大值+1
#define NAME_LEN 20 // 文件名最大长度(包括盘符、路径)+1

HString T[MAX_LEN];
HString T2[MAX_LEN];
char str[LINE_LEN],filename[NAME_LEN]="";
FILE *fp;
int n=1; // 文本行数

// 打开文件(新或旧)
void Open();
// 显示文本内容 
void List();
// 插入行
void Insert();
// 删除行
void Delete();
// 拷贝行
void Copy();
// 修改行 
void Modify();
// 查找字符串
void Search();
// 替换字符串
void Replace();
// 存盘 
void Save();
// 使用链表读取文件内部信息，将其中一行的数据存放在一个链表的节点中
void getInfo(LinkList &L);

// 打开文件(新或旧)
void Open()
{ 
    fp=fopen(filename,"r"); // 以读的方式打开文件
    if(fp) // 已存在此文件
    {
        while(fgets(str,LINE_LEN,fp)) // 由文件读入1行字符存储到str中 
        {
            // str[strlen(str)-1]=0; // 将换行符10强制改为串结束符0 
            if(n>=MAX_LEN)
            {
                printf("文件太大\n");
                return; 
            }
            StrAssign(T[n],str);
            StrAssign(T2[n],str);
            n++; 
        }
        fclose(fp); // 关闭文件 
    }
}

// 显示文本内容 
void List()
{ 
    int i;
    for(i=1;i<n;i++)
    {
        printf("%3d| ",i);
        StrPrint(T[i]);
    }
}

// 插入行
void Insert()
{ 
    int i,l,m; 
    printf("在第l行前插m行,请输入l m: "); 
    scanf("%d%d%*c",&l,&m); 
    if(n+m>MAX_LEN)
    {
        printf("插入行太多\n");
        return; 
    }
    if(n>=l-1&&l>0)
    {
        for(i=n-1;i>=l-1;i--)
            StrCopy(T[i+m],T[i]);
        n+=m; 
        printf("请顺序输入待插入内容:\n"); 
        for(i=l-1;i<l-1+m;i++)
        {
            cin >> str;
            InitString(T[i]);
            StrAssign(T[i],str);
        } 
    }
    else printf("行超出范围\n");
}

//最后一行插入（商品购买）
void Buy()
{
    if(n+1 > MAX_LEN){
        cout<<"商品购买过多～"<<endl;
        return;
    }
    cin >> str;
    InitString(T[n]);
    StrAssign(T[n],str);
}

// 删除行
void Delete()
{ 
    int i,l,m; 
    printf("从第l行起删除m行,请输入l m: "); 
    scanf("%d %d",&l,&m);
    if(n>=l+m-1&&l>0)
    {
        for(i=l-1+m;i<n;i++)
        {
            if(!T[i-m].ch)
                free(T[i-m].ch);
            StrCopy(T[i-m],T[i]);
        }
        for(i=n-m;i<n;i++)
            InitString(T[i]);
        n-=m; 
    }
    else printf("行超出范围\n");
}

// 拷贝行
void Copy()
{ 
    int i,l,m,k; 
    printf("把第l行开始的m行插在原k行之前,请输入l m k: "); 
    scanf("%d%d%d",&l,&m,&k);
    if(n+m>MAX_LEN)
    {
        printf("拷贝行太多\n");
        return; 
    }
    if(n>=k-1&&n>=l-1+m&&(k>=l+m||k<=l))
    {
        for(i=n-1;i>=k-1;i--)
            T[i+m]=T[i];
        n+=m;
        if(k<=l)
            l+=m;
            for(i=l-1;i<l-1+m;i++)
            {
                InitString(T[i+k-l]);
                StrCopy(T[i+k-l],T[i]);
            }
    } else
    printf("行超出范围\n"); 
}

// 修改行 
void Modify()
{ 
    int i;
    printf("请输入待修改的行号: "); 
    scanf("%d%*c",&i); 
    if(i>0&&i<=n)
    {
        printf("%d: ",i); 
        StrPrint(T[i-1]); 
        printf("请输入新内容: "); 
        cin >> str;
        StrAssign(T[i-1],str);
    } else
    printf("行号超出范围\n"); 
}

// 查找字符串
void Search()
{ 
    int i,k,f=1; // f为继续查找标志 
    char b[2];
    HString s; 
    printf("请输入待查找的物品任意信息: "); 
    scanf("%s%*c",str); 
    InitString(s);
    StrAssign(s,str); 
    for(i=0;i<n && f;i++) // 逐行查找
    {
        k=1; // 由每行第1个字符起查找 
        while(k)
        {
            k=Index(T[i],s,k); // 由本行的第k个字符开始查找 
            if(k) // 找到
            {
                printf("第%d行: ",i+1);
                StrPrint(T[i]); 
                printf("第%d个字符处找到。继续查找吗(Y/N)? ",k); 
                cin>>b;
                if(b[0]!='Y'&&b[0]!='y') // 中断查找
                {
                    f=0; 
                    break;
                } else k++; 
            }
        } 
    }
    if(f) printf("未能查找到您所需要查找的关键字\n");
}

// 替换字符串
void Replace()
{
    int i,k,f=1; // f为继续替换标志
    char b[2];
    HString s,t; 
    printf("请输入待替换的字符串: "); 
    scanf("%s%*c",str);
    InitString(s);
    StrAssign(s,str);
    printf("替换为");
    scanf("%s%*c",str);
    InitString(t);
    StrAssign(t,str);
    for(i=0;i<n&&f;i++) // 逐行查找、替换 
    {
        k=1; // 由每行第1个字符起查找 
        while(k)
        {
            k=Index(T[i],s,k); // 由本行的第k个字符开始查找 
            if(k) // 找到
            {
                printf("第%d行: ",i+1);
                StrPrint(T[i]); printf("第%d个字符处找到。是否替换(Y/N)? ",k);
                cin>>b;
                if(b[0]== 'Y'||b[0]== 'y') 
                {
                    StrDelete(T[i],k,StrLength(s));
                    StrInsert(T[i],k,t);
                }
                printf("继续替换吗(Y/N)?");
                cin>>b;
                if(b[0]!= 'Y'&&b[0]!= 'y') // 中断查找、替换 
                {
                    f=0;
                    break; 
                }else
                    k+=StrLength(t);
            } 
        }
    } 
    if(f) printf("没找到\n"); 
}

// 存盘 
void Save()
{ 
    int i,j;
    fp=fopen(filename,"w"); // 以写的方式重新打开文件 
    if(fp) // 打开文件成功
    {
        for(i=0;i<n;i++)
        { // 依次将每行存入文件
            for(j=0;j<T[i].length;j++) // 依次存入每个字符 
                fputc(T[i].ch[j],fp);
            // fputc(10,fp); // 存入换行符
            ClearString(T[i]); // 释放串空间 
        }
        fclose(fp); // 关闭文件 
    }
    else printf("存盘失败\n");
}


// 使用链表读取文件内部信息，将其中一行的数据存放在一个链表的节点中
void getInfo_Mall(LinkList &L)
{
    int i,j;
    char *Pi[5];
    HString P;
    ClearList(L);

    for(i = 1;i < n ;i++){
        StrCopy(T2[i],T[i]);
    }
    
    for(i = 1;i<n;i++)
    {
        for(j=0;j<5;j++)
        {
            InitString(P);
            P.ch = (char *)malloc(StrLength(T[i])/4*sizeof(char));
            Pi[j] = (char *)malloc(StrLength(T[i])/4*sizeof(char));
            if(!P.ch)
                exit(OVERFLOW);
            StrCat(T2[i],P);
            StrConvert(P,Pi[j]);
        }
        if(i == 1)
            cout<<endl<<Pi[0]<<"\t"<<Pi[1]<<" \t"<<Pi[2]<<"\t"<<Pi[3]<<"\t"<<Pi[4];
        else
            AddGood_Mall(L,Pi[0],Pi[1],Pi[2],atof(Pi[3]),atof(Pi[4]));
    }
}

// 使用链表读取文件内部信息，将其中一行的数据存放在一个链表的节点中
void getInfo_Cus(LinkList &L)
{
    int i,j;
    char *Pi[3];
    HString P;
    ClearList(L);

    for(i = 1;i < n ;i++){
        StrCopy(T2[i],T[i]);
    }
    
    for(i = 1;i<n;i++)
    {
        for(j=0;j<3;j++)
        {
            InitString(P);
            P.ch = (char *)malloc(StrLength(T[i])/4*sizeof(char));
            Pi[j] = (char *)malloc(StrLength(T[i])/4*sizeof(char));
            if(!P.ch)
                exit(OVERFLOW);
            StrCat(T2[i],P);
            StrConvert(P,Pi[j]);
        }
        if(i == 1)
            cout<<endl<<Pi[0]<<"\t"<<Pi[1]<<"\t"<<Pi[2];
        else
            AddGood_Cus(L,Pi[0],Pi[1],atof(Pi[2]));
    }
}
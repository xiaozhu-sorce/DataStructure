#define DestroyString ClearString

// 初始化(产生空串)字符串T。另加 T.length=0;
void InitString(HString &T);
//生成一个其值等于串常量chars的串T
void StrAssign(HString &T,char *chars);
//由串S复制得串T 
void StrCopy(HString &T,HString S);
//若S为空串，则返回TRUE;否则返回FALSE 
Status StrEmpty(HString S);
// 若S>T，则返回值>0;若S=T，则返回值=0;若S<T，则返回值<0 
int StrCompare(HString S,HString T);
// 返回S的元素个数，称为串的长度 
int StrLength(HString S);
// 将S清为空串 
void ClearString(HString &S);
// 用T返回由S1和S2联接而成的新串 
void Concat(HString &T,HString S1,HString S2);
// 用Sub返回串S的第pos个字符起长度为len的子串。其中,1≤pos≤StrLength(S)且0≤len≤StrLength(S)-pos+1 
Status SubString(HString &Sub, HString S,int pos,int len);
// T为非空串。若主串S中第pos个字符之后存在与T相等的子串，则返回第一个这样的子串在S中的位置;否则返回0 
int Index(HString S,HString T,int pos);
// 1≤pos≤StrLength(S)+1。在串S的第pos个字符之前插入串T
Status StrInsert(HString &S,int pos,HString T);
// 从串S中删除第pos个字符起长度为len的子串 
Status StrDelete(HString &S,int pos,int len);
// 串S，T和V存在，T是非空串,用V替换主串S中出现的所有与T相等的不重叠的子串 
Status Replace(HString &S,HString T,HString V);
// 输出T字符串
void StrPrint(HString T);


// 初始化(产生空串)字符串T。另加 T.length=0;
void InitString(HString &T)
{ 
    T.ch=NULL;
    T.length = 0;
}

//生成一个其值等于串常量chars的串T
void StrAssign(HString &T,char *chars)
{ 
    int i,j;
    if(T.ch)
        free(T.ch); // 释放T原有空间 
    i=strlen(chars); // 求chars的长度i 
    if(!i)
    {
        T.ch=NULL;
        T.length=0;
    }
    else
    {
        T.ch=(char*)malloc(i*sizeof(char)); // 分配串空间 
        if(!T.ch) // 分配串空间失败
            exit(OVERFLOW); 
        for(j=0;j<i;j++) // 拷贝串
            T.ch[j]=chars[j];
        T.length=i;
    } 
}

//生成一个其值等于T.ch的字符串chars
void StrConvert(HString &T,char *chars)
{
    int len = T.length;
    if(strlen(chars)!=0)
        free(chars);
    // chars = (char *)malloc(len*sizeof(char));
    if(!chars)
        exit(OVERFLOW);
    for (int i = 0; i < len; i++)
    {   
        chars[i] = T.ch[i];
    }
}

//由串S复制得串T 
void StrCopy(HString &T,HString S)
{ 
    int i;
    if(T.ch)
    free(T.ch); // 释放T原有空间
    T.ch=(char*)malloc(S.length*sizeof(char)); // 分配串空间 
    if(!T.ch) // 分配串空间失败
        exit(OVERFLOW); 
    for(i=0;i<S.length;i++) // 拷贝串
        T.ch[i]=S.ch[i];
    T.length=S.length;
}

//若S为空串，则返回TRUE;否则返回FALSE 
Status StrEmpty(HString S)
{ 
    if(S.length==0&&S.ch==NULL)
        return TRUE;
    else
        return FALSE;
}

// 若S>T，则返回值>0;若S=T，则返回值=0;若S<T，则返回值<0 
int StrCompare(HString S,HString T)
{ 
    int i;
    for(i=0;i<S.length && i<T.length;i++)
        if(S.ch[i]!=T.ch[i])
            return S.ch[i]-T.ch[i];
    return S.length-T.length;
}

// 返回S的元素个数，称为串的长度 
int StrLength(HString S)
{ 
    return S.length;
}

// 将S清为空串 
void ClearString(HString &S)
{ 
    free(S.ch);
    S.ch=NULL;
    S.length=0;
}

// 用T返回由S1和S2联接而成的新串 
void Concat(HString &T,HString S1,HString S2)
{ 
    int i;
    if(T.ch)
        free(T.ch); // 释放旧空间
    T.length=S1.length + S2.length;
    T.ch=(char *)malloc(T.length*sizeof(char));
    if(!T.ch)
        exit(OVERFLOW);
    for(i=0;i<S1.length;i++)
        T.ch[i]=S1.ch[i];
    for(i=0;i<S2.length;i++)
        T.ch[S1.length+i]=S2.ch[i];
}

// 用Sub返回串S的第pos个字符起长度为len的子串。其中,1≤pos≤StrLength(S)且0≤len≤StrLength(S)-pos+1 
Status SubString(HString &Sub, HString S,int pos,int len)
{ 
    int i; 
    if(pos<1 ||pos>S.length|| len<0|| len>S.length-pos+1)
        return ERROR;
    if(Sub.ch)
        free(Sub.ch);
    if(!len) // 空子串
    {
        Sub.ch=NULL;
        Sub.length=0;
    }else{
        Sub.ch=(char*)malloc(len*sizeof(char));
        if(!Sub.ch)
            exit(OVERFLOW);
        for(i=0;i<=len-1;i++)
            Sub.ch[i]=S.ch[pos-1+i];
        Sub.length=len;
    }
    return OK; 
}

// T为非空串。若主串S中第pos个字符之后存在与T相等的子串，则返回第一个这样的子串在S中的位置;否则返回0 
int Index(HString S,HString T,int pos)
{ 
    int n,m,i;
    HString sub;
    InitString(sub);
    if(pos>0) {
        n=StrLength(S);
        m=StrLength(T);
        i=pos;
        while(i<=n-m+1)
        {
            SubString(sub,S,i,m);
            if(StrCompare(sub,T)!=0)
                ++i; 
            else
                return i; 
        }
    }
    return 0; 
}

// 1≤pos≤StrLength(S)+1。在串S的第pos个字符之前插入串T
Status StrInsert(HString &S,int pos,HString T)
{ 
    int i;
    if(pos<1||pos>S.length+1) // pos不合法
        return ERROR;
    if(T.length) // T非空，则重新分配空间，插入T 
    {
        S.ch=(char*)realloc(S.ch,(S.length+T.length)*sizeof(char));
        if(!S.ch)
            exit(OVERFLOW);
        for(i=S.length-1;i>=pos-1;--i) // 为插入T而腾出位置
            S.ch[i+T.length]=S.ch[i];
        for(i=0;i<T.length;i++)
            S.ch[pos-1+i]=T.ch[i]; // 插入T 
        S.length+=T.length;
    }
    return OK;
}

// 从串S中删除第pos个字符起长度为len的子串 
Status StrDelete(HString &S,int pos,int len)
{ 
    int i;
    if(S.length<pos+len-1)
        return ERROR;
    for(i=pos-1;i<=S.length-len;i++)
        S.ch[i]=S.ch[i+len];
    S.length-=len;
    S.ch=(char*)realloc(S.ch,S.length*sizeof(char));
    return OK;
}

// 串S，T和V存在，T是非空串,用V替换主串S中出现的所有与T相等的不重叠的子串 
Status Replace(HString &S,HString T,HString V)
{ 
    int i=1; // 从串S的第一个字符起查找串T
    if(StrEmpty(T)) // T是空串
        return ERROR;
    do
    {
        i=Index(S,T,i); // 结果i为从上一个i之后找到的子串T的位置 
        if(i) // 串S中存在串T
        {
            StrDelete(S,i,StrLength(T)); // 删除该串T 
            StrInsert(S,i,V); // 在原串T的位置插入串V 
            i+=StrLength(V); // 在插入的串V后面继续查找串T
        }
    }while(i);

    return OK;
}

// 输出T字符串
void StrPrint(HString T)
{ 
    int i;
    for(i=0;i<T.length;i++)
        printf("%c",T.ch[i]);
    printf("\n");
}

// 将串T以'|'字符分割为两个字符串，将分割出来的字符串存储在S中，断开的字符串继续存储到T中
void StrCat(HString &T,HString &S)
{
    int i,j,k=0;
    for(i=0;i<T.length;i++)
    {
        if(T.ch[i] == '|')
        {
            break;
        }
        S.ch[i] = T.ch[i];
        S.length++;
    }
    for(j=i+1;j<T.length;j++)
    {
        T.ch[k++] = T.ch[j];
    }
    T.length -=i;
    T.length--;
}
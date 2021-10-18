#define DestroyString ClearString

//生成一个其值等于chars的串T
Status StrAssign(SString T,char *chars)
{
    int i;
    if(strlen(chars) > MAX_STR_LEN)
        return ERROR;
    else
    {
        T[0] = strlen(chars);
        for ( i = 1; i <= T[0]; i++)
        {
            T[i] = *(chars+i-1);
        }
        return OK;
    }
}

//又串S复制得到串T
void StrCopy(SString T,SString S)
{
    int i;
    for(i = 0; i <= S[0];i++)
        T[i] = S[i];
}

//判断是否为空串
Status StrEmpty(SString S)
{
    if(S[0] == 0)
        return TRUE;
    else
        return FALSE;
}

//串S和T存在。若S>T.则返回值>0;若S=T,则返回值为0,若S<T，则返回值<0;
int StrCompare(SString S,SString T)
{
    int i;
    for ( i = 1; i < S[0] && i < T[0]; ++i)
        if(S[i]!=T[i])
            return S[i] - T[i];
        return S[0]-T[0];    
}

//返回S的元素个数
int StrLength(SString S)
{
    return S[0];
}

//将S清空为空串
void ClearString(SString S)
{
    S[0] = 0;
}

//用T返回S1和S2连接而成的新串。若未截断，则返回TRUE；否则返回FALSE
Status Concat(SString T,SString S1,SString S2)
{
    int i;
    //未截断
    if (S1[0]+S2[0] <= MAX_STR_LEN)
    {
        for(i=1; i<S1[0];i++)
            T[i] = S1[i];
        for(i=1; i<S2[0];i++)
            T[S1[0]+i] = S2[i];
        T[0] = S1[0]+S2[0];
        return TRUE;
    }
    //截断S2
    else
    {
        for(i=1; i<S1[0];i++)
            T[i] = S1[i];
        for(i=1; i<MAX_STR_LEN-S1[0];i++)
            T[S1[0]+i] = S1[i];
        T[0] = MAX_STR_LEN;
        return FALSE;
    }
}

//用Sub返回串S的第pos个字符起长度为len的子串
Status SubString(SString Sub,SString S,int pos,int len)
{
    int i;
    if(pos<1 ||pos>S[0] ||len<0 ||S[0]-pos+1)
        return FALSE;
    for ( i = 1; i < len; i++)
        Sub[i]=S[pos+i-1];
    Sub[0] = len;
    return OK;
}

//返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数值为0
int Index(SString S,SString T,int pos)
{
    int i,j;
    if(1<=pos && pos<=S[0])
    {
        i=pos;
        j=1;
        while (i<=S[0] && j<=T[0])
            if(S[i] == T[j])
            {
                ++j;
                ++i;
            }
            else //指针后退重新开始匹配
            {
                i=i-j+2;
                j=1;
            }
        if(j>T[0])
            return i-T[0];
        else   
            return 0;
    }
    else
        return 0;
}

//在串S的第pos个字符之前插入串T。完全插入返回TRUE，部分插入返回TRUE，部分插入返回FALSE；
Status StrInsert(SString S,int pos,SString T)
{
    int i;
    if(pos<1 ||pos>S[0]+1)
        return ERROR;
    
    if (S[0]+T[0]<=MAX_STR_LEN)
    {//完全插入
        for ( i = S[0]; i >= pos; i--)
            S[i+T[0]]=S[i];
        for(i=pos;i<pos+T[0];i++)
            S[i]=T[i-pos+1];
        S[0]+=T[0];
        return TRUE;
    }
    else
    {//部分插入
        for(i=MAX_STR_LEN;i>=pos+T[0];i--)
            S[i]=S[i-T[0]];
        for(i=pos;i<pos+T[0]&&i<=MAX_STR_LEN;i++)
            S[i]=T[i-pos+1];
        S[0] = MAX_STR_LEN;
        return FALSE;
    }
}

//从S中删除自第pos个字符起长度为len的子串
Status StrDelete(SString S,int pos,int len)
{
    int i;
    if(pos<1|| pos>S[0]-len+1|| len<0)
        return ERROR;
    for (i = pos+len; i <= S[0]; i++)
        S[i-len]=S[i];
    S[0]-=len;
    return OK;
}

//用V替换主串S中出现的所有与T相等的不重叠的子串
Status Replace(SString S,SString T,SString V)
{
    int i;
    Status k;
    if(StrEmpty(T))
        return ERROR;
    do
    {
        i=Index(S,T,i);
        if(i)
        {
            StrDelete(S,i,StrLength(T));
            k = StrInsert(S,i,V);
            if(!k)
                return ERROR;
            i+=StrLength(V);
        }
    } while (i);
    return OK;
}

//输出字符串T
void StrPrint(SString T)
{
    int i;
    for(i=1;i<=T[0];i++)
        printf("%c",T[i]);
    printf("\n");
}
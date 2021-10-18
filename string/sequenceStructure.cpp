#define DestroyString ClearString

#include"../c1.h"
#include"base.h"

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
    
}
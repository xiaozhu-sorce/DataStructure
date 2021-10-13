#include"c1.h"
#include"c2-1.h"

Status equal(ElemType c1,ElemType c2)
{
    if(c1 == c2)
        return TRUE;
    else   
        return FALSE;
}

int comp(ElemType a ,ElemType b)
{
    if(a==b)
        return 0;
    else    
        return (a-b)/abs(a-b);
}

void printf(ElemType c)
{
    printf("%d",c);
}

void printf2(ElemType c)
{
    printf("%c",c);
}

void printf(ElemType &c)
{
    printf("%d",c);
}
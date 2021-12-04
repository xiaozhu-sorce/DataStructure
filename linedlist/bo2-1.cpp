//初始化线性表
void InitList(SqList &L)
{
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.elem){
        exit(OVERFLOW);
    }
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
}

//销毁线性表
void DestroyList(SqList &L)
{
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
}

//清空线性表
void ClearList(SqList L)
{
    L.length = 0;
}

//判断线性表是否为空
Status ListEmpty(SqList L)
{
    if(L.length == 0)
        return TRUE;
    else    
        return FALSE;
}

//返回线性表的长度
int ListLength(SqList L)
{
    return L.length;
}

//用e返回L中的第i个数据元素的值
Status GetElem(SqList L,int i,ElemType &e)
{
    if(i<1||i>L.length)
        return ERROR;
    e=*(L.elem+i-1);
    return OK;
}

//compare（）是数据元素判定函数（满足为1，否则为0）
int LocateElem(SqList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    ElemType *p;
    int i=1;
    p = L.elem;
    while (i <= L.length && !compare(*p++,e))
    {
        ++i;
    }
    if(i<=L.length)
        return i;
    else
        return 0;
}

//返回cur_e的前驱元素
Status PriorElem(SqList L,ElemType cur_e,ElemType &pre_e)
{
    int i = 2;
    ElemType *p=L.elem+1;
    while (i <= L.length && *p!=cur_e)
    {
        p++;
        i++;
    }
    if(i > L.length)
        return INFEASIBLE;
    else
    {
        pre_e = *--p;
        return OK;
    }
}

//返回cur_e的后驱元素
Status NextElem(SqList L,ElemType cur_e,ElemType &next_e)
{
    int i = 1;
    ElemType *p =L.elem;
    while (i < L.length && *p!=cur_e)
    {
        i++;
        p++;
    }
    if(i==L.length)
        return INFEASIBLE;
    else
    {
        next_e = *++p;
        return OK;
    }
    
}

//在L中第i个位置之前插入新的元素e，L的长度加1
Status ListInsert(SqList &L,int i,ElemType e)
{
    ElemType *newbase,*q,*p;
    if(i < 1 || i > L.length+1)
    {
        if (!(newbase=(ElemType *)realloc(L.elem,(L.listsize + LIST_INCREMENT) * sizeof(ElemType))))
            exit(OVERFLOW);
        L.elem = newbase;
        L.listsize += LIST_INCREMENT;
    }
    q = L.elem+i-1;
    for(p = L.elem+L.length - 1;p>=q;--p)
        *(p+1) = *p;
    *q = e;
    ++L.length;
    return OK;
}

//删除L的第i个数据元素，并且用e返回其值，L的长度减1
Status ListDelete(SqList &L,int i,ElemType &e)
{
    ElemType *p,*q;
    if(i<1 || i>L.length)
        return ERROR;
    p = L.elem + i -1;
    for(++p;p<=q;++p)
        *(p-1) = *p;
    L.length--;
    return OK;
}

void ListTraverse(SqList L,void(*vi)(ElemType&))
{
    ElemType *p;
    int i;
    p = L.elem;
    for(i = 1;i <= L.length;i++)
        vi(*p++);
    printf("\n");
}
//初始化链表
void InitList(LinkList &L)
{
    L = (LinkList)malloc(sizeof(Node));
    if(!L)
        exit(OVERFLOW);
    L->data = 0;
    L->next=L;//将其构造为循环链表
}

//销毁链表
void DestroyList(LinkList &L)
{
    LinkList q;
    while(L)
    {
        q = L->next;
        free(L);
        L=q;
    }
}

//清空链表
void ClearList(LinkList L)
{
    LinkList p,q;
    p=L->next;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL;
}

//判断链表是否为空
Status ListEmpty(LinkList L)
{
    if(L->next)
        return FALSE;
    else   
        return TRUE;
}

//链表长度
int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next;
    //注意是不是循环链表
    while(p != L)
    {
        i++;
        p = p->next;
    }
    return i;
}

//当第i个元素存在时，其值赋给e并返回OK;
Status GetElem(LinkList L,int i,ElemType &e)
{
    int j=1;
    LinkList p = L->next;
    while (p &&j<i)
    {
        p = p->next;
        j++;
    }
    if(!p || j>i)
        return ERROR;
    e = p->data;
    return OK;
    
}

//在链表中的第i个元素之前插入e
Status ListInsert(LinkList L,int i,ElemType e)
{
    int j = 0;
    LinkList p=L,s;
    while (p && j<i)
    {
        p=p->next;
        j++;
    }
    if (!p || j>i-1)
        return ERROR;
    s= (LinkList)malloc(sizeof(LinkList));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

//删除第i个元素，并且由e返回其值
Status ListDelete(LinkList L,int i,ElemType e)
{
    int j = 0;
    LinkList p=L,q;
    while (p->next && j<i-1)
    {
        p=p->next;
        j++;
    }
    
    if(!p->next||j>i-1)
        return ERROR;
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}

//输出循环链表的每个节点的数据域
void showList(LinkList &L)
{
    LinkList p = L->next->next;
    while (p!=L->next)
    {
        cout<<" "<< p->data<<" ";
        p = p->next;
    }
    printf("\n");
}

void ListTraverse(LinkList L,void(*vi)(ElemType))
{
    LinkList p=L->next;
    while (p)
    {
        vi(p->data);
        p=p->next;        
    }
    printf("\n");
}

//在循环链表的尾部插入e；
void ListAdd(LinkList &LTail,ElemType e)
{
    LTail->next->data++;
    LinkList p = LTail->next,s;
    s= (LinkList)malloc(sizeof(Node));
    s->data = e;
    s->next = p;
    LTail->next = s;
    //LTail = s;错误？
    LTail = LTail->next;
}
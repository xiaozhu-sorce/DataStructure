//初始化循环链表
void InitList(LinkList &L);
//销毁链表
void DestroyList(LinkList &L);
//清空链表
void ClearList(LinkList &L);
//判断链表是否为空
Status ListEmpty(LinkList L);
//链表长度
int ListLength(LinkList L);
//当第i个元素存在时，其值赋给e并返回OK;
Status GetElem(LinkList L,int i,Goods &e);
//在链表中的第i个元素之前插入e
Status ListInsert(LinkList L,int i,Goods e);
//输出循环链表的每个节点的数据域
void showList_Mall(LinkList &L);
//输出货品的信息
void showGood_Mall(Goods &good);
//在链表的尾部插入商品信息；
void AddGood_Mall(LinkList &L,const char number[],const char n[],const char s[],double input,double output);

//输出循环链表的每个节点的数据域
void showList_Cus(LinkList &L);
//输出货品的信息
void showGood_Cus(Goods &good);
//在链表的尾部插入商品信息；
void AddGood_Cus(LinkList &L,const char number[],const char n[],const char s[],double input,double output);


//初始化循环链表
void InitList(LinkList &L)
{
    L = (LinkList)malloc(sizeof(Node));
    if(!L)
        exit(OVERFLOW);
    L->data = NULL;
    L->next=L;//循环
}

//销毁循环链表
void DestroyList(LinkList &L)
{
    LinkList q,p=L->next;
    while(p!=L)
    {
        q = p->next;
        free(p);
        p=q;
    }
    free(L);
    L=NULL;
}

//清空循环链表，将L重置为空表
void ClearList(LinkList &L)
{
    LinkList p,q;
    L=L->next;
    p=L->next;
    while(p!=L)
    {
        q=p->next;
        free(p);
        p=q;
    }
    L->next=L;
}

//判断循环链表是否为空
Status ListEmpty(LinkList L)
{
    if(L->next == L)
        return FALSE;
    else   
        return TRUE;
}

//循环链表长度
int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next;
    while(p!=L)
    {
        i++;
        p = p->next;
    }
    return i;
}

//当第i个元素存在时，其值赋给e并返回OK;
Status GetElem(LinkList L,int i,Goods &e)
{
    int j=1;
    LinkList p = L->next->next;
    if(i<=0||i>ListLength(L))
        return ERROR;
    while (j<i)
    {
        p = p->next;
        j++;
    }
    e = p->data;
    return OK;
}

//在循环链表中的第i个元素之前插入e
Status ListInsert(LinkList L,int i,Goods e)
{
    int j = 0;
    LinkList p=L->next,s;
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

//输出货品的信息
void showGood_Mall(Goods &good)
{
    cout<< good->ID<< "\t"<<good->name<< "     \t"<< good->stock << "\t"<< good->purchasingPrice<< "\t"<< good->sellingPrice<<endl;
}

//输出循环链表的每个节点的数据域
void showList_Mall(LinkList &L)
{
    LinkList p = L->next->next;
    while (p!=L->next)
    {
        showGood_Mall(p->data);
        p = p->next;
    }
    printf("\n");
}

//在链表的尾部插入商品信息；
void AddGood_Mall(LinkList &L,const char number[],const char n[],const char s[],double input,double output)
{
    L->next->data++;
    LinkList p = L->next,m;
    Goods e;
    m = (LinkList)malloc(sizeof(Node));
    e = (Goods)malloc(sizeof(Data));

    strcpy(e->ID,number);
    strcpy(e->name,n);
    strcpy(e->stock,s);
    e->purchasingPrice = input;
    e->sellingPrice = output;
    m->data = e;
    m->next = p;
    L->next = m;
    L = L->next;
}



//输出货品的信息
void showGood_Cus(Goods &good)
{
    cout<< good->ID<< "\t"<<good->name<< "     \t"<< good->sellingPrice<<endl;
}

//输出循环链表的每个节点的数据域
void showList_Cus(LinkList &L)
{
    LinkList p = L->next->next;
    while (p!=L->next)
    {
        showGood_Cus(p->data);
        p = p->next;
    }
    printf("\n");
}

//在链表的尾部插入商品信息；
void AddGood_Cus(LinkList &L,const char number[],const char n[],double output)
{
    L->next->data++;
    LinkList p = L->next,m;
    Goods e;
    m = (LinkList)malloc(sizeof(Node));
    e = (Goods)malloc(sizeof(Data));

    strcpy(e->ID,number);
    strcpy(e->name,n);
    e->sellingPrice = output;
    m->data = e;
    m->next = p;
    L->next = m;
    L = L->next;
}
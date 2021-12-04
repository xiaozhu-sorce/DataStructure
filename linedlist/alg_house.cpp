/**
 * 将两个循环有序链表合并。
 */
#include"../c1.h"
#include"c2-2.h"
#include"bo2-2.cpp"

void union_OL(LinkList &La,LinkList &Lb)
{
    LinkList pa,pb,rc,qb; 
    pa = La->next->next;
    pb = Lb->next->next;
    rc = La->next;
    while (pa != La->next && pb != Lb->next)
    {
        if(pa->data < pb->data)
        {
            rc->next = pa;
            rc = pa;
            pa = pa->next;
        }
        else if(pa->data > pb->data)
        {
            rc->next = pb;
            rc = pb;
            pb = pb->next;
        }
        else
        {
            rc->next=pa;
            rc = pa;
            pa = pa->next;
            qb = pb;
            pb = pb->next;
            delete(qb); 
        }
    }

    if(pb == Lb->next) rc->next = pa;
    else
    {
        rc->next = pb;pb = Lb->next;
        Lb->next = pa;La = Lb;
    }
    delete(pb);   
}

//对循环链表的数据域进行排序
void sortList(LinkList &L)
{
    int len = L->next->data;
    LinkList p; 
    p = L->next->next;
    for(int i = 0; i < len-1; i++){
        for(int j = 0; j < len-1-i; j++){
            if(p->data > p->next->data){
                int temp = p->data;
                p->data = p->next->data;
                p->next->data = temp;
            }
            p = p->next;
        }
        p = L->next->next;
    }
}

int main()
{
    int i;
    LinkList La,Lb;
    InitList(La);
    ElemType f;
    while (1)
    {
        cin>>f;
        ListAdd(La,f);
        if(cin.get() == '\n'){
            break;
        }
    }
    sortList(La);
    cout<<"La =";
    showList(La);

    InitList(Lb);
    while (1)
    {
        cin>>f;
        ListAdd(Lb,f);
        if(cin.get() == '\n'){
            break;
        }
    }
    sortList(Lb);
    cout<<"Lb =";
    showList(Lb);

    union_OL(La,Lb);
    cout<<"合并后的数组为";
    showList(La);
    return 0;
}
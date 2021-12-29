#include <iostream>
#include "../c1.h"
using namespace std;
int a[100];

typedef struct Node
{
    int data;
    Node *next;
} Node, *LinkList;

void InitList(LinkList &L)
{
    L = (LinkList)malloc(sizeof(Node));
    if (!L)
        exit(-1);
    L->data = 0;
    L->next = L;
}
void ListAdd(LinkList &LTail, int e)
{
    LTail->next->data++;
    LinkList p = LTail->next, s;
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    s->next = p;
    LTail->next = s;
    LTail = LTail->next;
}

void inNum(LinkList &LTail)
{
    int n;
    cout << "请输入所需要的整数的个数：";
    cin >> n;
    cout << "请输入n个数据：" << endl;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        a[i] = num;
    }
    for (int i = 0; i < n; i++)
    {
        cout << a[i];
    }
    for (int j = 0; j < n; j++)
    {
        ListAdd(LTail, a[j]);
    }
}

int GetElem(LinkList &L, int i, int e)
{
    int j = 1;
    LinkList p = L->next;
    while (p && j < i)
    {
        if (e == p->data)
            break;
        p = p->next;
        j++;
    }
    return j;
}

int ListLength(LinkList L)
{
    int i = 0;
    LinkList p = L->next;
    while (p != L)
    {
        i++;
        p = p->next;
    }
    return i;
}

int main()
{
    int x, f, length, n;
    LinkList L;
    InitList(L);
    inNum(L);

    length = ListLength(L);
    cout << "请输入您想要查找的值X:" << endl;
    cin >> x;
    cout << "X的位置 ：" << GetElem(L, length, x) << endl;
    cout << "链表节点个数为：" << length << endl;
    return 0;
}
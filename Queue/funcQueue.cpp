#include "base.h"
#include "../c1.h"

void InitQueue_L(LinkQueue &Q)
{
    if (!(Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode))))
        exit(OVERFLOW);
    Q.front->next = NULL;
}

void DestroyQueue_L(LinkQueue &Q)
{
    while (Q.front)
    {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
}

void EnQueue_L(LinkQueue &Q, QElemType e)
{
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
}

bool DeQueue_L(LinkQueue &Q, QElemType &e)
{
    if (Q.rear == Q.front)
        return FALSE;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    delete p;
    return TRUE;
}
#include "../c1.h"

const int QUEUE_INIT_SIZE = 100;
const int QUEUEINCREMENT = 10;

typedef int QElemType;

typedef struct
{
    QElemType *elem;
    int front;
    int rear;
    int queuesize;
    int incrementsize;
} SqQueue;

void InitQueue_Sq(SqQueue &Q, int maxsize = QUEUE_INIT_SIZE, int increasize = QUEUEINCREMENT)
{
    Q.elem = (QElemType *)malloc(sizeof(QElemType) * (maxsize + 1));
    Q.queuesize = maxsize;
    Q.incrementsize = increasize;
    Q.front = Q.rear = 0;
}

int QueueLength_Sq(SqQueue Q)
{
    return (Q.rear - Q.front + Q.queuesize) % Q.queuesize;
}

bool DeQueue_Sq(SqQueue &Q, QElemType &e)
{
    if (Q.rear == Q.front)
        return FALSE;
    e = Q.elem[Q.front];
    Q.front = (Q.front + 1) % Q.queuesize;
    return TRUE;
}

void incrementQueuesize(SqQueue &Q)
{
    QElemType a[];
    a = new QElemType[Q.queuesize + Q.incrementsize];
    // a = (QElemType *)malloc(sizeof(QElemType) * (Q.queuesize + Q.incrementsize));
    for (int k = 0; k < Q.queuesize - 1; k++)
        a[k] = Q.elem[(Q.front + k) % Q.queuesize];
    delete[] Q.elem;
    Q.elem = a;
    Q.front = 0;
    Q.rear = Q.queuesize - 1;
    Q.queuesize += Q.incrementsize;
}

void EnQueue_Sq(SqQueue &Q, QElemType e)
{
    if ((Q.rear + 1) % Q.queuesize == Q.rear)
        incrementQueuesize(Q);
    Q.elem[Q.rear] = e;
    Q.rear = (Q.rear + 1) % Q.queuesize;
}
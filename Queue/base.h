typedef int QElemType;

typedef struct QNode
{
    QElemType data;
    QNode *next;
} * QueuePtr;

typedef struct queue
{
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

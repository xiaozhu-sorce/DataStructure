#include <stdio.h>
#include <iostream>
using namespace std;

#define STACK_INIT_SIZE 100 // 存储空间初始分配量
#define STACK_INCREMENT 10  // 存储空间分配增量

const int MAX_X = 105, MAX_Y = 105;

typedef struct
{
    int xpos;
    int ypos;
} PosType;

typedef struct DQNode
{
    PosType seat;
    struct DQNode *next;
    struct DQNode *pre;
} DQNode, *DQueuePtr;

typedef struct
{
    DQueuePtr front;
    DQueuePtr rear;
} DLinkQueue;

typedef PosType SElemType;

// 栈的顺序存储结构
struct SqStack
{
    SElemType *base; // 在栈构造之前和销毁之后，base的值为NULL
    SElemType *top;  // 栈顶指针
    int stacksize;   // 当前已分配的存储空间，以元素为单位
};

void InitQueue(DLinkQueue &Q)
{
    Q.front = NULL;
    Q.rear = NULL;
}

void EnQueue(DLinkQueue &Q, SElemType e)
{
    DQNode *p = (DQNode *)malloc(sizeof(DQNode));
    p->seat.xpos = e.xpos;
    p->seat.ypos = e.ypos;
    p->next = NULL;
    if (!Q.rear)
    {
        p->pre = NULL;
        Q.rear = p;
        Q.front = p;
    }
    else
    {
        p->pre = Q.front;
        Q.rear->next = p;
        Q.rear = p;
    }
}

void GetHead(DLinkQueue Q, SElemType &e)
{
    e.xpos = Q.front->seat.xpos;
    e.ypos = Q.front->seat.ypos;
}

void DeQueue(DLinkQueue &Q)
{
    Q.front = Q.front->next;
}

bool QueueEmpty(DLinkQueue &Q)
{
    return (Q.front == NULL);
}

bool InitStack(SqStack &S)
{
    //构造一个空表
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base)
        return false;
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return true;
}

//插入e为新的栈顶元素
bool Push(SqStack &S, SElemType &e)
{
    if (S.top - S.base >= S.stacksize)
    {
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACK_INCREMENT) * sizeof(SElemType));
        if (!S.base)
            return false;
        S.top = S.base + S.stacksize; //因为S.base的内存是重新分配的，所以也要重新找S.top的位置。
        S.stacksize += STACK_INCREMENT;
    }
    *S.top++ = e;
    return true;
}

//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR；
bool Pop(SqStack &S, SElemType &e)
{
    if (S.top == S.base)
        return false;
    e = *(--S.top);
    return true;
}

//根据v来判断方位
PosType NextPos(PosType &npos, int v)
{
    PosType ele;
    ele.xpos = npos.xpos;
    ele.ypos = npos.ypos;
    int di[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dj[] = {1, 1, 0, -1, -1, -1, 0, 1};
    ele.xpos += di[v];
    ele.ypos += dj[v];
    return ele;
}

//是否能够通过，首先是进入的位置的坐标是否合格，之后判断是否为0.
bool Pass(int **map, int m, int n, SElemType npos)
{
    if (npos.xpos < 0 || npos.xpos > m - 1 || npos.ypos < 0 || npos.ypos > n - 1)
        return false;
    if (*((int *)map + n * npos.xpos + npos.ypos) != 0)
        return false;

    return true;
}

//寻找最短路径是否成功
bool ShortestPath(int **maze, int m, int n, SqStack &S)
{
    DLinkQueue Q;
    DQueuePtr p;
    bool visited[m][n];
    bool found = false;
    InitQueue(Q);

    PosType e, curpos, npos;

    int i, j, v;

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            visited[i][j] = false;

    if (*((int *)maze) != 0)
        return false;

    e.xpos = 0;
    e.ypos = 0;
    EnQueue(Q, e);

    while (!found && !QueueEmpty(Q))
    {
        GetHead(Q, curpos);
        for (v = 0; v < 8 && !found; v++)
        {
            npos = NextPos(curpos, v);

            //判断是否满足条件是否可以进队列
            if (visited[npos.xpos][npos.ypos] == false && Pass(maze, m, n, npos))
            {
                EnQueue(Q, npos);
                visited[npos.xpos][npos.ypos] = true;
            }

            //寻找结束的标志
            if (npos.xpos == m - 1 && npos.ypos == n - 1)
                found = true;
        }
        DeQueue(Q);
    }

    if (found)
    {
        cout << "恭喜你查找成功。以下为您需要走过的位置坐标(x,y)" << endl;
        InitStack(S);
        p = Q.rear;
        while (p)
        {
            Push(S, p->seat);
            p = p->pre;
        }

        SElemType ele;
        i = 1;
        while (Pop(S, ele))
        {
            cout << "第" << i++ << "个位置:";
            cout << ele.xpos << " " << ele.ypos << endl;
        }
        return true;
    }
    else
        return false;
}

int main()
{
    int m, n;
    bool fl = false;
    do
    {
        fl = false;
        cout << "请输入迷宫的长高:";
        cin >> m >> n;
        if (m < 0 || n < 0)
        {
            cout << "Please input the correct number" << endl;
            fl = true;
        }
        else
        {
            break;
        }
    } while (fl);

    int map[m][n];

    cout << "请输入您的迷宫路径"
         << "长宽分别为 " << m << " " << n << " 的矩形。" << endl;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    SqStack S;
    bool flag = ShortestPath((int **)map, 6, 8, S);
    return 0;
}
// int map[6][8] = {
//     {0, 1, 0, 1, 0, 0, 0, 1},
//     {1, 0, 0, 1, 1, 0, 1, 0},
//     {0, 1, 1, 0, 0, 1, 1, 1},
//     {1, 0, 0, 1, 1, 0, 0, 1},
//     {1, 0, 0, 0, 1, 1, 0, 1},
//     {0, 1, 1, 1, 0, 0, 0, 0}};

/*测试用例：
0 1 0 1 0 0 0 1
1 0 0 1 1 0 1 0
0 1 1 0 0 1 1 1
1 0 0 1 1 0 0 1
1 0 0 0 1 1 0 1
0 1 1 1 0 0 0 0
*/
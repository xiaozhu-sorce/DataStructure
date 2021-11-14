#include"../c1.h"

//销毁链表
void DestroyStack(SqStack &S){
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
}

void clearStack(SqStack &S){
    S.top = S.base;
}

//若S为空栈，则返回true，否则返回false；
Status StackEmpty(SqStack S){
    if(S.base == S.top) return true;
    else return false;
}

//返回S的元素个数，即为栈的长度
int StackLength(SqStack S){
    return S.top - S.base;
}

//构造一个空栈S
Status InitStack(SqStack &S){
    //构造一个空表
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

//若栈不空，用e返回S的栈顶元素，并返回OK；否则返回ERROR
Status GetTop(SqStack S,SElemType &e){
    if(S.base == S.top) return ERROR;
    e = * (S.top - 1);
    return OK;
}

//插入e为新的栈顶元素
Status Push(SqStack &S,SElemType &e){
    if(S.top - S.base >= S.stacksize){
        S.base = (SElemType *)realloc(S.base,(S.stacksize + STACK_INCREMENT) * sizeof(SElemType));
        if(!S.base) exit(OVERFLOW);
        S.top = S.base + S.stacksize; //因为S.base的内存是重新分配的，所以也要重新找S.top的位置。
        S.stacksize += STACK_INCREMENT;
    }
    *S.top++ = e;
    return OK;
}

//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR；
Status Pop(SqStack &S,SElemType &e){
    if(S.top == S.base) return ERROR;
    e = *--S.top;
    return OK;
}

//从栈顶到栈底依次输出S中的各个元素数据
void StackTraverse(SqStack &S){
    SqStack e;
    e = S;
    while(e.top > e.base){
        cout<< *e.base++<<" ";
    }
}
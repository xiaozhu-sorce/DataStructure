#define STACK_INIT_SIZE 100 // 存储空间初始分配量 
#define STACK_INCREMENT 10 // 存储空间分配增量 

typedef int SElemType;

// 栈的顺序存储结构
struct SqStack
{
    SElemType *base; // 在栈构造之前和销毁之后，base的值为NULL 
    SElemType *top; // 栈顶指针
    int stacksize; // 当前已分配的存储空间，以元素为单位
}; 
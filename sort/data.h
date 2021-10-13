#define MAX_SIZE 20

typedef int KeyType;

struct RedType
{
    //关键字
    KeyType key;
    InfoType otherInfo;
};

//SqList的 r[0]不放元素！！！！作为辅助位存在
struct SqList
{
    RedType r[MAX_SIZE+1];
    int length;
};


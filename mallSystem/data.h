typedef char SString[20];

struct HString
{
    char *ch;
    int length;
};

struct Data
{
    SString ID;
    SString name;
    SString stock;
    double purchasingPrice;
    double sellingPrice;
};

struct Node
{
    Data *data;
    Node *next;
};

typedef Data *Goods;
typedef Node *LinkList,*cart;//（购物车）
typedef char SString[20];

struct HString
{
    char *ch;
    int length;
};

struct Data
{
    int ID;
    SString name;
    int stock;
    float purchasingPrice;
    float sellingPrice;
};

struct Node
{
    Data *data;
    Node *next;
};

typedef Data *Goods;
typedef Node *LinkList,*cart;//（购物车）
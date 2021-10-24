struct HString
{
    char *ch;
    int length;
};

struct Data
{
    int number;
    HString name;
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
typedef Node *LinkList;
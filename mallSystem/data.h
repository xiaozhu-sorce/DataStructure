#define MAX_STR_LEN 40

typedef char NString[MAX_STR_LEN + 1];

struct Data
{
    int number;
    NString name;
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
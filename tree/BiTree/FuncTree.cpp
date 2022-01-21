#include "base.h"
#include "../../c1.h"

//初始化
void InitBiTree(BiTree &T)
{
    T = NULL;
}

void DestroyBiTree(BiTree &T)
{
    if (T)
    {
        if (T->left)
            DestroyBiTree(T->left);
        if (T->right)
            DestroyBiTree(T->right);
        free(T);
        T = NULL;
    }
}

void CreateBiTree(BiTree &T)
{
    char ch;
    cin >> ch;
    if (ch == '#')
        T = NULL;
    else
    {
        T = (BiNode *)malloc(sizeof(BiTree));
        T->val = ch;
        CreateBiTree(T->left);
        CreateBiTree(T->right);
    }
}
#include <iostream>
using namespace std;

typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} BiNode, *BiTree;

int hL = 0;
int hR = 0;
int node = 0;

void InitTree(BiTree &T)
{
    T = NULL;
}

void CreatebiTree(BiTree &T)
{
    char ch;
    cin >> ch;
    if (ch == '#')
        T = NULL;
    else
    {
        T = (BiNode *)malloc(sizeof(BiTree));
        T->val = ch;
        CreatebiTree(T->left);
        CreatebiTree(T->right);
    }
}

int BiTreeDepth(BiTree &T)
{
    if (!T)
        return 0;
    else
    {
        hL = BiTreeDepth(T->left);
        hR = BiTreeDepth(T->right);
        if (hL > hR)
            return hL + 1;
        else
            return hR + 1;
    }
}

int BiTreeSum(BiTree &T)
{
    if (!T)
        return 0;
    int left = BiTreeSum(T->left);
    int right = BiTreeSum(T->right);
    return 1 + left + right;
}

int main()
{
    BiTree tree;
    InitTree(tree);
    CreatebiTree(tree);

    cout << "二叉树的高度为：" << BiTreeDepth(tree) << endl;
    cout << "二叉树中的节点总数为：" << BiTreeSum(tree) << endl;
    return 0;
}
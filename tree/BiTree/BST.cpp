#include <iostream>
using namespace std;

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

typedef struct List
{
    Node *header;
} List;

///双向循环链表的查找
Node *listFind(List dl, int val)
{
    if (dl.header->next == dl.header)
        return NULL;

    Node *cur = dl.header->next;
    while (cur != dl.header)
    {
        if (cur->data == val)
            return cur;
            
        cur = cur->next;
    }
    return NULL;
}


struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// BST搜索
struct TreeNode *searchBST(struct TreeNode *root, int val)
{
    if (root == NULL)
        return NULL;
    else
    {
        if (root->val > val)
            return searchBST(root->left, val);
        else if (root->val < val)
            return searchBST(root->right, val);
        else
            return root;
    }
}

// BST搜索迭代
struct TreeNode *searchBST1(struct TreeNode *root, int val)
{
    while (root != NULL && val != root->val)
        root = val < root->val ? root->left : root->right;
    return root;
}

// BST搜索简单
struct TreeNode *searchBST2(struct TreeNode *root, int val)
{
    while (root != NULL)
    {
        if (root->val > val)
            root = root->left;
        else if (root->val < val)
            root = root->right;
        else
            return root;
    }
    return NULL;
}

// BST非递归插入
struct TreeNode *createTreeNode(int val)
{
    struct TreeNode *ret = (TreeNode *)malloc(sizeof(TreeNode));
    ret->val = val;
    ret->left = ret->right = NULL;
    return ret;
}

struct TreeNode *insertIntoBST(struct TreeNode *root, int val)
{
    if (root == NULL)
    {
        root = createTreeNode(val);
        return root;
    }
    struct TreeNode *pos = root;
    while (pos != NULL)
    {
        if (val < pos->val)
        {
            if (pos->left == NULL)
            {
                pos->left = createTreeNode(val);
                break;
            }
            else
                pos = pos->left;
        }
        else
        {
            if (pos->right == NULL)
            {
                pos->right = createTreeNode(val);
                break;
            }
            else
                pos = pos->right;
        }
    }
    return root;
}

int main()
{
    return 0;
}

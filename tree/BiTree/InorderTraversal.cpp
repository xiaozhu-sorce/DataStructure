#include "../../c1.h"

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void traverse(struct TreeNode *root, int *res, int *resSize)
{
    if (!root)
        return;
    traverse(root->left, res, resSize);
    res[(*resSize)++] = root->val;
    traverse(root->right, res, resSize);
}

int *inorderTraversal(struct TreeNode *root, int *returnSize)
{
    int *res = (int *)malloc(sizeof(int) * 501);
    *returnSize = 0;
    traverse(root, res, returnSize);
    return res;
}

int main()
{
    return 0;
}
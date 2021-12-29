#include "data.h"
#include "sequenceBo.cpp"
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int a[10000];
bool flag[10000];
int T, n;
int c;

//背包问题，其中w是物品的价值，T是背包的重量，n是物品的数量
void knapsack(int w[], int T, int n)
{
    SqStack s;
    SElemType k;
    int j = 1;
    InitStack(s);
    do
    {
        while (T > 0 && k < n)
        {
            if (T - w[k] >= 0)
            {
                Push(s, k);
                T -= w[k];
            }
            k++;
        }

        if (T == 0)
        {
            cout << "第" << j++ << "次";
            StackTraverse(s);
            cout << endl;
        }

        Pop(s, k);
        T += w[k];
        k++;
    } while (!StackEmpty(s) || k < n);
}

void output() //输出函数
{
    c++;
    for (int i = 0; i < n; i++)
    {
        if (flag[i])
            cout << a[i] << " "; //物体在包内，输出
    }
    cout << endl;
    printf("\n");
}

//V为当前的背包体积，index为第几件物品。
void dfs(int V, int index)
{
    if (V == 0)
    {
        output(); //背包装满输出
        return;
    }
    if (V < 0 || index >= n) //base case
    {
        return; //不合条件返回
    }

    dfs(V, index + 1); //递归

    if (V - a[index] >= 0)
    {
        flag[index] = true; //装进去为true
        dfs(V - a[index], index + 1);
        flag[index] = false; //取出来为false
    }
}

int main()
{
    // int w[]={1,8,4,3,5,2};

    cout << "请输入背包体积的大小：" << endl;
    cin >> T;
    cout << "请输入物体个数：" << endl;
    cin >> n;
    cout << "请输入物体的体积：" << endl;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    memset(flag, false, sizeof(flag)); //标记置为false
    
    dfs(T, 0);                         //背包问题

    knapsack(a, T, n);
    return 0;
}
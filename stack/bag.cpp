#include"data.h"
#include"sequenceBo.cpp"

//背包问题，其中w是物品的价值，T是背包的重量，n是物品的数量
void knapsack(int w[],int T,int n)
{
    SqStack s;
    SElemType k;
    int j = 1; 
    InitStack(s);
    do
    {
        while(T > 0 && k < n){
            if(T - w[k] >= 0 ){
                Push(s,k);T-=w[k];
            }
            k++;
        }

        if(T == 0){
            cout<<"第"<<j++<<"次";
            StackTraverse(s);
            cout<<endl;
        }

        Pop(s,k);T+=w[k];
        k++;
    } while (!StackEmpty(s) || k<n);
    
}

int main(){
    int w[]={1,8,4,3,5,2};
    knapsack(w,10,6);
    return 0;
}
#include<iostream>
using namespace std;

void swap(int *a,int i,int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

//递归调整堆
void heapify(int a[],int len, int n){
    //base case
    if(n >= len) 
        return ;

    int c1 = 2*n + 1;
    int c2 = 2*n + 2;
    int max = n;

    if(c1 < len && a[c1] > a[max])
        max = c1;

    if(c2 < len && a[c2] > a[max])
        max = c2;

    if(max != n){
        swap(a,n,max);
        heapify(a,len,max);
    }
}

void delElem(int *a,int index,int len){
    swap(a,index-1,len-1);

    for(int i = (index-1-1)/2; i>=0; i--)
        heapify(a,len,i);

    for(int i = 0; i < len-1;i++)
        cout<<a[i]<<",";
}

int main(){
    int a[] = {50,47,48,27,46,19,38,26,5,2,44,4,15,36,37};
    delElem(a,8,15);
    return 0;
}
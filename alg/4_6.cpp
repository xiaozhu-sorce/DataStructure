#include<iostream>
using namespace std;

//将从s到e的数组对称调换
void leftConverse(char *a,int s,int e){
    for(int i = 0;i < (e-s+1)/2;i++){
        char temp = a[s+i];
        a[s+i] = a[e-i];
        a[e-i] = temp;
    }
}

//循环向左移动k个元素，a[]为数组，k为需要左移的个数，len为数组的长度
void cycleThroughKElements(char *a,int k,int len){
    leftConverse(a,0,k-1);
    leftConverse(a,k,len-1);
    leftConverse(a,0,len-1);

    for(int i = 0;i < len;i++)
        cout<<a[i]<<" ";
    cout<< endl;
}

int main(){
    char a[7] = {'a','b','c','d','e','f','g'};
    cycleThroughKElements(a,3,7);
    return 0;
}
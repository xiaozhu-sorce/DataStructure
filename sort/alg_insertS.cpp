#include"../c1.h"
typedef int InfoType;
#include"data.h"
#include"insertSort.cpp"

void print(SqList &L)
{
    int i;
    for ( i = 1; i <= L.length; i++)
    {
        printf("(%d,%d)",L.r[i].key,L.r[i].otherInfo);
    }
    printf("\n");
}

#define N 8

int main()
{
    RedType d[N] = {{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
    SqList l1,l2,l3;
    int i;
    for ( i = 0; i < N; i++)
    {
        l1.r[i+1] = d[i];
    }
    l1.length = N;
    l2 = l3 = l1;
    cout<<"排序前："<<endl;
    print(l1);
    cout<<"1.排序后："<<endl;
    InserSort(l1);
    print(l1);
    cout<<"2.排序后："<<endl;
    BInsertSort(l2);
    print(l2);
    cout<<"3.排序后："<<endl;
    P2_InsertSort(l3);
    print(l3);
    return 0;
}
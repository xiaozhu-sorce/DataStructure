//普通的选择排序
void InserSort(SqList &L)
{
    int i,j;
    for(int i = 2;i <= L.length;i++)
    {
        if (L.r[i].key < L.r[i-1].key)
        {
           L.r[0] = L.r[i];
           for ( j = i-1; L.r[0].key < L.r[j].key ; --j)
           {
               L.r[j+1] = L.r[j];
           }
           L.r[j+1] = L.r[0];
        }
    }
}

//二分法
void BInsertSort(SqList &L)
{
    int i,j,m,low,high;

    for ( i = 2; i <= L.length; i++)
    {
        L.r[0] = L.r[i];
        low = 1;
        high = i-1;

        //二分查找找到需要插入的位置
        while (low <= high)
        {
            m = (low + high)/2;
            if(L.r[0].key < L.r[m].key)
                high = m-1;
            else
                low = m+1;
        }

        for (j = i-1; j >= high+1 ; j--)
        {
            L.r[j+1] = L.r[j];
        }

        L.r[high+1] = L.r[0];
    }
}

//2路插入排序
void P2_InsertSort(SqList &L)
{
    int i,j,first,final;
    RedType *d;
    d = (RedType *)malloc(L.length*sizeof(RedType));
    d[0] = L.r[1];
    //first，final在此算法中指向的一直都是最小的元素以及最大的元素。
    first = final = 0;
    for ( i = 2; i <= L.length ; ++i)
    {
        if(L.r[i].key < d[first].key)
        {
            first = (first-1 + L.length) % L.length;
            d[first] = L.r[i];
        }else if(L.r[i].key > d[final].key)
        {
            final++;
            d[final] = L.r[i];
        }
        else
        {
            j=final++;
            while (L.r[i].key < d[j].key)
            {
                d[(j+1)%L.length] = d[j];
                j = (j-1+L.length)%L.length; //因为此处所以j只会为1不会为0！！
            }
            d[j+1] = L.r[i];
        }
    }

    for ( i = 1; i <= L.length; i++)
    {
        L.r[i] = d[(i+first-1) % L.length];
    }
}


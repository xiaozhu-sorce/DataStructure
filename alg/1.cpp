#include <iostream>
#include <set>
using namespace std;

int main(){
    set<int> s;
    set<int>::iterator iter;
    int n;
    cout<<"请输入数组的元素的个数"<<endl;
    cin>>n;
    int a[n];
    cout<<"请输入元素的值"<<endl;
    for(int i = 0;i < n;i++){
        cin>>a[i];
        s.insert(a[i]);
    }
    for(iter = s.begin() ; iter != s.end() ; ++iter)
    {
        cout<<*iter<<" ";
    }
    return 0;
}
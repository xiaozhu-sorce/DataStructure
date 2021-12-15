#include <iostream>
using namespace std;

template <class T>
class ListNode{
    public:
        //ListNode *pre;
        ListNode<T> *next;
        T data;
};

template <class T>
class Queue{
    private:
        ListNode<T> *head;
        ListNode<T> *rear;
        int size;
    public:
        Queue();
        bool isEmpty();
        void offer(T t);
        T poll();
        T peek();
        T getNode(int i);
        int Size();
};

template<class T>
T Queue<T>::getNode(int i){
    ListNode<T> *p = this->head;
    if(i>size){
        printf("所取节点溢出！！\n");
        exit(-1);
    }
    for(int j = 0 ; j < i; j++){
        p = p->next;
    }
    return p->data;

}

template <class T>
Queue<T>::Queue(){
    ListNode<T> *p = new ListNode<T>;
//    p->pre = NULL;
    p->next = NULL;
    head = p;
    rear = head;
    size = 0;
}

template <class T>
void Queue<T>::offer(T t){
    ListNode<T> *p = new ListNode<T>;
    p->data = t;
    p->next = NULL;
    rear->next = p;
    rear = rear->next;
    size++;
}

template <class T>
T Queue<T>::poll(){
    if(head == rear){
        throw "都空了还想抛出？！";
    }
    ListNode<T> *p = head;
    head = head->next;
    T ans = head->data;
    delete p;
    size--;
    return ans;
}

template<class T>
T Queue<T>::peek(){
    return this->head->next->data;
} 

template <class T>
bool Queue<T>::isEmpty(){
    return head == rear;
}

template <class T>
int Queue<T>::Size(){
    return size;
}

/*
int main(){
    Queue<int> q;
    for(int i = 0 ; i < 10; i++){
        q.offer(i);
    }
    for(int i = 0; i < q.Size();i++){
        int c = q.getNode(i + 1);
        printf("%d\n",c);
    }
    return 0;
}
*/
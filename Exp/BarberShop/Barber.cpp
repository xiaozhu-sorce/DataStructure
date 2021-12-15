#include "Person.cpp"
#include "Queue.cpp"

class Barber{
    private:
        Queue<Custom> *simple_queue;
        Queue<Custom> *vip_queue;
        int level;
        int price;
    public:
        Barber(Queue<Custom> *simple = NULL,Queue<Custom> *vip = NULL,int price = 30,int level = 1);
        int getVipTime();
        int getSimpleTime();
        void setLevel(int n);
        void setPrice(int price);
        int getLevel();
        int getPrice();   
        int getSimpleSize();
        int getVipSize();
        void show(); 
        Queue<Custom>* getVipQueue();
        Queue<Custom>* getSimpleQueue();
};

Barber::Barber(Queue<Custom> *simple,Queue<Custom> *vip ,int price ,int level ){
    this->simple_queue = simple;
    this->vip_queue = vip;
    this->price = price;
    this->level = level;
}

int Barber:: getVipTime(){
    int sum = 0;
    int n = vip_queue->Size();
    for(int i = 1 ; i<= n;i++){
        Custom c = vip_queue->getNode(i);
        sum += c.getTime();
    }
    return sum;
}

int Barber:: getSimpleTime(){
    int sum = 0;
    int n = simple_queue->Size();
    for(int i = 1 ; i<= n;i++){
        Custom c = simple_queue->getNode(i);
        sum += c.getTime();
    }
    return sum;
}

void  Barber::setLevel(int n){
    this->level = n;
} 
void Barber::setPrice(int price){
    this->price = price;
}
int Barber::getLevel(){
    return this->level;
}
int Barber::getPrice(){
    return this->price;
}

int Barber::getSimpleSize(){
    return this->simple_queue->Size();
}
int Barber::getVipSize(){
    return this->vip_queue->Size();
}

Queue<Custom>* Barber::getVipQueue(){
    return this->vip_queue;
}
Queue<Custom>* Barber::getSimpleQueue(){
    return this->simple_queue;
}


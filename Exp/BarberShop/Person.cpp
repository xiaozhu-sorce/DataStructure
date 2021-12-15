#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;
class Barber;
class Custom{
    private:
        string zhanghao;
        string password; 
        bool isVip;
        int time;
    public:
        Custom();
        Custom(int time,bool isVip);
        string getZhanghao();
        int getTime();
        bool getIsVip();   
        void show();
};

void Custom::show(){
    cout<< time << "  " <<isVip << endl;
}

Custom::Custom(){
    this->zhanghao = "";
    this->password = "";
    this->isVip = false;
    this->time = 30;
}

Custom::Custom(int time, bool isVip){
    this->zhanghao = "";
    this->password = "";
    this->isVip = isVip;
    this->time = time;
}

bool Custom::getIsVip(){
    return this->isVip;
}

int Custom::getTime(){
    return this->time;
}

/*
int main(){
    Queue<Custom> q;
    for(int i = 0 ; i < 10;i++){
        bool key = false;
        if(i % 2 == 0){
            key = true;
        }
        Custom c(i,key);
        q.offer(c);
    }
    for(int i = 0 ; i < q.Size();i++){
        Custom d = q.getNode(i + 1);
        d.show();
    }
    return 0;
}
*/
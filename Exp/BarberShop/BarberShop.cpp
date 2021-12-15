#include "Barber.cpp"
#include "random"
#include "ctime"
using namespace std;

bool isMatch(string name,string password,string (*user)[10],int n,bool *vip);
void initRandom(Barber** b);
void vip_do(Barber *b);
void simple_do(Barber* b);
void show(Barber** b,int n);
void choose(Barber** b,int n,bool vip);
void chooseBarber(Barber** b,int n,bool vip);
void waiting(Barber *b,bool vip);

int main(){
    fstream file;
    file.open("b_store.txt",ios::in);
    string user[20][10];
    int n = 0;
    bool key = false;
    for(int i = 0 ; i < 20 ; i++){
        n++;
        for(int j = 0 ; j < 3 ; j++){
            file >> user[i][j];
            if(user[i][j]== ""){
                key = true;
                break;
            }
        }
        if(key){
            break;
        }
    }
    file.close();
    printf("欢迎光临\n");
    Init:
    printf("请输入您的账号：\n");
    string name;
    cin>>name;
    printf("请输入您的密码:\n");
    string password;
    cin>>password;
    bool vip = false;
    if(isMatch(name,password,user,8,&vip)){
        Barber** b = new Barber*[8];
        initRandom(b);
        chooseBarber(b,8,vip);
        int num;
        printf("您选择的理发师是:");
        do{
            scanf("%d",&num);
            if(num < 0 || num > 7){
                printf("输入错误，请再次输入\n");
            }
        }while(num< 0 || num >7);
        waiting(b[num],vip);
    }else{
        int m;
        printf("1.退出\n2.再次登录\n");
        scanf("%d",&m);
        switch(m){
        case 1 :
            printf("再见！");
            return 0;
            break;
        case 2 :
            goto Init;
            break;
        }
        
    }
    return 0;
}

bool isMatch(string name, string password, string (*user)[10],int n,bool *vip){
    int t = 0;
    *vip = false;
    for(t = 0 ; t < n;t++){
        if(user[t][0] == name){
            break;
        }
    }
    if(t == n){
        printf("该账号没有录入！\n");
        return false;
    }else{
        if(user[t][1] != password){
            printf("密码错误!\n");
            return false;
        }else{
            printf("登录成功!");
            if(user[t][2] == "vip"){
                *vip = true;
                printf("你的身份是vip\n");
            }else{
                printf("你的身份是普通顾客\n");
            }
            return true;
        }
    }
}

void chooseBarber(Barber **b,int n,bool vip){
    int x = 1;
    printf("1.查看理发师清单\n");
    printf("2.选择理发师\n");
    printf("3.下一步\n");
    do{
        printf("请输入行动编号：\n");
        scanf("%d",&x);
        if(x == 1){
            show(b,n);
        }else if(x == 2){
            choose(b,n,vip);
        }else if( x == 3){
            return;
        }else{
            printf("输入错误，请再次输入\n");
            x = 1;
        }
    }while(x>0 && x< 4);
}

void choose(Barber **b,int n,bool vip){
    printf("请选择理发师：");
    int m = 0 ; 
    scanf("%d",&m);
    while(m > n || m < 0){
        printf("输入错误！请再次输入\n");
        scanf("%d",&m);
    }
    if(vip){
        vip_do(b[m]);
    }else{
        simple_do(b[m]);
    }
}

void show(Barber** b,int n){
    for(int i = 0; i < n ;i++){
        printf("%d号理发师是%d级\n",i,b[i]->getLevel());
    }
}

void simple_do(Barber* b){
    printf("1.查看队列\n");
    printf("2.查看等待时间\n");
    printf("3.查看理发师价格\n");
    printf("4.退出\n");
    int m = 0;
    printf("请选择你的行动:");
    scanf("%d",&m);
    while(m > 4 || m < 0){
        printf("输入错误！请再次输入\n");
        scanf("%d",&m);
    }
    switch(m){
        case 1:{
            int  p = b->getSimpleSize() + b->getVipSize();
            printf("你前面还有%d个人\n",p);
            break;
        }
        case 2:{
            int t =  b->getVipTime() + b->getVipTime();
            printf("还需等待%d\n分钟",t);
            break;
        }
        case 3:{
            int l = b->getPrice();
            printf("ta的费用是%d元\n",l);
        }
        case 4:
        return;
        default:break;
    }
}

void vip_do(Barber *b){
    printf("尊贵的vip客户，已经将您的优先级提高，使用vip特殊通道！\n");
    printf("1.查看队列\n");
    printf("2.查看等待时间\n");
    printf("3.查看价格\n");
    printf("4.退出\n"); 

    int m = 0;
    printf("请选择你的行动:");
    scanf("%d",&m);
    while(m > 4 || m < 0){
        printf("输入错误！请再次输入\n");
        scanf("%d",&m);
    }
    switch(m){
        case 1:{
            int  p = b->getVipSize();
            printf("你前面还有%d个人\n",p);
            break;
        }
        case 2:{
            int t =  b->getVipTime();
            printf("还需等待%d分钟\n",t);
            break;
        }
        case 3:{
            int l = b->getPrice() * 9 /10;
            printf("ta的费用是%d,已享受九折优惠\n",l);
            break;
        }
        case 4:
        return;
    }
}

void initRandom(Barber** b){
    srand(time(NULL));
    for(int i = 0 ; i < 8 ;i++){
        Queue<Custom> simple,vip;
        int t1 = rand() % (i + 1);
        int t2 = rand() %2;
        for(int i = 0; i < t1;i++){
            int t = rand()%21 + 20;
            Custom f(t,false);
            simple.offer(f);
        }
        for(int i = 0; i < t2;i++){
            int t = rand()%21 + 20;
            Custom f(t,true);
            simple.offer(f);
        }
        int level = 0;
        if(i < 2){
            level = 3;
        }else if( i < 5){
            level = 2;
        }else{
            level = 1;
        }
        int price = level * level * 30;
        b[i] = new Barber(&simple,&vip,price,level);
    }
}

void waiting(Barber *b,bool vip){
    printf("经过漫长的%d分钟",b->getSimpleTime());
    if(vip){
        printf("现在终于轮到你了\n");
        srand(time(NULL));
        int t = rand()%21 + 20;
        printf("经过了%d分钟后，你完成了理发\n",t);
        printf("花费了%d元",b->getPrice()* 9/10);
        return;
    }
    printf("该死的vip终于走了，又经过漫长的%d分钟",b->getSimpleTime()); 
    printf("现在终于轮到你了\n");
    srand(time(NULL));
    int k = rand()%21 + 20;
    printf("经过了%d分钟后，你完成了理发\n",k);
    printf("花费了%d元",b->getPrice());
}
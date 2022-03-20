#include<iostream>
#include<time.h>
using namespace std;

int main() {
	int n = 2500;
	
	srand(time(NULL));	//把这个放到循环外面
	
	while (n) {
		std::cout << rand() % 5 << ",";
		n--;
	}
    cout<<endl;
}
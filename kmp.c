#include"stdio.h"
#include"string.h"

//abcdeacbde
//acbde
int BF(char S[],char P[]){
    int i,k,m;
	int j = strlen(P);
	for( i = 0 ; i < strlen(S) - j ; i++ ){
		k = i ; 
		m = 0 ;
		while(k <= i + j){		
			if( S[k++] != P[m++] )
				break;
			if( k == i+j ){
				return i + 1;
			}
		}
	}
	printf("error!");
	return 0;
}

//BP
int main(){
    char source[] = "abcabcde";
    char pattern[] = "abca";
    
}
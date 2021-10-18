#include"..\c1.h"
#include"base.h"
#include"sequenceStructure.cpp"

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

int Index(SString S,SString T,int pos)
{
    int i,j;
    if(1<=pos && pos<=S[0])
    {
        i=pos;
        j=1;
        while (i<=S[0] && j<=T[0])
            if(S[i] == T[j])
            {
                ++j;
                ++i;
            }
            else //指针后退重新开始匹配
            {
                i=i-j+2;
                j=1;
            }
        if(j>T[0])
            return i-T[0];
        else   
            return 0;
    }
    else
        return 0;
}

//BP
int main(){
    char source[] = "abcabcde";
    char pattern[] = "abca";
    
}
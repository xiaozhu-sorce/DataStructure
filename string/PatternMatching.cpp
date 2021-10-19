#include"../c1.h"
#include"base.h"
#include"sequenceStructure.cpp"

//暴力解法
int BF(SString S,SString P,int pos){
    int i,j,k,m;
    //j为除了第一位后字符串的长度
	j = P[0];
    //i要循环的次数为两个字符串长度的差加一
    if(1<=pos && pos<=S[0])
    {
        for( i = pos ; i <= S[0] - P[0]+1; i++ ){
            k = i ; 
            m = 1 ;
            while(k <= i + j){		
                if( S[k++] != P[m++] )
                    break;
                if( k == i+j )
                    return i;
            }
        }
    }else{
        return 0;
    }
	return 0;
}


//求解next[]数组。
void get_next(SString S,int next[]){
    int i=1,j=0;
    next[1] = 0;
    while(i < S[0]){
        if(j==0||S[i]==S[j]){
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j=next[j];
    }
}

//暴力枚举
void get_next_bf(SString S,int next[]){
    int i,len,j;
    for( i = 1 ; S[i] != '\0' ; i++ ){//计算[0,i]的最大真前后缀的长度 
		for( len = i-1 ; len >= 1 ; len-- ){
			for( j = 1 ; j < len ; j++ ){ //比较[0,len-1]和[i-len+1,i] 
				if( S[j] != S[i-len+j] )  break;
			}
			if( j == len ){
				next[i] = len;
				break;
			} 
		}	
	}
}

//kmp算法
int KMP(SString S,SString P,int pos,int next[]){
    get_next_bf(S,next);
    int i = pos,j=1;
    if(1<=pos && pos<=S[0])
    {
        while(i <= S[0] && j <= P[0]){
            if( j == 0 || S[i] == P[j]){
                i++;
                j++;
            }else
                j = next[j];
        }
        if(j > P[0])
            return i - P[0];
        else
            return 0;
    }else{
            return 0;
    }
}

int main(){
    int i,*p;
    SString source,pattern;
    StrAssign(source,"ababcac");
    StrAssign(pattern,"abcac");
    int sum1,sum2,sum3;
    p = (int *)malloc((StrLength(pattern)+1)*sizeof(int));
    sum1 = Index(source,pattern,1);
    cout << sum1 <<endl;
    sum2 = BF(source,pattern,1);
    cout << sum2 <<endl;
    sum3 = KMP(source,pattern,1,p);
    cout << sum3 <<endl;
    return 0;
    
}
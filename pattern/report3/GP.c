#include <stdio.h>
#include <string.h>

void usage(void);
int g(int,int);
int d(char,char);

int main(int ac,char *av[]){

    //引数チェッカー
    if( ac !=3 ){
        usage();
        return 1;
    }

    // 各引数(文字列)をInpt1,Inp2に設定
    char* Inp1 = av[1];
    char* Inp2 = av[2];

   //各文字列の文字数をI,Jに設定
    int I = strlen(Inp1);
    int J = strlen(Inp2);

    printf("%d\n",I);
    return 0;
}

// 使い方を出力

void usage(void){
    puts("Usage> ./GP abcde abfeg");
}

int g(int i,int j){

    return 0;
}

//関数d
//対象とする2文字が等しければ0
//そうでなければ1を返す.

int d(char i,char j){
    
    if (i == j){
        return 0;
    }else{
        return 1;
    }
}

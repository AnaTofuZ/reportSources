/*
 *
 * 認知工学 DPマッチングを用いて異なる文字数を決定するプログラム
 * Author <c> 清水隆博 @AnaTofuZ
 *      2017/04/26
 *
 */


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

    printf("%d\n",d(Inp1[0],Inp2[0]));

    printf("%d\n",I);


    for (int j = 0; j < J; j++) {

        for (int i = 0; i < I; i++) {
            
        }
    }
    return 0;
}

// usage関数
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

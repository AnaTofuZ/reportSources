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
int d(char,char);

int main(int ac,char *av[]){

    //引数チェッカー
    if( ac !=3 ){
        usage();
        return 1;
    }

    // 各引数(文字列)をI_A,J_Aに設定
    char* I_A = av[1];
    char* J_A = av[2];


   //各文字列の文字数をI,Jに設定
    int I = strlen(I_A);
    int J = strlen(J_A);



    // 2次元配列D[I][J]を作成

    int D[I][J];

    // 2次元配列D[I][J]に関数dの返り値を設定

    for (int i = 0; i < I; i++) {
        for (int j = 0; j < J; j++) {
                D[i][j]=d(I_A[i],J_A[j]);
        }
    }


    // 確認用としてDの結果を票形式で出力

    puts("d(i,j)");

    for (int i = --I; 0 <= i ; i--) {
        for (int j =0; j < J ; j++) {
                printf("%3d",D[i][j]);
        }
        printf("\n");
    }


    // 2次元配列g[I][J]を作成

    int g[I][J];

    // 横一列のみ初期設定

    for (int j = 0; j < J; j++) {
        
        if(j==0){
            g[0][0] = 2 * D[0][0];
        }else{
            int i=--j;
            g[0][j] = g[0][i] + D[0][j];
        }
    }

    for (int i = 1; i < I; i++) {
        for (int j = 0; j < J; j++) {
            
        }
    }

    return 0;
}

// usage関数
// 使い方を出力

void usage(void){
    puts("Usage> ./GP abcde abfeg");
}


//関数d
//対象とする2文字が等しければ0
//そうでなければ1を返す.

int d(char i,char j){

    if (i == j){
        return (0);
    }else{
        return (1);
    }

}

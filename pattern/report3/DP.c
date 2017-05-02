/*
 *
 * 認知工学 DPマッチングを用いて異なる文字数を決定するプログラム
 * Author <c> 清水隆博 @AnaTofuZ
 *      2017/04/26
 *
 */


#include <stdio.h>
#include <string.h>

#define ARRAY_MAX 255

void usage(void);
int d(char,char);
void showArray(int,int,int ar[ARRAY_MAX][ARRAY_MAX],char*,char*);

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

    showArray(I,J,D,I_A,J_A);


    // 2次元配列g[I][J]を作成

    int g[I][J];

    // 下一行のみ初期設定

    for (int j = 0; j < J; j++) {
        
    // 初回は定義より 2*D[0][0]をいれる．
        if(j==0){
            g[0][0] =2*D[0][0];
        }else{
        // それ以外は左隣のものの距離を足す
            g[0][j] = (g[0][j-1] + D[0][j]);
        }
    }

    // 上の行を処理していく

    for (int i = 1; i < I; i++) {
        for (int j = 0; j < J; j++) {

        // 1番左の列で無いかどうかの判断
            if (j !=0) {

                //現段階の最小値は左と足したもの
               int  min = g[i-1][j]+D[i][j];
                // 左斜め下が最小値の場合,そちらを採用
                if(min > g[i-1][j-1]+ 2*D[i][j]){
                    min = g[i-1][j-1]+ 2*D[i][j];

                // 下が最小値の場合,そちらを採用
                    if (min > g[i][j-1] + D[i][j]){
                        g[i][j] = g[i][j-1] + D[i][j];
                        continue;
                    }
                   g[i][j]=min;
                   continue;
                }
                
                g[i][j]=min;
            } else {
                // 1番左の列の場合1つ下のものとの距離を計算
                 g[i][0] = g[i-1][0]+D[i][0]; 
            }
            
        }
    }

    puts("g(i,j)");
    showArray(I,J,g,I_A,J_A);

    puts("-----");
    printf("This words diff :%3d\n",g[I-1][J-1]);

    return 0;
}

// usage関数
// 使い方を出力

void usage(void){
    puts("Usage> ./DP abcde abfeg");
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

// showArray関数
// 多次元配列を表の形式で出力

void showArray(int I,int J,int ar[I][J],char* I_A,char* J_A){

    for (int i = (I-1); 0 <= i ; i--) {
    
        printf("%c|",I_A[i]);

        for (int j =0; j < J ; j++) {
                printf("%3d",ar[i][j]);
        }
        printf("\n");
    }

    printf(" ");

    for (int j = 0; j < J; j++) {
        printf("---");
    }

    puts("");
    printf("  ");

    for (int j = 0; j < J; j++) {
        printf("%3c",J_A[j]);
    }

    printf("\n");

}

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

    // for文でIをデクリメントしてしまったので戻す．
    I++;

    // 2次元配列g[I][J]を作成

    int g[I][J];

    // 下一行のみ初期設定

    for (int j = 0; j < J; j++) {
        
    // 初回は定義より 2*D[0][0]をいれる．
        if(j==0){
            g[0][0] =2*D[0][0];
        }else{
            int j_decry=j;
            j_decry--;
        // それ以外は左隣のものの距離を足す
            g[0][j] = (g[0][j_decry] + D[0][j]);
        }
    }

    // 上の行を処理していく

    for (int i = 1; i < I; i++) {
        for (int j = 0; j < J; j++) {

        // 1番左の列で無いかどうかの判断

            if (j !=0) {
                
                int min,i_decry,j_decry;

                i_decry = i;
                j_decry = j;

                i_decry--;
                j_decry--;

                //現段階の最小値は左と足したもの

                min = g[i_decry][j]+D[i][j];

                // 左斜め下が最小値の場合,そちらを採用

                if(min > g[i_decry][j_decry]+ 2*D[i][j]){
                    min = g[i_decry][j_decry]+ 2*D[i][j];

                // 下が最小値の場合,そちらを採用

                    if (min > g[i][j_decry] + D[i][j]){
                        g[i][j] = g[i][j_decry] + D[i][j];
                        continue;
                    }
                   g[i][j]=min;
                   continue;
                }
                
                g[i][j]=min;

            } else {
                int  i_decry = i;
                // 1番左の列の場合1つ下のものとの距離を計算
                i_decry--;
                 g[i][0] = g[i_decry][0]+D[i][0]; 
            }
            
        }
    }

    puts("g(i,j)");

    for (int i = --I; 0 <= i ; i--) {
        for (int j =0; j < J ; j++) {
                printf("%3d",g[i][j]);
        }
        printf("\n");
    }

    puts("-----");
    printf("This words diff :%3d\n",g[I][--J]);

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


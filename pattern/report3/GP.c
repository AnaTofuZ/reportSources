#include <stdio.h>
#include <string.h>

void usage(void);

int main(int ac,char *av[]){

    if( ac !=3 ){
        usage();
        return 1;
    }

    char* Inp1 = av[1];
    char* Inp2 = av[2];
    int I = strlen(av[1]);

    printf("%d\n",I);
    return 0;
}

void usage(void){
    puts("Usage> ./GP abcde abfeg");
}

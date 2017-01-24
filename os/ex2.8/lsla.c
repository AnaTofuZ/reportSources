//
//  main.c
//  lsla
//
//  Created by Takahiro SHIMIZU on 11/15/16.
//  Copyright © 2016 ie-ryukyu. All rights reserved.
//

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define EROOR 1
#define FOUND 1
#define NOT_FOUNT 1

void list_dir(const char *base_path);
void puts_list(struct dirent *dp,int *sum);

int main(int argc, char * argv[]) {

    char *path = "./";

    struct dirent *dent;

    if (argc >1){
        path = argv[1];
    }

    list_dir(path);

    return 0;
}


void list_dir(const char *base_path){

    DIR *dir;
    struct dirent *dp;
    int blocksum = 0;

    dir = opendir(base_path);
    
    if(dir == NULL){
        perror(base_path);
        return;
     }

    while ((dp = readdir(dir)) !=NULL) {
         puts_list(dp,&blocksum);
    }

    printf("total %d\n",blocksum);

    closedir(dir);
}

void puts_list(struct dirent *dp,int *sum){

    struct stat sb;

    if(stat(dp->d_name,&sb) == 0){

    if ((sb.st_mode & S_IFMT) == S_IFDIR){
        printf("d");
    }

    *sum +=sb.st_blocks;

    }
}

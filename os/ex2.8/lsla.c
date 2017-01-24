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

static void list_dir(const char *base_path);

int main(int argc, char * argv[]) {

    char *path = "./";
    DIR *dirp;

    struct dirent *dent;

    if (argc >1){
        path = argv[1];
    }

    dirp = opendir(path);

    if (dirp == NULL) {
        perror(path);
        return (EROOR);
    }

    list_dir(path);

    return 0;
}


static void list_dir(const char *base_path){

    DIR *dir;
    struct dirent *dp;

    dir = opendir(base_path);
    
    if(dir == NULL){
        perror(base_path);
        return;
     }

    while ((dp = readdir(dir)) !=NULL) {
        printf("%s\n", dp->d_name);
    }

    closedir(dir);
}

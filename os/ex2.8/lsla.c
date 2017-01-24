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


static char *parse_cmd_args(int argc,char **argv);
static void list_dir(const char *base_path);

int main(int argc, char * argv[]) {

    char *path = "./";
    DIR *dir;

    struct dirent *dent;

    if (argc >1){
        path = argv[1];
    }

    dir = opendir(path);

    if (dir == NULL) {
        perror(path);
        return 1;
    }

    while ((dent = readdir(dir)) !=NULL) {
        printf("%s\n",dent->d_name);
    }

    closedir(dir);

    return 0;
}


static void list_dir(const char *base_path){

    DIR *dir;
    struct dirent *dent;

    dir = opendir(base_path);
    
    if(dir == NULL){
        perror(base_path);
        return;
     }

    while ((dent = readdir(dir)) !=NULL) {
        printf("%s\n", dent->d_name);
    }

    closedir(dir);
}

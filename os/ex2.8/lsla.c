//
//  main.c
//  Clsa
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

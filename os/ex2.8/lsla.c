//
//
//  lsla.c
//
//  Created by Takahiro SHIMIZU on 11/15/16.
//  Copyright © 2016 ie-ryukyu. All rights reserved.
//

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <string.h>
#define EROOR 1
#define FOUND 1
#define NOT_FOUNT 1

void list_dir(const char *base_path);
void puts_list(struct dirent *dp,int *sum);
void get_detail(mode_t mode,char *get_show);
char* get_username(uid_t uid);
char* get_groupname(gid_t gid);

int main(int argc, char * argv[]) {

    char *path = ".";

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

  /**
   * print ls elemtns and sum block size caluculation.
   */

    struct stat sb;

    if(stat(dp->d_name,&sb) == 0){

    char show[12];

    get_detail(sb.st_mode,show);
    printf("%s  ",show);
    printf("%2d\t",sb.st_nlink);
    printf("%s\t",get_username(sb.st_uid));
    printf("%s\t",get_groupname(sb.st_gid));

    *sum +=sb.st_blocks;

    }
}

void get_detail(mode_t mode,char *get_show){
/**
 * get file mode . the entry type,owner permissions,and group permissions.
 */

    switch (mode & S_IFMT) {
        case S_IFBLK:
             get_show[0] ='b';
             break;
        case S_IFCHR:
             get_show[0] = 'c';
             break;
        case S_IFDIR:
             get_show[0] ='d';
             break;
        case S_IFLNK:
             get_show[0]= 'l';
             break;
        case S_IFSOCK:
             get_show[0] ='s';
             break;
        case S_IFIFO:
             get_show[0]='p';
             break;
        case S_IFREG:
             get_show[0]='-';
             break;
        defalut:
             get_show[0]='?';
             break;
    }

    get_show[1]  = mode & S_IRUSR ? 'r':'-';
    get_show[2]  = mode & S_IWUSR ? 'w':'-';

    if (mode & S_ISUID) {
        get_show[3] = mode & S_IXUSR ? 's':'S';
    } else {
        get_show[3] = mode & S_IXUSR ? 'x':'-';
    }

    get_show[4]  = mode & S_IRGRP ? 'r':'-';
    get_show[5]  = mode & S_IWGRP ? 'w':'-';

    if (mode & S_ISGID) {
        get_show[6] = mode & S_IXGRP ? 's':'S';
    } else {
        get_show[6] = mode & S_IXGRP ? 'x':'-';
    }

    get_show[7]  = mode & S_IROTH ? 'r':'-';
    get_show[8]  = mode & S_IWOTH ? 'w':'-';

    if (mode & S_ISVTX) {
        get_show[9] = mode & S_IXOTH ? 't':'T';
    } else {
        get_show[9] = mode & S_IXOTH ? 'x':'-';
    }
    
    get_show[10] ='\0';


}


char* get_username(uid_t uid){
    char* username;
    struct passwd *passwd = getpwuid(uid);

    if (passwd != NULL) {
        return username=passwd->pw_name;      
    } else {
        sprintf(username,"%d",uid);
        return username;
    }
}

char* get_groupname(gid_t gid){
    char* groupname;
    struct group *group = getgrgid(gid);

    if(group !=NULL){
        return groupname = group->gr_name;
    } else {
        sprintf(groupname,"%d",gid); 
        return groupname;
    }
}

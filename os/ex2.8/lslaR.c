//
//
//  lslaR.c
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
#include <time.h>
#include <grp.h>
#include <stdlib.h>
#include <string.h>
#define EROOR 1
#define FOUND 1
#define NOT_FOUNT 1
#define PATH_MAX 4096

void list_dir(char *base_path);
void puts_list(struct dirent *dp);
void get_detail(mode_t mode,char *get_show);
char* pathlink(mode_t mode,char* name);
char* get_username(uid_t uid);
char* get_groupname(gid_t gid);
unsigned int sumTotal(DIR *dir,struct dirent *dp);

int main(int argc, char * argv[]) {


    char *path = argc >1 ? argv[1]:".";


    list_dir(path);

    return 0;
}


void list_dir(char *base_path){

/**
 * list_dir is use opendir and reaadir.
 * print is total block  .
 */

    DIR *dir;
    struct dirent *dp;

    dir = opendir(base_path);
    
    if(dir == NULL || chdir(base_path) != 0){
        perror(base_path);
        return ;
     }

    printf("total %d\n",sumTotal(dir,dp));

    while ((dp = readdir(dir)) !=NULL) {
         puts_list(dp);
    }


    closedir(dir);
}

void puts_list(struct dirent *dp){

  /**
   * print ls elemtns and sum block size caluculation.
   */

    struct stat sb;

    if(lstat(dp->d_name,&sb) == 0){

    char show[10+1];
    char times[13];

    get_detail(sb.st_mode,show);
    printf("%s  ",show);
    printf("%2d  ",sb.st_nlink);
    printf("%s  ",get_username(sb.st_uid));
    printf("%s  ",get_groupname(sb.st_gid));
    printf("%6lld  ",sb.st_size);
    strftime(times,sizeof(times),"%m %e %H:%M",localtime(&sb.st_ctime));
    printf("%s ",times);
    printf("%s",dp->d_name);

    char *showlink = pathlink(sb.st_mode,dp->d_name);
    showlink == NULL ? putchar('\n'):printf(" -> %s\n",showlink);


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

/*
 * get_* is using *id get to *name
 */

char* get_username(uid_t uid){

    struct passwd *passwd = getpwuid(uid);

    if (passwd != NULL) {
        return passwd->pw_name;
    } else {
        char* username;
        sprintf(username,"%d",uid);
        return username;
    }
}

char* get_groupname(gid_t gid){
    struct group *group = getgrgid(gid);

    if(group !=NULL){
        return group->gr_name;
    } else {
        char* groupname;
        sprintf(groupname,"%d",gid); 
        return groupname;
    }
}

/*
 * pathlink show symblolick link
 */

char* pathlink(mode_t mode,char* name){
    char* returnLink =NULL;

    if (S_ISLNK(mode)){
        char link[PATH_MAX +1];
        int link_len = readlink(name,link,PATH_MAX);

        if (link_len >0) {
            link[link_len]='\0';
            returnLink = link;
        }
    }
    return returnLink;
}

/*
 * sumTotal for get total block size
 */

unsigned int sumTotal(DIR *dir,struct dirent *dp){

    unsigned int sum =0;
    struct stat sb;

   while((dp = readdir(dir)) !=NULL){     
        if(lstat(dp->d_name,&sb) == 0){
            sum +=sb.st_blocks;
        }
    }
    rewinddir(dir);
    return sum;
}


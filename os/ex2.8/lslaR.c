//
//
//  lslaR.c
//
//  Created by Takahiro SHIMIZU on 01/26/17.
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
#define STACK_SIZE 10


// set function  vefore ls -la 
void list_dir(DIR *stack,char *base_path,unsigned int deepth,unsigned int new_deep);

// modifed puts_list argments 
void puts_list(struct dirent *dp);
void get_detail(mode_t mode,char *get_show);
char* pathlink(mode_t mode,char* name);
char* get_username(uid_t uid);
char* get_groupname(gid_t gid);
unsigned int sumTotal(DIR *dir,struct dirent *dp);

// make new function  
void search_directory(DIR *stack,DIR *dir,struct dirent *dp,char *now_path,unsigned int deepth,unsigned int new_deep);
void push_stack(DIR *stack,DIR *dirp,unsigned int deepth,unsigned int new_deep);

int main(int argc, char * argv[]) {

    unsigned int deepth=0;
    unsigned int new_deep=0;
    DIR *stack = (DIR *)calloc(sizeof(DIR),STACK_SIZE);


    char *path = argc >1 ? argv[1]:".";
    list_dir(stack,path,deepth,new_deep);

    free(stack);
    return 0;
}

/**
 * list_dir is use opendir and reaadir.
 * print is total block  .
 */

void list_dir(DIR *stack,char *base_path,unsigned int deepth,unsigned int new_deep){

    DIR *dir;
    struct dirent *dp;

    dir = opendir(base_path);
    
    if(dir == NULL || chdir(base_path) != 0){
        perror(base_path);
        return ;
     }else{
         push_stack(stack,dir,deepth,new_deep);
     }

    printf("total %d\n",sumTotal(dir,dp));

    while ((dp = readdir(dir)) !=NULL) {
         puts_list(dp);
    }
    rewinddir(dir);

    search_directory(stack,dir,dp,base_path,deepth,new_deep);

    closedir(dir);
}

  /**
   * print ls elemtns and sum block size caluculation.
   */

void puts_list(struct dirent *dp){

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

    /**
     * get file mode . the entry type,owner permissions,and group permissions.
     * show dis mode example S_IFBLK for man stat(lstat) pages
     * get_show is examle "-rw-r--r--"
     */

void get_detail(mode_t mode,char *get_show){

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

/*
 * find direcotory at change dir and roopback 
 */


void search_directory(DIR *stack,DIR *dir,struct dirent *dp,char *now_path,unsigned int deepth,unsigned int new_deep){

   char next_path[PATH_MAX];
   struct stat sb;

   while((dp = readdir(dir)) !=NULL){     

        /*
         * This function search direcotory not use except direcotory files
         */

       if(dp->d_type == DT_DIR){
           /*
            * exclusion current and parent
            */
           if(strcmp(dp->d_name,".")==0 ||strcmp(dp->d_name,"..")==0){
            continue;
            }
    
           memset(next_path,0,sizeof(next_path));
           sprintf(next_path,"%s/%s",now_path,dp->d_name);
           printf("%s:\n",next_path);
           list_dir(stack,next_path,deepth,new_deep);
        }
   }


}

// stack push

void push_stack(DIR *stack,DIR *dir,unsigned int deepth,unsigned int new_deep){

    if(deepth >= new_deep + STACK_SIZE){
        DIR *new;
        new_deep++;
        new = (DIR *)realloc(stack,sizeof(DIR)* (STACK_SIZE + new_deep));

        if (new == NULL) {
            free(stack);
        } else {
            dir = new;
        }
    }
        stack[deepth] = *dir;
        deepth++;
}



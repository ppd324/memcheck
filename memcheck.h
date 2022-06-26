//
// Created by 裴沛东 on 2022/6/26.
//

#ifndef WAITCHILD_MEMCHECK_H
#define WAITCHILD_MEMCHECK_H
#define ENABLE_MEMCHEAK 1
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFSIZE 100
#if ENABLE_MEMCHEAK
void* malloc_hook(size_t size,const char *file,const char* func,int line) {

    void* p = malloc(size);
    char buff[BUFFSIZE] = {0};
    sprintf(buff,"./mem/%p.mem",p);
    FILE *fp = fopen(buff,"w");
    if(fp == NULL) {
        printf("failed to open %s",buff);
        return p;
    }
    fprintf(fp,"[+%s:%d] malloc --> addr %p,size:%zu\n",file,line,p,size);
    printf("[+%s:%d] malloc --> addr %p,size:%zu\n",file,line,p,size);
    fclose(fp);
    return p;
}
void free_hook(void *p,const char *file,const char* func,int line) {
    char buff[BUFFSIZE] = {0};
    sprintf(buff,"./mem/%p.mem",p);
    if(unlink(buff) < 0) {
        printf("double free\n");
        printf("[+%s:%d] double free --> addr %p\n",file,line,p);
    }
    free(p);
}
#define malloc(size) malloc_hook(size,__FILE__,__func__,__LINE__)
#define free(p) free_hook(p,__FILE__,__func__,__LINE__)
#endif

#endif //WAITCHILD_MEMCHECK_H

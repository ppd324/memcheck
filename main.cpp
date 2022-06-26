#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "memcheck.h"
int main() {
//    pid_t child  = fork();
//    if(child > 0) { //父进程
//        printf("child pid %d\n",child);
//        waitpid(-1,NULL,0);
//        printf("wait child\n");
//    } else if(child == 0) {
//        execl("ls", "ls","-l", NULL);
//    }
    void *p = malloc(20);
    free(p);
    void *p1 = malloc(30);
    free(p1);
    int *p2 = new int(10);
    delete p2;
    return 0;
}

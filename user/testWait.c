#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    // int pid = fork();
    // int exitCode = -1;
    // if(pid > 0) {
    //     printf("parent: child=%d\n", pid);
    //     pid = wait(&exitCode);
    //     printf("child %d is done\n", pid);
    //     printf("wait code is %d \n", exitCode);
    // }
    // else if(pid == 0) {
    //     printf("child: exiting\n");
    //     exit(0);
    // } else {
    //     printf("fork error\n");
    // }
    if(fork() == 0) {
        write(1, "hello ", 6);
        exit(0);
    }else {
        wait(0);
        write(1, "world\n", 6);
    }
    exit(0);
}
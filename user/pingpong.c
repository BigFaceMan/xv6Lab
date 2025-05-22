#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);

    if (fork()) {
        char buf[1] = {'p'};
        write(p1[1], buf, 1);

        int len = read(p2[0], buf, 1);
        if (len > 0) {
            printf("%d: received pong\n", getpid());
        }
    } else {
        char buf[1];
        int len = read(p1[0], buf, 1);
        if (len > 0) {
            printf("%d: received ping\n", getpid());
            write(p2[1], buf, 1);
        }
    }

    // if (fork()) {
    //     wait(0);
    //     printf("%d: received pong\n", getpid());
    // } else {
        
    //     printf("%d: received ping\n", getpid());
    // }
    exit(0);
}

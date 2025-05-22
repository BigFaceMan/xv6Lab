#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void cCh(int fp[2], int fr) {
    int p[2];
    // pipe(p);
    while(pipe(p) == -1) {
        sleep(1);
    }
    // printf("wakeup\n");

    fp[0] = p[0];
    fp[1] = p[1];

    if (!fork()) {
        if (fr != -1) {
            close(fr);
        }
        int cp[2] = {-1, -1};
        close(p[1]);
        int gNum = -1;
        int primeBase = -1;
        int ncCh = 1;
        while (read(p[0], &gNum, sizeof(gNum))) {
            if (primeBase == -1) {
                primeBase = gNum;
                printf("prime %d\n", primeBase);
            } else {
                if (gNum % primeBase) {
                    if (ncCh) {
                        ncCh = 0;
                        cCh(cp, p[0]);
                        close(cp[0]);
                    }
                    write(cp[1], &gNum, sizeof(gNum));
                }
            }
        }
        if (cp[1] != -1) {
            close(cp[1]);
        }
        close(p[0]);
        wait(0);
        exit(0);
    } 
}
int main(int argc, char *argv[]) {
    int p[2];
    cCh(p, -1);
    close(p[0]);
    for (int i = 2; i <= 280; i ++) {
        write(p[1], &i, sizeof(i));
    }
    close(p[1]);
    wait(0);
    exit(0);
}

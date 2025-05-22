#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAXARGS 32

int readline(char *buf) {
    int n = 0;
    while (read(0, buf + n, 1)) {
        if (buf[n] == '\n') {
            return n;
        }
        n ++;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    char buf[200];
    char *targv[MAXARGS];
    int len;
    while ((len = readline(buf)) != 0) {
        buf[len] = 0;
        int i = 0;
        while (i < argc - 1) {
            targv[i] = argv[i + 1];
            i ++;
        }
        targv[i] = buf;
        targv[i + 1] = 0;
        if (!fork()) {
            exec(argv[1], targv);
        }
        wait(0);
    }
    exit(0);
}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("please input params sleep time!\n");
        exit(0);
    }
    int time = atoi(argv[1]);
    printf("(nothing happens for a little while)\n");
    sleep(time);
    exit(0);
}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
 // 输出清屏控制码：\033 是 ESC，[2J 是清屏，[H 是光标移到左上角
    printf("\033[2J\033[H");
    exit(0);
}

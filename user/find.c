#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char* fmtname(char *path) {
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void find(char *path, char *tag) {
    char buf[512], *p;
    char *name;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, O_RDONLY)) < 0){
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type){
        case T_DEVICE:
        case T_FILE:
            name = path + strlen(path) - 1;
            while (*name && *name != '/') {
                name --;
            }
            name ++;
            if (!strcmp(name, tag)) {
                // printf("%s %d %d %d\n", fmtname(path), st.type, st.ino, (int) st.size);
                printf(path);
                printf("\n");

            }
            break;

        case T_DIR:
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
                printf("ls: path too long\n");
                break;
            }
            strcpy(buf, path);
            p = buf+strlen(buf) - 1;
            if (*p != '/') {
                p ++;
                *p = '/';
            }
            p ++;
            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if(de.inum == 0)
                    continue;
                if (!strcmp(".", de.name) || !strcmp("..", de.name)) 
                    continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                find(buf, tag);
            }
            break;
    }
    close(fd);
    
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("no args\n");
        exit(0);
    }
    char *root = argv[1];
    
    find(root, argv[2]);

    exit(0);
}

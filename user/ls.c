#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
// 这个函数 fmtname 用于从一个路径中提取文件名，并返回一个固定长度的字符串。它会将文件名填
// 充到固定长度 DIRSIZ（14 个字符），并在文件名长度不足 DIRSIZ 时，用空格填充剩余的字符
char *fmtname(char *path) {
    static char buf[DIRSIZ + 1];
    char *p;

    // Find first character after last slash.
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    // Return blank-padded name.
    if (strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));
    return buf;

}

void ls(char *path) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    //printf("%s", path);
    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "ls: cannot stat %s\n", path); 
        close(fd);
        return;
    }
    //printf("%s", p1);
    switch (st.type) {
        case T_DEVICE:
        case T_FILE:
            printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
        break;
  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
        printf("ls: path too long\n");
        break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0)
            continue;
        
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0) {
            printf("ls: cannot stat %s\n", buf);
            continue;
        }   
        
            printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }    
    break; 
  }
 
  close(fd);
}

int main(int argc, char *argv[]) {
  int i;

    if (argc < 2) {
        ls(".");
        exit(0);
    }
    for (i = 1; i < argc; i++)
        ls(argv[i]);
  exit(0);
}

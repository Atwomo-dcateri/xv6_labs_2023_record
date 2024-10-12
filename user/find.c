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
    //printf("%s \n", buf);
    return;
}


char* find(char *path, char *name, char *origin) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    
    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "ls: cannot open %s\n", path);
        return 0;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "ls: cannot stat %s\n", path); 
        close(fd);
        return;
    }

    switch (st.type) {
    
        case T_DIR:
    
        // if (strcmp(path,".") == 0)
        // {
        //     printf("./%s \n", path);
        // }
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
            printf("ls: path too long\n");
            break;
        }

        strcpy(buf, path);
        p = buf + strlen(buf);//p 是一个字符指针，用来指向路径 buf 的末尾
        *p++ = '/';
        char origin_path[100] ;
        strcpy(origin_path, buf);
        //strcpy(origin_dir.buf);
        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            if (de.inum == 0)
                continue;
            if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            //p[DIRSIZ] = 0;
            if (stat(buf, &st) < 0) {
                printf("ls: cannot stat %s\n", buf);
                continue;
            }
            //printf("%s%s%d \n", origin_dir, fmtname(buf), strlen(buf));
            if (strcmp(de.name, name) == 0)
            {
                printf("%s%s \n", origin_path, fmtname(buf));
            }
            if (st.type == 1)
            {   
                
                find(de.name, name, path);
                return strcpy(origin_path, origin);
            } 
        }
         
        break;
  }
  close(fd);
  return path;
}

void ls(char *path) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "ls: cannot stat %s\n", path); 
        close(fd);
        return;
    }

    switch (st.type) {
    
        case T_DIR:
        if (strcmp(path,".") == 0)
        {
            break;
        }
        if (strcmp(path,"a") == 0)
        {
            printf("./%s \n", path);
        }
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
            printf("ls: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);//p 是一个字符指针，用来指向路径 buf 的末尾
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
            if (st.type == T_FILE)
            {
                printf("./%s/%s\n", path, fmtname(buf));
            }
             
        }
                   
        break;
  }
  close(fd);
}



int main(int argc, char *argv[]) {
    
    char path[100];

    if (argc > 2)
    {
        find(argv[1], argv[2], path);
    }
    
    for (uint8 i = 0; i < strlen(path); i++)
    {
        printf("%s", path[i]);
    }
    
    exit(0);
}
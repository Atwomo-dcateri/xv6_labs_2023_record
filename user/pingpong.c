#include "user/user.h"

/*int main(int argc, char const *argv[])
{   
    
    int pid1 = fork();
    int* pid2 = &pid1;
    
    if (pid1 == 0)
    {   
        int p1 = getpid();
        printf("%d: received ping\n", p1);
        exit(0);
    }
    if (pid1 > 0)
    {   
        wait(pid2);
        int p2 = getpid();

        printf("%d: received pong\n", p2);
    }
    
    if (pid1 < 0)
    {
        printf("fork error!");
    }
    
    return 0;
}*/

int main(int argc, char const *argv[])
{
    /* code */
    int p[2];
    char *args[2];
    args[0] = "received ping\n";
    args[1] = "received pong\n";
    pipe(p);

    int pid1 = fork();

    if (pid1 == 0)
    {   
        int fd1 = dup(p[1]);
        // close(p[0]);
        //hello world\n
        //close(p[1]);
        close(0);
        int p1 = getpid();
        write(p[0], args[1], 1);
        close(p[1]);
        close(p[0]);
        read(fd1, args[0], 14);
        printf("%d: %s", p1, args[0]);
        close(fd1);
    }
    if (pid1 > 0)
    {   
        close(0);
        // dup(p[1]);
        // close(p[0]);
        int p2 = getpid();
        read(p[1], args[1], 14);
        close(p[1]);
        write(p[0], args[0], 14);
        wait(&pid1);
        printf("%d: %s", p2, args[1]);
        close(p[0]);
       
    }
    if (pid1 < 0)
    {
        printf("fork error!");
    }
    return 0;
}

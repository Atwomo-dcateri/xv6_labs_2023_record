#include "user/user.h"
//#include "stdio.h"

int main(int argc, char const *argv[])
{
    /* code */
    int p[3];
    pipe(p);
    int array[35];

    close(p[0]);
    close(p[1]);
    close(p[2]);
    close(0);
    for (int i = 0; i < 35; i++)
    {
        array[i] = i + 2;
        
    }
    //printf("%d", array[0]);
    int pid1 = fork();

    if (pid1 == 0)
    {   
        close(p[1]);
        close(p[2]);
        //close(p[0]);
    
        printf("primes: %d \n", array[0]);
        for (int i = 1; i <= 33; i++)
        {   
            
            if (array[i]%array[0] == 0)
            {
                
            } else {

                write(p[0], &array[i], 2);
            }
            close(p[0]);
        }
        //exit(0);        
    }
    
    int pid2 = fork();

    if (pid2 == 0){
        int a = 45;
        close(p[0]);
        //close(p[1]);
        close(p[2]);
        while (a != 0)
        {   int i = 0;
            a = read(p[1], &array[i], 2);
            i++;
        }
        
        wait(&pid1);
        printf("primes: %d \n", array[0]);
        close(p[1]);
        exit(0);
    }
    wait(&pid2);
    return 0;
}
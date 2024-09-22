#include "user/user.h"
//#include "stdio.h"
//p[0]read，p[1]write


int main(int argc, char const *argv[])
{
    /* code */
    int p[2];
    int p1[2];
    int p2[2];
    
    pipe(p2);
    pipe(p1);
    pipe(p);

    int array1[34];
    for (int i = 0; i < 34; i++)
    {
        array1[i] = i + 2;
        
    }

    int pid1 = fork();

    if (pid1 == 0)
    {   
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);
        close(p[0]);
        printf("prime %d \n", array1[0]);
        //printf("prime:%d \n", array1[1]);
        for (int i = 1; i < 34; i++)
        {   
            
            if (array1[i] % array1[0] != 0)
            {
                write(p[1], &array1[i], sizeof(int));
            } 
            
        }
        close(p[1]);
        exit(0);        
    }
    
    int pid2 = fork();

    if (pid2 == 0){
        int array2[20];
        int a = 1;
        int i = 0;

        close(p[1]);
        close(p1[0]);

        close(p2[0]);
        close(p2[1]);
        while (a > 0 )
        {   
            a = read(p[0], &array2[i], sizeof(int));
            i++;
        }

        printf("prime %d \n", array2[0]);
        for (int j = 1; i - 1 > j; j++)
        {
            if (array2[j]%array2[0] != 0)
                {
                    write(p1[1], &array2[j], sizeof(int));
                    
                }

        }
        
        close(p1[1]);
        close(p[0]);
        exit(0);
    }

    int pid3 = fork();

    if (pid3 == 0)
    {
        int array3[15];
        int a = 1;
        int i = 0;
        close(p[0]);
        close(p[1]);
        close(p1[1]);
        close(p2[0]);
        while(a > 0) {

            a = read(p1[0], &array3[i], sizeof(int));
            i++;
        }

        printf("prime %d \n", array3[0]);

        for ( int j = 1; i - 1 > j; j++)
        {
            if (array3[j]%array3[0] != 0)
            {
                write(p2[1], &array3[j], sizeof(int));
            }
            
        }
        
        close(p1[0]);
        close(p2[1]);
        exit(0);

    }
    int pid4 = fork();

    if (pid4 == 0)
    {   
        int read_array[15];
        int a = 1;
        int i = 0;

        close(p[0]);
        close(p[1]);
        close(p1[0]);
        close(p1[1]);

        close(p2[1]);
        while (a > 0)
        {
            a = read(p2[0], &read_array[i], sizeof(int));
            i++;
        }

        printf("prime %d \n", read_array[0]);
        for (int j = 1; j < i - 1; j++)
        {
            if (read_array[j] % read_array[0])
            {
                printf("prime %d \n", read_array[j]);
            }
            
        }
        
        close(p2[0]);
        exit(0);
        
    }
        
    close(p[0]);
    close(p[1]);
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);

    wait(0);
    wait(0);
    wait(0);
    wait(0);
    exit(0);

    return 0;
}
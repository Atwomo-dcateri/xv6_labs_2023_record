#include "kernel/types.h"
#include "user/user.h"
//#include "user/ulib.c"

int main(int argc, char *args[]){

    if (argc < 2)
    {
        printf("Please input sleep time\n");
        exit(1);
    };
    int s_time = 0;

    s_time = atoi(args[1]); 
    if (s_time < 0)
    {
        printf("Please input crroet time!\n");
        exit(1);
    };
    
    sleep(s_time);
    exit(0);

}


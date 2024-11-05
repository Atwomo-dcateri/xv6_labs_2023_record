#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"


#define NULL '\0'

#define MAXLEN 512
    
char buffer[512];

void main(int args, char *argc[]) {
    
    if (args < 2)
    {
        printf("Invaild xargs value! \n");
    }
    
    
    //if (fork() == 0) {
        
        char *p;
        p = buffer;
        char *argcs[MAXARG] =  {"\0"};
        int index = 0;
        char temp_array[MAXLEN] = {"\0"};
        //int read_byte = 0;

        int n = 0 ;
        for(int i = 1;i < args; i++)
            argcs[index++] = argc[i];
        
        
        //p = buffer;
        //argcs[index] = temp_array;
        //argcs[index + 1] = NULL;
        //

        // for (int i = 0; i < strlen(buffer); i++)
        // {
        //     printf("%c", buffer[i]);//打印的是字符而非字符串
        // }
        int index1 = 0;
        while ((n = read(0, buffer, MAXLEN)) != 0){
        //printf("%d", strlen(buffer));
        argcs[index] = temp_array;
        for (; *p != '\0'; p++) {//为什么会越界
       
            if (*p == '\n') {
                
        // for(int i = 0; i < strlen(buffer); ++i){

        //     //index1++;
        //     if (buffer[i] == '\n')
        //     {
             
                if(fork() == 0) {

                    exec(argc[1], argcs);
                }
                wait(0);
                
            } else {
              
                if (index1 > MAXLEN - 1)
                {
                   fprintf(0,"Input exceed buffer size.\n");
                   exit(0);
                }
                
                //temp_array[i] = buffer[i];
                temp_array[index1] = buffer[index1];
                index1++;
            }
        }
    };
    exit(0);   
}
    
   

/*echo hello world\n | xargs echo bye*/
//acgfun.net
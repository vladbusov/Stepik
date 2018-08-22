#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#define BUFFER 256


int main(int argc, const char *argv[])
{
    pid_t proc = getpid();
    printf("%d\n", proc);
    proc = fork();
    switch(proc)
    {
    case  0: 
                setsid();
                fclose(stdin);
                fclose(stdout);
                fclose(stderr);
                sleep(1000);
                break;
    case -1:  
                return -1;
                break; 
    default: 
                exit(0);
                break;
    }
   
    return 0;
}

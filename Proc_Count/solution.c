#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
 
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include <locale.h>
#include <regex.h>

#define PATTERN "^[0-9]*$"
#define CMP_STRING "genenv"

int main(int argc, const char *argv[])
{
    DIR* curentMainDir = opendir("/proc");
    struct dirent *entry;

    regex_t preg;
    int err,regerr;

    err = regcomp(&preg, PATTERN, REG_EXTENDED);

    if (err != 0) {
        char buff[512];
        regerror(err, &preg, buff, sizeof(buff));
        printf("%s\n",buff);
    }

    regmatch_t pm;
    int counter = 0;

    while( (entry = readdir(curentMainDir)) != NULL)
    {
        regerr = regexec( &preg, entry->d_name, 0, &pm, 0);
        if (regerr == 0) {
            char filePath[512];
            sprintf(filePath,"/proc/%s/comm", entry->d_name);
            FILE* fp;
    
            fp = fopen(filePath,"r");
	        if(fp == NULL)
	        {
		        printf("не могу открыть файл '%s'",filePath);
	        }
            
            char nameBuffer[256];
            fgets(nameBuffer, sizeof(nameBuffer), fp);
            
            if (strcmp(CMP_STRING, nameBuffer) == 0)
            {
                counter++;
            }
            fclose(fp);
        }
    }
    printf("%d\n",counter);
    return 0;
}

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

#define BUFFER 256

int counter = 1;

pid_t getparent(pid_t cpid)
{
	FILE* fp;
	char tmp[BUFFER];
	sprintf(tmp, "/proc/%d/status", cpid);
	if ((fp = fopen(tmp,"r"))==NULL)
	{
        return NULL;	
	}
	const char* strId = "ppid:\t";
	const int strIdLen = strlen(strId);
	while(fgets(tmp, sizeof(tmp)-1, fp))	
	{
		if (!strncasecmp(strId,tmp,strIdLen))
		{
			sscanf(tmp + strIdLen, "%s", tmp);
            pid_t ppid;
            char buff[512];
			sprintf(buff, "%s", tmp + strIdLen);
            ppid = (pid_t) atoi(buff);
            fclose(fp);
			return ppid;
		}
	}
    return NULL;
}


void find_in_dir( pid_t proc ) 
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

    while( (entry = readdir(curentMainDir)) != NULL)
    {
        if ( proc == getparent(atoi(entry->d_name)))
        {
            counter++;
            find_in_dir(atoi(entry->d_name));
        }
    }
    return;
}

int main(int argc, const char *argv[])
{
    find_in_dir(atoi(argv[1]));
    printf("%d\n", counter);
    return 0;
}

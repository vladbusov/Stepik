#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER 256

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
			return ppid;
		}
	}
    return NULL;
}

int main(int argc, const char *argv[])
{
    pid_t cpid = atoi(argv[1]); 
    printf( "%d\n", cpid );

    while(cpid != 1) {
        cpid = getparent(cpid);
        printf("%d\n", cpid); 
    }

    return 0;
}

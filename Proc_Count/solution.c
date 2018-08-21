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
            counter++;
        }
    }
    printf("%d\n",counter);
    return 0;
}

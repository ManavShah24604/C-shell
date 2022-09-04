#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>

void echo()
{
    char *second;
    second = strtok(NULL, "\n");

    if (second == 0)
    {
        printf("\n");
        return;
    }
    else
    {
        char *third = strtok(second, " ""\t");
        while(third!=0 && third!=NULL)
        {
            printf("%s ",third);
            third = strtok(NULL, " ""\t");
        }
        printf("\n");
    }
}
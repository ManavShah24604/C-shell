#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#define NEG -10000000
void pinfo(int num)
{
    int pidnumber = getpid();
    if (num != NEG)
        pidnumber = num;
    printf("%d\n",pidnumber);
    char original[100010];
    sprintf(original, "/proc/%d/stat", pidnumber);
    FILE *filepointer;
    filepointer = fopen(original, "r");
    if(filepointer==NULL)
    {
        printf("No such pid exists\n");
    }
    char file_contents[100][10000];
    int count = 0;
    char temp[10000];
    while (fscanf(filepointer, "%[^ ] ", temp) != EOF)
    {
        strcpy(file_contents[count], temp);
        // printf("%s %d\n", file_contents[count],count);
        count++;
    }
    fclose(filepointer);
    printf("pid : %d\n", pidnumber);
    if (strcmp(file_contents[2], "Z") == 0)
        printf("process Status : {%s}\n", file_contents[2]);
    else
    {
        if (strcpy(file_contents[4], file_contents[7]) == 0)
            printf("process Status : {%s+}\n", file_contents[2]);
        else
            printf("process Status : {%s}\n", file_contents[2]);
    }
    printf("memory : %s\n", file_contents[22]);
    char sometemp[100010], new[1100];
    sprintf(new, "/proc/%d/exe", pidnumber);
    printf("%s\n", new);
    readlink(new, sometemp, 100000);
    printf("executable Path : %s\n", sometemp);
}
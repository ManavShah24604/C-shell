#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
// #define continue return
int check = 0;
char root[2560];
void funcofcd()
{
    char *second;
    char lastcwd[2][100010];
    getcwd(lastcwd[1], sizeof(lastcwd[1]));
    second = strtok(NULL, " "
                          "\t");
    // printf("%s\n", second);
    char *third;
    third = strtok(NULL, " "
                         "\t");
    if (third)
    {
        printf("bash: cd: too many arguments\n");
        return;
    }
    if (second == 0)
    {
        chdir(root);
    }
    else if (strcmp(second, "..") == 0)
    {
        chdir("..");
    }
    else if (strcmp(second, "--") == 0 || strcmp(second, "~") == 0)
    {
        chdir(root);
    }
    else if (strcmp(second, "-") == 0)
    {
        if (check == 0)
        {
            printf("-bash: cd: OLDPWD not set\n");
            return;
        }
        else
        {
            check = 1;
            // printf("%s\n", lastcwd[0]);
            chdir(lastcwd[0]);
        }
    }
    else if (strlen(second))
    {
        if (chdir(second) == -1)
        {
            printf("bash: cd: %s: No such file or directory\n", second);
            return;
        }
    }
    strcpy(lastcwd[0], lastcwd[1]);
    getcwd(lastcwd[1], sizeof(lastcwd[1]));
    check = 1;
    // printf("%s\n", second);
}
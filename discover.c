#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <string.h>
#include <time.h>
#include <grp.h>
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
// char answers[10000][100];
int flagf = 0, flagd = 0;
char directory[10000];
char filetosearch[10101];
int i = 0;
char root[2560];
// void finalprint(char str[], int flag)
// {
//     char tempstr[10000];
//     tempstr[0]='\0';
//     getcwd(tempstr,sizeof(tempstr));
//     if (strstr(str, root) == NULL)
//     {
//         if (flag)
//         {
//             printf(BLUE "%s\n" RESET, str);
//         }
//         else
//             printf("%s\n", str);

//     }
//     else
//     {

//     }
// }
char currentdirectory[10000];

void func(char currentdir[])
{
    DIR *ls_dir;
    struct dirent *ls_struct;
    struct stat new;
    if (stat(currentdir, &new) == 0)
    {
        ls_dir = opendir(currentdir);
        // printf("%s\n", currentdir);
        if (ls_dir != NULL)
        {
            ls_struct = readdir(ls_dir);
            while (ls_struct != 0 && ls_struct != NULL)
            {
                // printf("%s\n",ls_struct->d_name);
                char str[100000];
                str[0] = '\0';
                strcpy(str, currentdir);
                // printf("%s\n",currentdir);
                strcat(str, "/");
                strcat(str, ls_struct->d_name);
                if (filetosearch == 0 || filetosearch == NULL || strlen(filetosearch) == 0)
                {
                    if (opendir(str) != NULL)
                    {
                        if (flagd == 1 || flagf == 0)
                        {
                            // printf("%d %d\n",flagd,flagf);
                            int len = strlen(currentdirectory);
                            for (int it = len + 1; it < strlen(str); it++)
                            {
                                printf("%c", str[it]);
                            }
                            printf("\n");
                            // finalprint(str, 1);
                            // printf(BLUE "%s\n" RESET, str);
                        }
                    }
                    else if (flagf == 1 || flagd == 0)
                    {
                        int len = strlen(currentdirectory);
                        // printf(".\n");
                        for (int it = len + 1; it < strlen(str); it++)
                        {
                            printf("%c", str[it]);
                        }
                        printf("\n");
                        // finalprint(str, 0);
                        // printf("%s\n", str);
                    }
                    // ls_struct = readdir(ls_dir);
                }
                else
                {
                    if (strcmp(ls_struct->d_name, filetosearch) == 0)
                    {
                        if (opendir(str) != NULL && flagf == 1 && flagd == 0)
                        {
                        }
                        else if (opendir(str) == NULL && flagd == 1 && flagf == 0)
                        {
                        }
                        else
                        {
                            // strcpy(answers[i], ls_struct->d_name);
                            // i++;
                            int len = strlen(currentdirectory);
                            for (int it = len + 1; it < strlen(str); it++)
                            {
                                printf("%c", str[it]);
                            }
                            printf("\n");
                            // finalprint(str, 0);
                            // printf("%s\n", str);
                        }
                    }
                    if (strcmp(ls_struct->d_name, ".") == 0 || strcmp(ls_struct->d_name, "..") == 0)
                    {
                        ls_struct = readdir(ls_dir);
                        continue;
                    }
                }
                if (opendir(str) != NULL)
                {
                    int len = strlen(str);
                    if (str[len - 1] != '.')
                        func(str);
                }
                // printf("%s\n", str);
                ls_struct = readdir(ls_dir);
            }
        }
    }
    else
    {
        return;
    }
}

void discover()
{
    // memset(answers, '\0', sizeof(answers));
    char *read2;
    flagd = 0;
    getcwd(currentdirectory, sizeof(currentdirectory));
    flagf = 0;
    read2 = strtok(NULL, " "
                         "\t");
    directory[0] = '\0';
    filetosearch[0] = '\0';
    while (read2 != 0 && read2 != NULL)
    {
        if (strcmp(read2, "-d") == 0)
        {
            flagd = 1;
        }
        else if (strcmp(read2, "-f") == 0)
            flagf = 1;
        else if (strcmp(read2, "-df") == 0)
        {
            flagf = 1;
            flagd = 1;
        }

        else if (read2[0] == '"')
        {
            int len = strlen(read2);
            filetosearch[0] = '\0';
            for (int i = 1; i < len - 1; i++)
            {
                // printf("%c\n",read2[i]);
                filetosearch[i - 1] = read2[i];
            }
        }
        else
        {
            strcpy(directory, read2);
        }
        // printf("%s\n", read2);
        read2 = strtok(NULL, " "
                             "\t");
    }
    char current[10101];
    getcwd(current, sizeof(current));
    strcat(current, "/");
    if (directory == 0 || directory == NULL || strlen(directory) == 0)
    {
        directory[0] = '.';
        directory[1] = '\0';
    }
    strcat(current, directory);
    // printf("%s\n",filetosearch);
    func(current);
}
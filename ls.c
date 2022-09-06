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
char root[2560];
void ls()
{
    int flaga = 0, flagl = 0, flagdot = 0;
    char *database[100010];
    int count = 0;
    database[0] = NULL;
    database[count] = strtok(NULL, " "
                                   "\t");
    while (database[count] != 0)
    {
       
        count++;
        database[count] = strtok(NULL, " "
                                       "\t");
    }
    char *data[1001];
    data[0] = NULL;
    data[1] = NULL;
    int some = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(database[i], "-a") == 0)
        {
            flaga++;
        }
        else if (strcmp(database[i], "-l") == 0)
        {
            flagl++;
        }
        else if (strcmp(database[i], "-al") == 0 || strcmp(database[i], "-la") == 0)
        {
            flagl++;
            flaga++;
        }
        else
        {
            // printf("%s", database[i]);
            data[some] = (char *)malloc(10000);
            if (strcmp(database[i], "~") == 0)
            {
                strcpy(data[some], root);
            }
            else
                strcpy(data[some], database[i]);
            some++;
        }
    }
    DIR *ls_dir;
    struct dirent *ls_struct;
    int i = 0;
    do
    {
        if (flagl == 0)
        {

            if (data[i] == 0)
            {
                ls_dir = opendir("."); // as this ls  function gives the content of current dir
            }
            else
            {
                ls_dir = opendir(data[i]);
            }
            if (ls_dir == NULL)
            {
                struct stat somefile, newfile;
                struct stat ss;
                char tempcomplete[10100];
                tempcomplete[0] = '\0';
                getcwd(tempcomplete, sizeof(tempcomplete));
                strcat(tempcomplete, "/");
                if (data[i] != 0)
                    strcat(tempcomplete, data[i]);

                if (stat(tempcomplete, &newfile) == 0)
                {
                    stat(tempcomplete, &somefile);
                    int len = strlen(data[i]), dotpresent = 0;
                    for (int someit = len - 1; someit >= 0; someit--)
                    {
                        if (data[i][someit] == '/')
                        {
                            if (data[i][someit + 1] == '.')
                            {
                                dotpresent = 1;
                                break;
                            }
                        }
                    }
                    if (dotpresent == 1)
                    {
                        if (flaga == 1)
                        {
                            if (somefile.st_mode & S_IXUSR)
                                printf(GREEN "%s " RESET, data[i]);
                            else
                                printf("%s ", data[i]);
                        }
                    }
                    else
                    {
                        if (somefile.st_mode & S_IXUSR)
                            printf(GREEN "%s " RESET, data[i]);
                        else
                        {
                            printf("%s ", data[i]);
                        }
                    }
                }
                else
                    printf("error");
            }
            else
            {
                ls_struct = readdir(ls_dir);
                while (ls_struct != NULL)
                {
                    struct stat somefile, newfile;
                    struct stat ss;
                    char tempcomplete[10100];
                    tempcomplete[0] = '\0';
                    getcwd(tempcomplete, sizeof(tempcomplete));
                    strcat(tempcomplete, "/");
                    if (data[i] != 0)
                        strcat(tempcomplete, data[i]);
                    strcat(tempcomplete, "/");
                    strcat(tempcomplete, ls_struct->d_name);
                    stat(tempcomplete, &ss);
                    stat(tempcomplete, &somefile);
                    // printf("ishere \n");
                    char temp[100010];
                    temp[0] = '\0';
                    strcpy(temp, ls_struct->d_name);
                    if (temp[0] == '.' && flaga == 0)
                    {
                        ls_struct = readdir(ls_dir);
                        continue;
                    }
                    if (ss.st_mode & S_ISDIR(ss.st_mode))
                        printf(BLUE "%s  " RESET, temp);
                    else
                    {
                        if (ss.st_mode & S_IXUSR)
                            printf(GREEN "%s  " RESET, temp);
                        else
                            printf("%s  ", temp);
                    }
                    ls_struct = readdir(ls_dir);
                }
            }
            i++;
            printf("\n");
        }

        else
        {
            char temp[100010];
            if (data[i] == 0)
            {
                ls_dir = opendir("."); // as this ls  function gives the content of current dir
            }
            else
            {
                ls_dir = opendir(data[i]);
            }
            if (ls_dir == NULL)
            {
                struct stat somefile, newfile;
                struct stat ss;
                char tempcomplete[10100];
                tempcomplete[0] = '\0';
                getcwd(tempcomplete, sizeof(tempcomplete));
                strcat(tempcomplete, "/");
                if (data[i] != 0)
                    strcat(tempcomplete, data[i]);

                // printf("%s\n", tempcomplete);
                // stat(tempcomplete, &somefile);
                if (stat(tempcomplete, &newfile) == 0)
                {
                    // if (data[i][0] != '.')
                    //     printf(" %s ", data[i]);
                    temp[0] = '\0';
                    strcpy(temp, tempcomplete);
                    goto nextsection;
                }
                else
                    printf("error\n");
            }
            else
            {

                char seconddata[1010][100];
                int k = 0;
                long long tota = 0;
                while (1)
                {
                    ls_struct = readdir(ls_dir);
                    if (ls_struct == NULL)
                        break;
                    struct stat ss;
                    char tempcomplete[10100];
                    tempcomplete[0] = '\0';
                    getcwd(tempcomplete, sizeof(tempcomplete));
                    strcat(tempcomplete, "/");
                    if (data[i] != 0)
                        strcat(tempcomplete, data[i]);
                    strcat(tempcomplete, "/");
                    strcat(tempcomplete, ls_struct->d_name);
                    stat(tempcomplete, &ss);
                    tota += ss.st_blocks;
                    strcpy(seconddata[k], ls_struct->d_name);
                    if (seconddata[k][0] == '.' && flaga == 0)
                        tota -= ss.st_blocks;
                    k++;
                    // ls_struct = readdir(ls_dir);
                }
                for (int t = 0; t < k; t++)
                {
                    for (int y = 0; y < k - 1; y++)
                    {
                        if (strcmp(seconddata[y], seconddata[y + 1]) > 0)
                        {
                            char tempstr[10100];
                            strcpy(tempstr, seconddata[y]);
                            strcpy(seconddata[y], seconddata[y + 1]);
                            strcpy(seconddata[y + 1], tempstr);
                        }
                    }
                }
                if (data[i] != 0)
                    printf("%s:\n", data[i]);
                printf("total %lld\n", tota / 2);
                for (int t = 0; t < k; t++)
                {
                    // printf("ishere \n");

                    temp[0] = '\0';
                    strcpy(temp, seconddata[t]);
                nextsection:;
                    char complete[10100], tempcomplete[10100];
                    complete[0] = '\0';
                    getcwd(tempcomplete, sizeof(tempcomplete));
                    strcat(tempcomplete, "/");
                    if (data[i] != 0)
                        strcat(tempcomplete, data[i]);
                    strcat(tempcomplete, "/");
                    strcat(tempcomplete, temp);
                    if (temp[0] == '.' && flaga == 0)
                    {
                        ls_struct = readdir(ls_dir);
                        continue;
                    }
                    struct stat sss, newfile;
                    char permissions[10];
                    for (int j = 0; j < 10; j++)
                    {
                        permissions[j] = '-';
                    }
                    int somevar = stat(tempcomplete, &newfile);
                    if (somevar == 0 && S_ISDIR(newfile.st_mode)) // checking whether directory is there or not
                    {
                        permissions[0] = 'd';
                    }
                    if (newfile.st_mode & S_IRUSR) // checking user permissions for read
                    {
                        permissions[1] = 'r';
                    }

                    if (newfile.st_mode & S_IWUSR) // for write
                    {
                        permissions[2] = 'w';
                    }

                    if (newfile.st_mode & S_IXUSR) // for execute
                    {
                        permissions[3] = 'x';
                    }
                    if (newfile.st_mode & S_IRGRP) // checking group permissions
                    {
                        permissions[4] = 'r';
                    }
                    if (newfile.st_mode & S_IWGRP)
                    {
                        permissions[5] = 'w';
                    }
                    if (newfile.st_mode & S_IXGRP)
                    {
                        permissions[6] = 'x';
                    }
                    if (newfile.st_mode & S_IROTH) // checking Other permissions
                    {
                        permissions[7] = 'r';
                    }
                    if (newfile.st_mode & S_IWOTH)
                    {
                        permissions[8] = 'w';
                    }
                    if (newfile.st_mode & S_IXOTH)
                    {
                        permissions[9] = 'x';
                    }
                    // printf("total %ld\n", (newfile.st_blocks));

                    for (int j = 0; j < 9; j++)
                        printf("%c", permissions[j]);
                    printf("\t%ld\t", newfile.st_nlink);
                    struct passwd *password = getpwuid(newfile.st_uid);
                    struct group *grp = getgrgid(newfile.st_uid);
                    printf("%s\t%s\t", password->pw_name, grp->gr_name);
                    printf("%ld\t", newfile.st_size);
                    char temptime[100010];
                    temptime[0] = '\0';
                    strcpy(temptime, ctime(&newfile.st_ctime));
                    for (int j = 4; j <= 15; j++)
                    {
                        printf("%c", temptime[j]);
                    }
                    if (permissions[0] == 'd')
                        printf(BLUE "\t%s\n" RESET, temp);
                    else
                    {
                        if (permissions[3] == 'x')
                            printf(GREEN "\t%s\n" RESET, temp);
                        else
                            printf("\t%s\n", temp);
                    }
                }
            }
            i++;
            // printf("\n");
        }
        some--;
        closedir(ls_dir);
    } while (some > 0);
}
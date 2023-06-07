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
#include "header.h"
#include <time.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define NEG -10000000
char root[2560];
void mai(char input[])
{
    // strcat(input," ");
    int flagforjob = 0;
    // printf("%s\n",input);
    // printf("this is %s\n",input);
    if (strlen(input) == 1)
        return;
    input[strlen(input) - 1] = '\0';
    char str[10000];
    strcpy(str, input);
    if (strstr(input, "-r") != NULL)
    {
        flagforjob = 1;
    }
    else if (strstr(input, "-s") != NULL)
        flagforjob = 2;
    if (strlen(str) == 0)
    {
        return;
    }
    else
    {

        char *substr;
        char *storestrings[1000];
        int noofcommands = 0;
        storestrings[0] = strtok(str, ";");
        // printf("%s\n", storestrings[0]);
        while (storestrings[noofcommands] != 0 && storestrings[noofcommands] != NULL)
        {
            // printf("%s\n", substr);
            noofcommands++;
            storestrings[noofcommands] = strtok(NULL, ";");
            // printf("%s\n", storestrings[noofcommands]);
        }
        int i = 0;
        while (noofcommands--)
        {
            if (strstr(storestrings[i], "|") != NULL)
            {
                // printf("hewre\n");
                pipes(storestrings[i]);
            }
            else
            {
                char topasstobg[10100];
                strcpy(topasstobg, storestrings[i]);
                int someflag = 1;
                for (int someit = 0; someit < strlen(storestrings[i]); someit++)
                {
                    if (storestrings[i][someit] == '<' || storestrings[i][someit] == '>')
                    {
                        someflag = 0;
                        // printf("%s\n",storestrings[i]);
                        input_output(storestrings[i]);
                        break;
                    }
                }
                if (someflag == 1)
                {
                    char *first;
                    if (storestrings[i] != 0)
                    {
                        // printf("%d\n",strlen(storestrings[i]));
                    }
                    first = strtok(storestrings[i], " "
                                                    "\t");

                    if (first == 0)
                    {
                        break;
                    }
                    if (strcmp(first, "quit") == 0)
                    {
                        exit(0);
                    }

                    else if (strcmp(first, "cd") == 0)
                    {
                        funcofcd();
                    }
                    else if (strcmp(first, "pwd") == 0)
                    {
                        pwd();
                    }
                    else if (strcmp(first, "echo") == 0)
                    {
                        echo();
                    }
                    else if (strcmp(first, "discover") == 0)
                    {
                        discover();
                    }
                    else if (strcmp(first, "ls") == 0)
                    {
                        ls();
                    }
                    else if (strcmp(first, "jobs") == 0)
                    {
                        jobs(flagforjob);
                    }
                    else if (strcmp(first, "fg") == 0)
                    {
                        char *somepara = strtok(NULL, " "
                                                      "\t");
                        my_fg(atoi(somepara));
                    }
                    else if (strcmp(first, "bg") == 0)
                    {
                        char *somepara = strtok(NULL, " "
                                                      "\t");
                        my_bg(atoi(somepara));
                    }
                    else if (strcmp(first, "sig") == 0)
                    {
                        char *twotemp = strtok(NULL, " "
                                                     "\t");
                        if (twotemp != 0)
                        {
                            char *thirdtemp = strtok(NULL, " "
                                                           "\t");
                            if (thirdtemp != 0)
                            {
                                sig(atoi(twotemp), atoi(thirdtemp));
                            }
                            else
                                perror("Too few arguments\n");
                        }
                        else
                            perror("Too few arguments\n");
                    }
                    else if (strcmp(first, "pinfo") == 0)
                    {
                        char *second = strtok(NULL, " "
                                                    "\t");
                        if (second == 0)
                        {
                            pinfo(NEG);
                        }
                        else
                        {
                            int len = strlen(second);
                            int num = 0, pow = 1;
                            for (int iterator = len - 1; iterator >= 0; iterator--)
                            {
                                num += (second[iterator] - '0') * pow;
                                pow *= 10;
                            }
                            // printf("%d\n", num);
                            pinfo(num);
                        }
                    }
                    else if ((strcmp(first, "history")) == 0)
                    {
                        // history();
                        FILE *fhistory;
                        int count = 0;
                        char *file_contents = malloc(10000);
                        char temphistory[10000];
                        temphistory[0] = '\0';
                        strcpy(temphistory, root);
                        strcat(temphistory, "/");
                        strcat(temphistory, "history.txt");
                        fhistory = fopen(temphistory, "r");
                        while (fscanf(fhistory, "%[^\n] ", file_contents) != EOF)
                        {
                            // strcpy(history2[count], file_contents);
                            if (count > 10)
                                break;
                            printf("%s\n", file_contents);
                            count++;
                        }
                        int it = 0;
                        fclose(fhistory);
                    }
                    else
                    {
                        int someit = 0;
                        // if (topasstobg != 0 || topasstobg != NULL && topasstobg[0]!=0 )
                        bg_fg(topasstobg);
                        // printf("No such command exists\n");
                    }
                }
            }

            i++;
            substr = strtok(str, ";");
        }
    }
    return;
}
// fputs("hello  ", fhistory);

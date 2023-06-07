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
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define RED "\x1b[31m"

void fg2(char *input[], int l, int count)
{
    // printf("this is %s %s\n", input[0], input[1]);
    input[2] = NULL;
    pid_t pidnumber = fork();
    int it = 0;
    while (processpid[it] != 0)
    {
        it++;
    }
    if (pidnumber)
    {
        processpid[it] = pidnumber;
        processname[it] = (char *)malloc(sizeof(1000));
        strcpy(processname[it], input[0]);
    }
    if (pidnumber == -1)
    {
        perror("Child cannot be created\n");
    }
    if (pidnumber == 0)
    {
        setpgrp();
        int process = execvp(input[0], input);
        if (process != 0)
        {
            printf("Some wrong command\n");
            exit(0);
        }
    }
    else
        printf("[%d]  %d\n", count, pidnumber);
}

void bg_fg2(char input[])
{
    int i=0,someit=0;
    while (input[someit] == ' ')
    {
        someit++;
    }
    int flag = 0;
    char *topass[1010];
    int j = 0, k = 0, l = 0;
    topass[0] = (char *)malloc(1010);
    topass[0][0] = '\0';
    int len = strlen(input);
    // printf("%s\n", input);
    int count = 0;
    for ( i = someit; i < len; i++)
    {
        // if (input[i] == '\n')
        //     break;
        if (input[i] == ' ' || input[i] == '\t')
        {
            topass[j][k] = '\0';
            j++;
            topass[j] = (char *)malloc(1010);
            topass[j][0] = '\0';
            k = 0;
        }
        else if (input[i] == '&')
        {
            flag = 1;
            topass[j][k] = '\0';
            count++;
            topass[2] = NULL;
            fg2(topass, l, count);
            l = 0;
            j = 0;
            k = 0;
            if (i < len && input[i + 1] == ' ')
            {
                while (i < len && input[i + 1] == ' ')
                {
                    i++;
                }
                // i--;
            }
            if (i + 1 < len && (input[i] != ' ' || input[i] != '\t'))
            {
                flag = 2;
            }
        }

        else
        {
            topass[j][k] = input[i];
            // printf("%d %d",j,k);
            // printf("%c\n",topass[j][k]);
            k++;
            if (i < len && input[i + 1] == ' ')
            {
                while (i < len && input[i + 1] == ' ')
                {
                    i++;
                }
                i--;
            }
            if (i + 1 < len && (input[i] != ' ' || input[i] != '\t'))
            {
                flag = 2;
            }
        }
        l++;
    }
    topass[j][k] = '\0';
    // printf("this is %d\n", flag);
    if (flag == 0) // foreground process
    {
        int i = 0;
        char *secondarg[10000], *some;
        secondarg[i] = strtok(input, " "
                                     "\t");
        while (secondarg[i] != 0 && secondarg[i] != NULL)
        {
            // printf("here\n");
            i++;
            secondarg[i] = strtok(NULL, " "
                                        "\t");
        }
        // printf("%s\n", secondarg[0]);
        int val = fork(), sometemp;
        time_t start = time(NULL);
        if (val == -1)
        {
            // perror("Cannot create child process\n");
        }
        else if (val == 0)
        {
            // printf("%s %s\n",secondarg[0],secondarg);
            int ret = execvp(secondarg[0], secondarg);
            if (ret != 0)
            {
                // perror("No such command exists\n");
            }
        }
        else
        {
            waitpid(val, &sometemp, WUNTRACED | WCONTINUED);
            time_t end = time(NULL);
            sprintf(some, "took %ld seconds", end - start);
            // display_prompt(some);
        }
    }
    else if (flag == 2)
    {

        // printf("%s %s\n", topass[0], topass[1]);
        topass[2] = NULL;

        int val = fork(), sometemp;
        time_t start = time(NULL);
        if (val == -1)
        {
            // perror("Cannot create child process\n");
        }
        else if (val == 0)
        {
            // printf("%s %s\n",secondarg[0],secondarg);
            int ret = execvp(topass[0], topass);
            if (ret != 0)
            {
                // perror("No such command exists\n");
            }
        }
        else
        {
            waitpid(val, &sometemp, WUNTRACED | WCONTINUED);
            time_t end = time(NULL);
            // printf("Time takens is %ld\n", end - start);
            char some[10000];
            sprintf(some, "took %ld seconds", end - start);
            // display_prompt(some);
            // printf("\n");
        }
    }
}

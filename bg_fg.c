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

// int originalpid;
void fg(char *input[], int l, int count)
{
    // printf("this is %s %s\n", input[0], input[1]);
    input[2] = NULL;
    pid_t pidnumber = fork();
    // printf("ehre\n");

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
        // printf("%s  %s \n",input[0],input[1]);
        int process = execvp(input[0], input);
        if (process != 0)
        {
            printf("Some wrong command\n");
            exit(0);
        }
    }
    else
    {
        jobsarr[jobscount].index = jobscount + 1;
        jobsarr[jobscount].pid = pidnumber;
        jobsarr[jobscount].isrunning = 1;
        strcpy(jobsarr[jobscount].process, input[0]);
        // printf("%s %s\n",input[0],input[1]);
        if (input[1] != NULL)
        {
            strcat(jobsarr[jobscount].process, " ");
            // printf("%s\n", input[1]);
            strcat(jobsarr[jobscount].process, input[1]);
        }
        printf("[%d]  %d\n", jobsarr[jobscount].index, pidnumber);
        jobscount++;
    }
}

void bg_fg(char input[])
{
    int i = 0, someit = 0;
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
    for (i = someit; i < len; i++)
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

            fg(topass, l, count);
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
            // printf("%d %d\n",j,k);
            topass[j][k] = input[i];
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
            perror("Cannot create child process\n");
        }
        else if (val == 0)
        {
            // printf("%s %s\n",secondarg[0],secondarg[1]);
            int ret = execvp(secondarg[0], secondarg);
            if (ret != 0)
            {
                perror("No such command exists\n");
            }
        }
        else
        {

            waitpid(val, &sometemp, WUNTRACED | WCONTINUED);
            time_t end = time(NULL);
            sprintf(some, "took %ld seconds", end - start);
            display_prompt(some);
        }
    }
    else if (flag == 2) // foregrond process
    {
        // printf("here\n");
        // printf("%s %s\n", topass[0], topass[1]);
        topass[2] = NULL;

        int val = fork(), sometemp;
        time_t start = time(NULL);
        if (val == -1)
        {
            perror("Cannot create child process\n");
        }
        else if (val == 0)
        {
            // printf("%s %s\n",secondarg[0],secondarg);
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);
            setpgid(0, 0);
            // printf("%s  %s\n ",topass[0],topass[1]);
            int ret = execvp(topass[0], topass);
            if (ret != 0)
            {
                perror("No such command exists\n");
            }
        }
        else
        {
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(STDIN_FILENO, val);
            waitpid(val, &sometemp, WUNTRACED);
            tcsetpgrp(STDIN_FILENO, getpgrp());
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            if (WIFSTOPPED(sometemp))
            {
                // printf("here\n");
                jobsarr[jobscount].index = jobscount + 1;
                jobsarr[jobscount].pid = val;
                char somemy[10000];
                strcpy(somemy, topass[0]);
                if (topass[1] != NULL)
                {
                    strcat(somemy, " ");
                    strcat(somemy, topass[1]);
                }
                strcpy(jobsarr[jobscount].process, somemy);
                jobsarr[jobscount].isrunning = -100;
                jobscount++;
            }
            time_t end = time(NULL);
            // printf("Time takens is %ld\n", end - start);
            char some[10000];
            sprintf(some, "took %ld seconds", end - start);
            display_prompt(some);
            printf("\n");
        }
    }
}

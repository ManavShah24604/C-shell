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

#include "header.h"
// int valueofpid[1000], value[1000];
// char nameofprocess[2000][2000];
pid_t originalpid;
void funcforpid()
{
    int sometemp, pidnumber = waitpid(-1, &sometemp, WNOHANG);
    if (pidnumber > 0)
    {
        int it = 0;
        while (it < 500 && processpid[it] != pidnumber)
        {
            it++;
        }
        if (it >= 500)
            return;
        if (WIFSTOPPED(sometemp))
        {
            // printf("here\n");
            return;
        }
        fprintf(stderr, "Process %s with PID number %d executed ", processname[it], processpid[it]);
        if(WIFEXITED(sometemp))
        {
            printf("normally\n");
        }
        else
        printf("abmormally\n");
        for (int i = 0; i < jobscount; i++)
        {
            if (pidnumber == jobsarr[i].pid)
            {
                jobsarr[i].isrunning=0;
                break;
            }
        }
        // printf("\n");
        processpid[it] = 0;
        processname[it][0] = '\0';
    }
}
void ctrlc()
{
    pid_t temp = getpid();
    while (temp != originalpid)
    {
        if (temp < 0)
        {
            perror("something wrong\n");
        }
        kill(temp, SIGINT);
        temp = getpid();
    }
    // display_prompt();
}
int flag = 0;
void ctrlz()
{
    pid_t temp = getpid();
    // printf("sdlfjl\n");
    flag = 0;
    if (temp != originalpid)
    {
        flag = 1;
        if (temp < 0)
        {
            perror("something wrong\n");
        }
        char *some[3];
        some[0] = "bg";
        execvp(some[0], some);
    }
    else
    {
        int sometemp, pidnumber = waitpid(-1, &sometemp, WNOHANG);
        // printf("hi   i\n");
        int it = 0;
        while (it < 500 && processpid[it] != pidnumber)
        {
            it++;
        }
        if (it >= 500)
            return;
        if (WIFSTOPPED(sometemp))
            return;
        fprintf(stderr, "Process with PID number %d removed successfully\n", temp);
        // printf("\n");
        processpid[it] = 0;
        // processname[it][0] = '\0';
        // printf("some\n");
        return;
    }
}

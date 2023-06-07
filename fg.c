#include "header.h"

void my_fg(int parameter)
{
    if (parameter > jobscount)
    {
        printf("No such job exists\n");
        return;
    }
    int flag = 0;
    for (int i = 0; i < jobscount; i++)
    {
        if (jobsarr[i].isrunning==-100 || jobsarr[i].isrunning==1)
        {
            if (parameter == jobsarr[i].index)
            {
                flag = 1;
            }
        }
    }
    if (flag == 0)
    {
        printf("No such job exists\n");
        return;
    }
    for (int i = 0; i < jobscount; i++)
    {
        if (jobsarr[i].isrunning==-100 || jobsarr[i].isrunning==1)
        {
            if (parameter == jobsarr[i].index)
            {
                signal(SIGTTIN, SIG_IGN);
                signal(SIGTTOU, SIG_IGN);
                tcsetpgrp(STDIN_FILENO, jobsarr[i].pid);
                kill(jobsarr[i].pid, SIGCONT);
                int it = 0, pidnumber = jobsarr[i].pid;
                // printf("here\n");
                while (it < 500 && processpid[it] != pidnumber)
                {
                    it++;
                }
                if (it < 500)
                {
                    processpid[it] = 0;
                    processname[it] = '\0';
                }
                jobsarr[i].isrunning = 0;
                int sometemp;
                waitpid(pidnumber, &sometemp, WUNTRACED);
                tcsetpgrp(STDIN_FILENO, getpgrp());
                signal(SIGTTIN, SIG_DFL);
                signal(SIGTTOU, SIG_DFL);
                return;
            }
        }
    }
    // printf("No such job exists \n");
}

void my_bg(int parameter)
{
    if (parameter > jobscount)
    {
        printf("No such job exists\n");
        return;
    }
    int flag = 0;
    for (int i = 0; i < jobscount; i++)
    {
        if (jobsarr[i].isrunning == -100)
        {
            if (parameter == jobsarr[i].index)
            {
                flag = 1;
            }
        }
    }
    if (flag == 0)
    {
        printf("No such job exists\n");
        return;
    }
    for (int i = 0; i < jobscount; i++)
    {
        if (jobsarr[i].isrunning == -100)
        {
            if (parameter == jobsarr[i].index)
            {
                // printf("%d\n",jobsarr[i].pid);
                kill(jobsarr[i].pid, SIGTTIN);
                kill(jobsarr[i].pid, SIGCONT);
                jobsarr[i].isrunning=-1;
                char temp[10000];
                memset(temp,'\0',sizeof(temp));
                strcpy(temp,jobsarr[i].process);
                strcat(temp," & ");
                bg_fg(temp);

                // bg_fg(jobsarr[i].process);
                // return;
            }
        }
    }
}
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
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

void jobs(int flagforjob)
{
    for (int i = 0; i < jobscount; i++)
    {
        for (int j = 0; j < jobscount - 1; j++)
        {
            if (strcmp(jobsarr[j].process, jobsarr[j + 1].process) > 0)
            {
                if (jobsarr[j + 1].index != 0 && jobsarr[j].index != 0)
                {
                    my_jobs temp = jobsarr[j];
                    jobsarr[j] = jobsarr[j + 1];
                    jobsarr[j + 1] = temp;
                    // my_jobs temp;
                    // temp.index = jobsarr[i].index;
                    // temp.pid = jobsarr[i].pid;
                    // strcpy(temp.process, jobsarr[i].process);
                    // jobsarr[i].index = jobsarr[j].index;
                    // jobsarr[i].pid = jobsarr[j].pid;
                    // strcpy(jobsarr[i].process, jobsarr[j].process);
                    // jobsarr[j].index = temp.index;
                    // jobsarr[j].pid = temp.pid;
                    // strcpy(jobsarr[j].process, temp.process);
                }
            }
        }
    }
    for (int i = 0; i < jobscount; i++)
    {
        if (flagforjob == 0)
        {
            if (jobsarr[i].isrunning == 1)
                printf("[%d] Running %s & %d \n", jobsarr[i].index, jobsarr[i].process, jobsarr[i].pid);
            else if(jobsarr[i].isrunning==-100)
                printf("[%d] Stopped %s & [%d] \n", jobsarr[i].index, jobsarr[i].process, jobsarr[i].pid);
        }
        else if (flagforjob == 1)
        {
            if (jobsarr[i].isrunning == 1)
                printf("[%d] Running %s & [%d] \n", jobsarr[i].index, jobsarr[i].process, jobsarr[i].pid);
        }
        else
        {
            if (jobsarr[i].isrunning == -100)
            {
                printf("[%d] Stopped %s & [%d] \n", jobsarr[i].index, jobsarr[i].process, jobsarr[i].pid);
            }
        }
    }
}

#include"header.h"


void sig(int num, int parameter)
{
    for(int i=0;i<jobscount;i++)    
    {
        if(jobsarr[i].isrunning==1)
        {
            if(jobsarr[i].index == num)
            {
                kill(jobsarr[i].pid,parameter);
                return ;
            }
        }
    }
    perror("No such process is present\n");
    return ;
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"
int valueofpid[1000], value[1000];
char nameofprocess[2000][2000];
void funcforpid()
{
    int sometemp,pidnumber = waitpid(-1,&sometemp,WNOHANG);
    for(int it=0;it<256;it++)
    {
        if(valueofpid[it]==pidnumber && value[it]==1)
        {
            printf("Process %s of PID no. %d executed \n",nameofprocess[it],pidnumber);
            value[it]=0;
            break;
        }
    }

}
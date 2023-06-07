#ifndef header
#define header
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
void display_prompt();
void funcofcd();
void pwd();
void echo();
void discover();
void ls();
void pinfo();
void funcforpid();
void bg_fg(char input[]);
char *processname[1000];
int processpid[1000];
void func();
void ctrlc();
void ctrlz();
void jobs();
void mai();
void bg_fg2();  
void my_fg();
void my_bg();
void input_output();
void pipes();
void sig(int num, int parameter);
typedef struct my_job {
    int index,pid,isrunning;
    char process[10000];
}my_jobs;

my_jobs jobsarr[10000];
int jobscount;
#endif
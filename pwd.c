#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>

void pwd()
{
    char ansofpwd[10000];
    getcwd(ansofpwd,sizeof(ansofpwd));
    printf("%s\n",ansofpwd);
}
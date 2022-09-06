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

void bg_fg(char input[])
{
    int flag = 0;
    for (int i = strlen(input) - 1; i >= 0; i--)
    {
        if (input[i] == ' ' || input[i] == '\n')
            continue;
        else if (input[i] == '&')
        {
            flag = 1;
        }
        else
            break;
    }

    if (flag == 0) // foreground process
    {
        int i = 0;
        char *secondarg[10000],*some;
        secondarg[i]=strtok(input," ""\t");
        while (secondarg[i] != 0 && secondarg[i] != NULL) 
        {
            // printf("here\n");
            i++;
            secondarg[i] = strtok(NULL, " "
                                        "\t");
        }
        printf("%s\n", secondarg[0]);
        int val = fork();
        if (val == -1)
        {
            perror("Cannot create child process\n");
        }
        else if (val == 0)
        {
            int ret = execvp(secondarg[0], secondarg);
            if (ret != 0)
            {
                perror("No such command exists\n");
            }
        }
        else
            wait(NULL);
    }
    else
    {
        
    }
}



void b_g(1)
{
    
}
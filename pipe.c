#include "header.h"

void pipes(char input[])
{
    // printf("%s\n",input);
    char *data[1000];
    memset(data, '\0', sizeof(data));
    data[0] = strtok(input, "|");
    int i = 0;
    while (data[i] != NULL)
    {
        i++;
        data[i] = strtok(NULL, "|");
    }
    int store = i;
    data[store + 1] = NULL;
    int tempvar;
    int parr[2];
    for (i = 0; i < store; i++)
    {
        pipe(parr);
        pid_t val = fork();
        if (val == 0)
        {
            dup2(tempvar, STDIN_FILENO);
            if (data[i + 1] != NULL)
            {
                dup2(parr[1], STDOUT_FILENO);
            }
            close(parr[0]);
            char tempchar[10000];
            memset(tempchar,'\0',sizeof(tempchar));
            // int one = dup(0);
            // int second = dup(1);
            mai(data[i]);
            dup2(0, STDIN_FILENO);
            dup2(0, STDOUT_FILENO);
            exit(0);
        }
        else if (val > 0)
        {
            wait(NULL);
            close(parr[1]);
            tempvar = parr[0];
        }
        else
        {
            perror("Process cannot be genrated \n");
        }
    }
}
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
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
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

void input_output(char *input)
{
    // printf("%s\n", input);
    char tempinp[10000];
    // strcpy(tempinp,input);
    memset(tempinp, '\0', sizeof(tempinp));
    int ptr = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] != ' ')
        {
            ptr = i;
            break;
            // continue;
        }
    }
    for (int i = ptr; i < strlen(input); i++)
    {
        tempinp[i - ptr] = input[i];
    }
    // strcpy(input,tempinp);
    // strcat(input," ");
    int flag1 = 0, flag2 = 0, flag3 = 0;
    if (strstr(input, ">") != NULL)
    {
        // printf("er\n");
        flag1 = 1;
    }
    if (strstr(input, ">>") != NULL)
    {
        flag3 = 1;
        flag1 = 0;
    }
    if (strstr(input, "<") != NULL)
    {
        flag2 = 1;
    }
    if (flag1 > 0 || flag3 > 0)
    {
        if (flag2 == 1)
        {
            char *first, *second;
            if (flag1 == 1)
            {
                first = strtok(input, ">");
                // printf("%s\n",first);
                second = strtok(NULL, ">");
            }
            else
            {
                first = strtok(input, ">>");
                second = strtok(NULL, ">>");
            }
            // printf("%s\n",second);
            char tempfirst[10000];
            // memset(tempfirst,'\0',sizeof(tempfirst));
            int store2 = 0;
            for (int it = 0; it < strlen(second); it++)
            {
                if (second[it] != ' ')
                {
                    store2 = it;
                    break;
                }
            }
            for (int it2 = store2; it2 < strlen(second); it2++)
            {
                tempfirst[it2 - store2] = second[it2];
            }
            char tempsecond[10000];
            memset(tempsecond, '\0', sizeof(tempsecond));
            store2 = 0;
            for (int it = 0; it < strlen(tempfirst); it++)
            {
                if (tempfirst[it] != ' ')
                {
                    store2 = it;
                }
            }
            for (int it = 0; it <= store2; it++)
            {
                tempsecond[it] = tempfirst[it];
            }
            int fd1;
            if (flag1 == 1)
            {
                fd1 = open(tempsecond, O_WRONLY | O_TRUNC, 0644);
                if (fd1 == -1)
                {
                    fd1 = open(tempsecond, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }
            }
            else
            {
                fd1 = open(tempsecond, O_WRONLY | O_APPEND, 0644);
            }
            // printf("first is %s\n",first);
            char *first2 = strtok(first, "<");
            char *second2 = strtok(NULL, "<");
            char some[1000];
            memset(some, '\0', sizeof(some));
            int i = 0;
            while (second2[i] == ' ')
                i++;
            for (int j = i; j < strlen(second2); j++)
            {
                some[j - i] = second2[j];
            }
            int file_descriptor = open(some, O_WRONLY, 0644);
            // printf("%s\n",some);
            dup2(file_descriptor, STDIN_FILENO);
            // printf("first is %s  second is %s for oritinal is %d\n", first2, some, file_descriptor);
            char new[1000];
            memset(new, '\0', sizeof(new));
            strcpy(new, first2);
            strcat(new, some);
            dup2(fd1, STDOUT_FILENO);
            bg_fg2(new);
            dup2(0, STDOUT_FILENO);
            dup2(0, STDIN_FILENO);
        }
        else
        {
            char *first, *second;
            if (flag1 == 1)
            {
                first = strtok(input, ">");
                second = strtok(NULL, ">");
                // printf("%s  %s \n", first, second);
            }
            else
            {
                first = strtok(input, ">>");
                second = strtok(NULL, ">>");
            }
            char s2[10100];
            memset(s2, '\0', sizeof(s2));
            int i = 0;
            while (second[i] == ' ')
            {
                i++;
            }
            int j = i;
            for (j = i; j < strlen(second); j++)
            {
                if (second[j] == ' ')
                    break;
                s2[j - i] = second[j];
            }
            int fd1;
            if (flag1 == 1)
            {
                fd1 = open(s2, O_WRONLY | O_TRUNC, 0644);
                if (fd1 == -1)
                {
                    fd1 = open(s2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }
            }
            else
            {
                fd1 = open(s2, O_WRONLY | O_APPEND, 0644);
            }
            // memset(tempfirst,'\0',sizeof(tempfirst));
            char tempfirst[10000];
            // memset(tempfirst,'\0',sizeof(tempfirst));
            int store2 = 0;
            for (int it = 0; it < strlen(first); it++)
            {
                if (first[it] != ' ')
                {
                    store2 = it;
                    break;
                }
            }
            for (int it2 = store2; it2 < strlen(first); it2++)
            {
                tempfirst[it2 - store2] = first[it2];
            }
            char tempsecond[10000];
            memset(tempsecond, '\0', sizeof(tempsecond));
            store2 = 0;
            for (int it = 0; it < strlen(tempfirst); it++)
            {
                if (tempfirst[it] != ' ')
                {
                    store2 = it;
                }
            }
            for (int it = 0; it <= store2; it++)
            {
                tempsecond[it] = tempfirst[it];
            }
            // printf("%s\n", tempsecond);
            dup2(fd1, STDOUT_FILENO);
            bg_fg2(tempsecond);
            dup2(0, STDOUT_FILENO);
            dup2(0, STDOUT_FILENO);
        }
    }
    else if (flag2 == 1)
    {
        char *first = strtok(input, "<");
        char *second = strtok(NULL, "<");
        int i = 0;
        while (second[i] == ' ')
            i++;
        char some[10000];
        memset(some, '\0', sizeof(some));
        for (int j = i; j < strlen(second); j++)
        {
            some[j - i] = second[j];
        }
        int file_descriptor = open(some, O_WRONLY, 0644);
        dup2(file_descriptor, STDIN_FILENO);
        char new[1000];
        memset(new, '\0', sizeof(new));
        strcpy(new, first);
        strcat(new, " ");
        strcat(new, second);
        bg_fg2(new);
        dup2(0, STDIN_FILENO);
        // printf("hewrjwlje %s dsdsvsd %s\n", first, second);
    }
    else
    {
        bg_fg2(input);
    }
}
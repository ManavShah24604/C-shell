#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"
#define NEG -10000000
extern char root[2560];
char history2[100][500];
int main()
{
    getcwd(root, sizeof(root));
    int some = 0;
    int frontofhistory = 0, lastofhistory = -1;
    char temphistory[10000];
    temphistory[0] = '\0';
    strcpy(temphistory, root);
    strcat(temphistory, "/");
    strcat(temphistory, "history.txt");

    // if(fhistory==NULL) printf("error\n");
    printf("%s\n", temphistory);
    while (1)
    {

        // printf("here\n");
        display_prompt();
        //  printf("here\n");
        char str[100010];
        char *input;
        size_t buff = 100000;
        input = (char *)malloc(buff);

        some = 1;
        getline(&input, &buff, stdin);
        if (strlen(input) == 1)
            continue;
        input[strlen(input) - 1] = '\0';
        strcpy(str, input);
        if (strlen(str) == 0)
        {
            printf("here\n");
            continue;
        }
        else
        {
            FILE *fhistory;
            int count = 0;
            char *file_contents = malloc(10000);
            fhistory = fopen(temphistory, "r");
            while (fscanf(fhistory, "%[^\n] ", file_contents) != EOF)
            {
                strcpy(history2[count], file_contents);
                count++;
            }
            int it = 0;
            fclose(fhistory);
            if (strcmp(input, history2[count - 1]) == 0)
                goto here;

            if (count >= 19)
            {
                fhistory = fopen(temphistory, "w");
                for (it = 1; it <= 19; it++)
                {
                    fprintf(fhistory, "%s\n", history2[it]);
                }
            }
            else
            {
                fhistory = fopen(temphistory, "w");
                for (it = 0; it < count; it++)
                {
                    fprintf(fhistory, "%s\n", history2[it]);
                }
            }
            fprintf(fhistory, "%s\n", input);
            fclose(fhistory);
        here:;
            char *substr;
            char *storestrings[1000];
            int noofcommands = 0;
            storestrings[0] = strtok(str, ";");
            // printf("%s\n", storestrings[0]);
            while (storestrings[noofcommands] != 0 && storestrings[noofcommands] != NULL)
            {
                // printf("%s\n", substr);
                noofcommands++;
                storestrings[noofcommands] = strtok(NULL, ";");
                // printf("%s\n", storestrings[noofcommands]);
            }
            int i = 0;
            while (noofcommands--)
            {
                char *first;
                first = strtok(storestrings[i], " "
                                                "\t");
                i++;
                if (first == 0)
                {
                    break;
                }
                if (strcmp(first, "cd") == 0)
                {
                    funcofcd();
                }
                else if (strcmp(first, "pwd") == 0)
                {
                    pwd();
                    // char ansofpwd[10000];
                    // getcwd(ansofpwd, sizeof(ansofpwd));
                    // printf("%s\n", ansofpwd);
                }
                else if (strcmp(first, "echo") == 0)
                {
                    echo();
                }
                else if (strcmp(first, "ls") == 0)
                {
                    ls();
                }
                else if (strcmp(first, "pinfo") == 0)
                {
                    char *second = strtok(NULL, " "
                                                "\t");
                    if (second == 0)
                    {
                        pinfo(NEG);
                    }
                    else
                    {
                        int len = strlen(second);
                        int num = 0, pow = 1;
                        for (int iterator = len - 1; iterator >= 0; iterator--)
                        {
                            num += (second[iterator] - '0') * pow;
                            pow *= 10;
                        }
                        printf("%d\n",num);
                        pinfo(num);
                    }
                }
                else if ((strcmp(first, "history")) == 0)
                {
                    // history();
                    FILE *fhistory;
                    int count = 0;
                    char *file_contents = malloc(10000);
                    fhistory = fopen(temphistory, "r");
                    while (fscanf(fhistory, "%[^\n] ", file_contents) != EOF)
                    {
                        // strcpy(history2[count], file_contents);
                        if (count > 10)
                            break;
                        printf("%s\n", file_contents);
                        count++;
                    }
                    int it = 0;
                    fclose(fhistory);
                }
                else
                {
                    printf("No such command exists\n");
                }

                substr = strtok(str, ";");
            }
        }
    }
    // fputs("hello  ", fhistory);

    return 0;
}
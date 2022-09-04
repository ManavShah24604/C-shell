#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

void addtohistory(char input[])
{
    char history2[1000][500];
    char root[2560];
    int some = 0;
    char temphistory[10000];
    temphistory[0] = '\0';
    strcpy(temphistory, root);
    strcat(temphistory, "/");
    strcat(temphistory, "history.txt");
    FILE *fhistory;
    int count = 0;
    char *file_contents = malloc(10000);
    fhistory = fopen(temphistory, "r");
    while (fscanf(fhistory, "%[^\n] ", file_contents) != EOF)
    {
        printf("%s\n", input);
        strcpy(history2[count], file_contents);
        count++;
        // printf("> %s\n", file_contents);
    }
    int it = 0;
    fclose(fhistory);
    if (strcmp(input, history2[count - 1]) == 0)
        return;

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
}
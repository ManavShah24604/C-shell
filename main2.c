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

void die(const char *s)
{
    // perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
 */
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

/**
 * stdout and stdin are buffered we disable buffering on that
 * After entering in raw mode we read characters one by one
 * Up arrow keys and down arrow keys are represented by 3 byte escape codes
 * starting with ascii number 27 i.e. ESC key
 * This way we interpret arrow keys
 * Tabs are usually handled by the term, but here we are simulating tabs for the sake of simplicity
 * Backspace move the cursor one control character to the left
 * @return
 */
extern char root[2560], namesofprocess[2000][2000];
extern int valueofpid[1000], value[1000];
char history2[100][500];
extern int flagforc;
extern pid_t originalpid;

void ctrlforz()
{
}
int main()
{
    char *inp = malloc(sizeof(char) * 100);
    jobscount = 0;
    originalpid = getpid();
    getcwd(root, sizeof(root));
    int some = 0;
    int frontofhistory = 0, lastofhistory = -1;
    char temphistory[10000];
    temphistory[0] = '\0';
    strcpy(temphistory, root);
    strcat(temphistory, "/");
    strcat(temphistory, "history.txt");
    char c;
    while (1)
    {

        setbuf(stdout, NULL);
        enableRawMode();
        // printf("Prompt>");
        display_prompt();
        memset(inp, '\0', 100);
        int pt = 0;
        // printf("%s\n", inp);
        signal(SIGCHLD, funcforpid);
        signal(SIGINT, ctrlc);
        signal(SIGTSTP, ctrlforz);
        while (read(STDIN_FILENO, &c, 1) == 1)
        {

            if (iscntrl(c))
            {
                if (c == 10)
                    break;
                else if (c == 27)
                {
                    char buf[3];
                    buf[2] = 0;
                    if (read(STDIN_FILENO, buf, 2) == 2)
                    { // length of escape code
                        printf("\rarrow key: %s", buf);
                    }
                }
                else if (c == 127)
                { // backspace
                    if (pt > 0)
                    {
                        if (inp[pt - 1] == 9)
                        {
                            for (int i = 0; i < 7; i++)
                            {
                                printf("\b");
                            }
                        }
                        inp[--pt] = '\0';
                        printf("\b \b");
                    }
                }
                else if (c == 9)
                { // TAB character
                    char matches[1010][1000];
                    int mode[10000];
                    memset(matches, '\0', sizeof(matches));
                    int count = 0;
                    DIR *ls_dir;
                    struct dirent *ls_struct;
                    int i = 0;
                    ls_dir = opendir(".");
                    ls_struct = readdir(ls_dir);
                    int j = 0, len = 0, storelen = 0;
                    while (ls_struct != NULL)
                    {
                        struct stat somefile, newfile;
                        struct stat ss;
                        char tempcomplete[10100];
                        tempcomplete[0] = '\0';
                        getcwd(tempcomplete, sizeof(tempcomplete));
                        strcat(tempcomplete, "/");
                        strcat(tempcomplete, ls_struct->d_name);
                        stat(tempcomplete, &ss);
                        stat(tempcomplete, &somefile);
                        // printf("ishere \n");
                        char temp[100010];
                        temp[0] = '\0';
                        strcpy(temp, ls_struct->d_name);
                        int flag = 0;
                        char compare[10000];
                        memset(compare, '\0', sizeof(compare));
                        // printf("%s\n",temp);
                        // printf("\n%s\n",inp);
                        j = 0, len = 0;
                        for (i = 0; i < pt; i++)
                        {
                            if (inp[i] == ' ')
                            {
                                j = 0;
                                len = 0;
                                continue;
                            }
                            else
                            {
                                compare[j] = inp[i];
                                j++;
                                len++;
                                storelen = len;
                            }
                        }
                        for (i = 0; i < len; i++)
                        {
                            // printf("%c ", compare[i]);
                            if (temp[i] != compare[i])
                            {
                                flag = 1;
                                break;
                            }
                        }
                        if (flag == 0)
                        {
                            if (ss.st_mode & S_ISDIR(ss.st_mode))
                                mode[count] = 0;
                            else
                                mode[count] = 1;
                            strcpy(matches[count], temp);
                            count++;
                        }
                        ls_struct = readdir(ls_dir);
                    }
                    if (count > 1)
                    {
                        int len = 1e9;
                        for (i = 0; i < count; i++)
                        {
                            printf("\n%s", matches[i]);
                            if (len <= strlen(matches[i]))
                                len = strlen(matches[i]);
                        }
                        printf("\n");
                        int store = 0;
                        for (i = strlen(inp) - 1; i >= 0; i--)
                        {
                            if (inp[i] == ' ')
                            {
                                store = i;
                                break;
                            }
                        }
                        char temp[10000];
                        memset(temp, '\0', sizeof(temp));
                        for (i = 0; i <= store; i++)
                        {
                            temp[i] = inp[i];
                        }
                        int some = i;
                        display_prompt(NULL);
                        for (int it = 0; it < len; it++)
                        {
                            char temp2 = matches[0][it];
                            int flag2 = 1;
                            for (i = 0; i < count; i++)
                            {
                                if (temp2 != matches[i][it])
                                {
                                    flag2 = 0;
                                    break;
                                }
                            }
                            if (flag2 == 1)
                            {
                                temp[some] = temp2;
                                some++;
                            }
                            else
                                break;
                            // printf("%c",temp);
                        }
                        // printf("here\n");
                        printf("%s", temp);
                        strcpy(inp, temp);
                        // printf("\t%s\t",inp);
                        // break;
                    }
                    else
                    {
                        if (mode[0] == 0)
                        {
                            for (i = storelen; i < strlen(matches[0]); i++)
                            {
                                inp[pt++] = matches[0][i];
                                printf("%c", matches[0][i]);
                            }
                            inp[pt++] = '/';
                            printf("/");
                        }
                        else
                        {
                            for (i = storelen; i < strlen(matches[0]); i++)
                            {
                                inp[pt++] = matches[0][i];
                                printf("%c", matches[0][i]);
                            }
                            inp[pt++] = ' ';
                            printf(" ");
                        }
                    }

                    // inp[pt++] = c;
                    // for (int i = 0; i < 8; i++)
                    // { // TABS should be 8 spaces
                    //     printf(" ");
                    // }
                }
                else if (c == 4)
                {
                    exit(0);
                }
                else
                {
                    printf("%d\n", c);
                }
            }
            else
            {
                inp[pt++] = c;
                printf("%c", c);
            }
        }
        disableRawMode();

        // printf("\nInput Read: [%s]\n", inp);
        printf("\n");
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
        if (strcmp(inp, history2[count - 1]) == 0)
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
        fprintf(fhistory, "%s\n", inp);
        fclose(fhistory);
    here:;
        strcat(inp, " ");
        // printf("%s\n",inp);
        mai(inp);
    }
    return 0;
}
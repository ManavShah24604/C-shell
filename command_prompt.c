#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define MAGENTA "\x1b[35m"

#include <pwd.h>
#include <sys/types.h>
struct utsname system_name;
char root[25600];
void display_prompt(char some[])
{
    char current[256000];
    getcwd(current, sizeof(current));
    // printf("%s\n", current);
    char *username;
    struct passwd *p;
    username = (char *)malloc(10000);
    p = getpwuid(getuid());
    username = p->pw_name;
    uname(&system_name);
    char ans[100010];
    ans[0] = '\0';
    printf(RED "<");
    int lenofroot = strlen(root);
    int lenofcurrent = strlen(current);
    if (lenofcurrent < lenofroot)
    {
        strcat(ans, username);
        strcat(ans, "@");
        strcat(ans, system_name.nodename);
        strcat(ans, ":");
        printf(GREEN "%s" BLUE "%s" RESET, ans, current);
        // strcat(ans, current);
    }
    else
    {
        int flag = 1;

        for (int i = 0; i < lenofroot; i++)
        {
            if (root[i] != current[i])
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            strcat(ans, username);
            strcat(ans, "@");
            strcat(ans, system_name.nodename);
            printf(GREEN "%s", ans);
            // strcat(ans, ":~");
            char tempstr[100010];
            tempstr[0] = '\0';
            for (int i = lenofroot; i < lenofcurrent; i++)
            {
                tempstr[i - lenofroot] = current[i];
            }
            tempstr[lenofcurrent - lenofroot] = '\0';
            char tempans[10100];
            tempans[0] = '\0';
            strcat(tempans, ":~");
            strcat(tempans, tempstr);
            printf(BLUE "%s" RESET, tempans);
            // strcat(ans, tempstr);
        }
        else
        {
            strcat(ans, username);
            strcat(ans, "@");
            strcat(ans, system_name.nodename);
            strcat(ans, ":");
            printf(GREEN "%s", ans);
            printf(BLUE "%s", current);
            // strcat(ans, current);
        }
    }
    // strcat(ans, ">");
    if (some != NULL)
        printf(MAGENTA "%s" RESET, some);
    printf(RED ">" RESET);
    return;
}
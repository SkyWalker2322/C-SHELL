#include "./prompt/prompt.h"
#include "./chdir/chdir.h"
#include "./echo/echo.h"
#include "./pinfo/pinfo.h"
#include "./ls/ls.h"
#include "./bfg/bfg.h"
#include "headers.h"

void free_char_arry(char *a, long long int len)
{
    for (long long int i = 0; i < len; i++)
        a[i] = '\0';
}
void command_execute(char cmdline[]);

int main()
{
    char input[10001];
    free_char_arry(input, 10001);
    free_char_arry(shelldir, 10001);
    getcwd(shelldir, 10001);
    shelldirlen = strlen(shelldir);

    while (1)
    {
        prompt(shelldir);

        char commandline[10][1000];
        int count = 0;
        for (int i = 0; i < 10; i++)
            free_char_arry(commandline[i], 1000);

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        char *token = strtok(input, ";\n");
        while (token != NULL)
        {
            strcpy(commandline[count], token);
            //printf("%s\n", commandline[count]);
            token = strtok(NULL, ";\n");
            count++;
        }
        for (int i = 0; i < count; i++)
        {
            command_execute(commandline[i]);
        }
    }
}

void command_execute(char cmdline[])
{
    char args[100][100], *cmd;
    for (int i = 0; i < 100; i++)
        free_char_arry(args[i], 100);

    char cpcmdline[1000];
    char rpcmdline[1000];
    free_char_arry(rpcmdline, 1000);
    strcpy(cpcmdline, cmdline);
    int count = 0;
    char *token = strtok(cpcmdline, " \n\t\r");
    cmd = token;
    token = strtok(NULL, " \n\t\r");
    while (token != NULL)
    {
        strcpy(args[count], token);
        //printf("%s\n",cmd[count]);
        token = strtok(NULL, " \n\t\r");
        count++;
    }
    //printf("\n");
    int its_bg = 0, j = 0;
    int rn,b=1;
    while (strlen(args[j]) > 0)
    {
        if (args[j][0] == '&')
        {
            its_bg = 1;
            break;
        }
        j++;
    }
    j = 0;
    //printf("%ld\n",strlen(args[0]));
    if (strcmp(cmd, "cd") == 0)
    {
        change_dir(args[0]);
    }
    else if (strcmp(cmd, "pwd") == 0)
    {
        char pwdd[1000];
        free_char_arry(pwdd, 1000);
        getcwd(pwdd, 1000);
        printf("%s\n", pwdd);
    }
    else if (strcmp(cmd, "echo") == 0)
    {
        exec_echo(args);
    }
    else if (strcmp(cmd, "ls") == 0)
    {
        int a = 0, l = 0;
        char argx[100];
        free_char_arry(argx, 100);
        j = 0;
        while (strlen(args[j]) > 0)
        {
            if (strcmp(args[j], "-l") == 0)
                l = 1;
            if (strcmp(args[j], "-a") == 0)
                a = 1;
            if (strcmp(args[j], "-la") == 0 || strcmp(args[j], "-al") == 0)
                {
                    a = 1;
                    l = 1;
                }
            j++;
        }
        j=0;
        int fg = 0;
		while (j < 10)
		{
			if (strlen(args[j]) > 0 && args[j][0] != '-')
			{
				printf("%s:\n", args[j]);
				exec_ls(args[j], l, a);
				fg = 1;
			}
			j++;
		}
		if (fg == 0)
		{
			exec_ls(args[3], l, a);
		}

    }
    else if (strcmp(cmd, "pinfo") == 0)
    {
        exec_pinfo(args[0]);
    }
    else if (strcmp(cmd, "repeat")==0)
    {
        int rn = strlen(args[0]);
        for(int l=0;l<990;l++)
        {
            rpcmdline[l] = cmdline[8+rn+l];
        }
        //printf("%s",rpcmdline);
        int rnvalue = atoi(args[0]);
        for(int l=0;l<rnvalue;l++)
        {
            command_execute(rpcmdline);
        }
    }
    else
    {
        exec_bfgcommands(cmd, cmdline, its_bg);
    }
}
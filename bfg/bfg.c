#include "bfg.h"
#include "../headers.h"
#include "../prompt/prompt.h"
int value=0;
char cpcmd[100];
void bfg_run(int sig)
{
    pid_t pid;
    pid = wait(NULL);
    if (value == 1)
    {
        printf("\n%s with pid %d exited normally\n", cpcmd, pid);
        prompt(shelldir);
        fflush(stdout);
        
    }
    value = 0;
}
void exec_bfgcommands(char cmd[], char cmdline[], int its_bg)
{
    int p, q, n, l;
    value=1;
    strcpy(cpcmd,cmd);
    char *argx[100];
    int count = 0;
    char *token = strtok(cmdline, " ");
    while (token != NULL)
    {
        argx[count] = token;
        token = strtok(NULL, " ");
        count++;
    }
    
    p = fork();
    if (its_bg == 0)
    {
        
        if (p == 0)
        {
            execvp(cmd, argx);
        }
        else
        {
            wait(NULL);
        }
    }
    else if(its_bg==1){
        n=0;
        while(strlen(argx[n])>0)
        {
            if(argx[n][0]=='&')
            {
                argx[n][0] = '\0';
                break;
            }
            n++;
        }
        if (p==0)
        {
            printf("%d\n",getpid());
            if(execvp(cmd, argx) == -1)
            {
                perror("execvp");
                return ;
            }
            fflush(stdout);    
        }
        if(p>0)
        signal(SIGCHLD,bfg_run);   
    }
}
#include "pipe.h"
#include "../headers.h"
#include "../pinfo/pinfo.h"

void exec_pipe(char cmdline[])
{
    char args[10][100];
    for (int i = 0; i < 10; i++)
        free_char_arry(args[i], 100);
    int count = 0;
    char *token = strtok(cmdline, "|");
    while (token != NULL)
    {
        strcpy(args[count], token);
        token = strtok(NULL, "|");
        count++;
    }

    int in_fd,out_fd;
	in_fd=dup(0);
	out_fd=dup(1);
    int fildes[2];
    int proc,fd=0,i=0,status;

    while(strlen(args[i])!=0)
    {
        if(pipe(fildes)<0)
        {
            perror("Couldn't Create pipe");
            exit(1);
        }
        proc = fork();
        if(proc<0)
        {
            perror("Child proc");
            exit(1);
        }
        else if(proc==0)
        {
            dup2(fd, 0);
            if(strlen(args[i+1])!=0)
            {
                dup2(fildes[1],1);
            }
            close(fildes[0]);
            command_execute(args[i]);
            exit(1);
        }
        else{
            wait(NULL);
            close(fildes[1]);
			fd=fildes[0];
        }
        i++;
    }
}
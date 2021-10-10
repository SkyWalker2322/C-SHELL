#include "redirection.h"
#include "../headers.h"

int redirection_type(char str[])
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == '>' && str[i + 1] == '>')
            return 4;
        if (str[i] == '<')
        {
            for (int j = i + 1; j < strlen(str); j++)
            {
                if (str[j] == '>')
                    return 3;
            }
            return 2;
        }
        if (str[i] == '>')
            return 1;
    }
    return 0;
}

void redirections(char cmdline[])
{
    int type = redirection_type(cmdline);
    //printf("%d\n", type);
    if (type == 0)
    {
        return;
    }
    char *in_file;
    char *out_file;
    char *input[2];
    char *output[2];
    in_file = out_file = NULL;

    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    char *str1;
    str1 = cmdline;
    output[0] = strtok(str1, ">");
    output[1] = strtok(NULL, ">");
    //printf("%s~%s\n",output[0],output[1]);

    input[0] = strtok(output[0], "<");
    input[1] = strtok(NULL, "<");
    //printf("%s~%s\n",input[0],input[1]);

    in_file = strtok(input[1], " \n\t\r");
    out_file = strtok(output[1], " \n\t\r");
    //printf("%s~%s\n",in_file,out_file);

    char *argz[10];

    int count = 0;
    char *tokenz = strtok(cmdline, " \n\t\r");
    while (tokenz != NULL)
    {
        argz[count] = tokenz;
        //printf("%s\n",argz[count]);
        tokenz = strtok(NULL, " \n\t\r");
        count++;
    }

    int pid = fork();
    int status;
    if (pid < 0)
    {
        perror("Child");
        return;
    }
    else if (pid > 0)
    {
        while (wait(&status) != pid)
        {
        }
    }
    else
    {
        if (type == 1)
        {
            int fd_out;
            fd_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0)
            {
                perror("Output redirection");
                return;
            }
            dup2(fd_out, 1);
            close(fd_out);
        }
        else if (type == 2)
        {
            int fd_in = open(in_file, O_RDONLY);
            if (fd_in < 0)
            {
                perror("Input redirection");
                return;
            }
            dup2(fd_in, 0);
            close(fd_in);
        }
        else if (type == 3)
        {
            int fd_in, fd_out;
            fd_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0)
            {
                perror("Output redirection");
                return;
            }
            fd_in = open(in_file, O_RDONLY);
            if (fd_in < 0)
            {
                perror("Input redirection");
                return;
            }
            dup2(fd_in, 0);
            close(fd_in);
            dup2(fd_out, 1);
            close(fd_out);
        }
        else if (type == 4)
        {
            int fd_out;
            fd_out = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd_out < 0)
            {
                perror("Output redirection");
                return;
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        char cmd[20];
        strcpy(cmd,argz[0]);
        if(strcmp(cmd,"pinfo")==0)
        {
            exec_pinfo(argz[1]);
            dup2(saved_stdout,1);
        }
        else{
            int r = execvp(argz[0],argz);
		    if(r<0)
            {
			    dup2(saved_stdout,STDOUT_FILENO);
			    perror("Command not found");
			    exit(EXIT_FAILURE);
		    }
        }
        
    }
}

// echo "hello" > hello.txt
// sort < lines.txt > sort_lines.txt
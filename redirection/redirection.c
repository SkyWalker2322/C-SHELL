#include "redirection.h"
#include"../headers.h"

int redirection_type(char argz[][100]) 
{
    int j=0;
    for(int i=0;i<strlen(argz[j]);i++){
		if(strcmp(argz[j], ">>")==0)
			return 4;
		if(strcmp(argz[j], "<")==0 && strcmp(argz[j+2], ">")==0)
			return 3;
		if(strcmp(argz[j], '<')==0)
			return 2;
        if(strcmp(argz[j], ">")==0)
            return 1;
	}
	return 0;
}

void redirections(char cmdline[])
{
    char *in_file;
	char *out_file;
	char *input[2];
	char *output[2];
	in_file=out_file=NULL;

	int saved_stdout=dup(STDOUT_FILENO);
    char *str1;
	str1=cmdline;
	output[0]=strtok(str1,">");
	output[1]=strtok(NULL,">");

	input[0]=strtok(output[0],"<");
	input[1]=strtok(NULL,"<");


char argz[100][100], *cmdz;
    for (int i = 0; i < 100; i++)
        free_char_arry(argz[i], 100);

int count = 0;
    char *tokenz = strtok(cmdline, " \n\t\r");
    cmdz = tokenz;
    tokenz = strtok(NULL, " \n\t\r");
    while (tokenz != NULL)
    {
        strcpy(argz[count], tokenz);
        //printf("%s\n",cmd[count]);
        tokenz = strtok(NULL, " \n\t\r");
        count++;
    }
    int type = redirection_type(argz);
    int pid = fork();
    int status;
    if(pid<0)
    {
        perror("Child");
        return;
    }
    else if(pid>0)
    {
        while(wait(&status)!=pid){}
    }
    else{
        if(type==1)
    {
        int fd_out,stout;
            dup2(STDOUT_FILENO, stout);
			fd_out=open(out_file,O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd_out < 0){
				perror("Output redirection");
				return;
			}
			dup2(fd_out,STDOUT_FILENO);
            execvp(cmdz, argz);
			close(fd_out);
    }
    else if(type == 2)
    {

    }
    else if(type == 3)
    {

    }
    else if(type ==4)
    {

    }
    }
    
}
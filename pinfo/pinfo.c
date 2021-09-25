#include "pinfo.h"
#include "../headers.h"

void exec_pinfo(char args[])
{
    int pidint;
    char pid[10];
    free_char_arry(pid, 10);
    if (strlen(args) == 0)
    {
        pidint = getpid();
        //printf("%d\n",pidint);
        sprintf(pid, "%d", pidint);
    }
    else
    {
        strcpy(pid, args);
    }
    //printf("%ld\n",strlen(pid));
    char *arr = (char *)malloc(sizeof(char) * 100);
    sprintf(arr, "/proc/%s/stat", pid);
    FILE *file;
    char *exe=malloc(sizeof(char)*100);
    sprintf(exe, "/proc/%s/exe", pid);
    if(!(file=fopen(arr,"r")))
    {
        printf("process does not exists\n");
        return;
    }
    char tp[500];
    fscanf(file,"%[^\n]",tp);
    char prr[10][100];
	for(int i=0;i<10;i++)
		free_char_arry(prr[i],100);

    char *token1;
	token1=strtok(tp," ");
	for(int i=0;i<9;i++)
    {
		strcpy(prr[i],token1);
		token1=strtok(NULL," ");
	}
    printf("pid -- %s\n",prr[0]);
    if(strcmp(prr[4],prr[7])==0)
    printf("process status -- %s+\n",prr[2] );
    else
    printf("process status -- %s\n",prr[2] );
	printf("virtual mem -- %s\n",prr[8] );
    char exe_path[2050];
	int ret=readlink(exe,exe_path,1000);
	if(ret==-1){
		printf("no path for executable\n");
	}
	else{
		printf("executable path -- ~/%s\n",prr[1] );
	}
    free(arr);
    free(exe);
}
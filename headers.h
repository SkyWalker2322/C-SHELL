#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<dirent.h>
#include<time.h>
#include <pwd.h>
#include <assert.h>
#include <grp.h>
#include <math.h>
#include <signal.h>
#include<fcntl.h>          
#include<errno.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/utsname.h>

void free_char_arry(char* a,long long int len);
void command_execute(char cmdline[]);

char shelldir[10001];
int shelldirlen;
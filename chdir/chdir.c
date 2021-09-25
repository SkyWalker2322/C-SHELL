#include "chdir.h"
#include "../headers.h"

void change_dir(char path[])
{
    if( strlen(path)==0||path[0]=='~')
        chdir(getenv("HOME"));
    else {
        if(chdir(path))
        perror("cd");

        return;
    }

}

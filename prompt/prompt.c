#include "prompt.h"
#include "../headers.h"

void prompt(char shelldir[])
{
    char *hostname, systemname[200], shellname[10420];
    free_char_arry(shellname, 10420);
    free_char_arry(systemname, 200);
    hostname = (char *)malloc(200 * sizeof(char));
    hostname = getlogin();
    gethostname(systemname, 200);
    char curpdir[10001];
    free_char_arry(curpdir, 10001);
    getcwd(curpdir, 10001);

    int curdirlen = strlen(curpdir);
    char relativecurdir[shelldirlen + 1];
    for (int i = 0; i < shelldirlen; i++)
        relativecurdir[i] = curpdir[i];
    relativecurdir[shelldirlen] == '\0';
    //
       char remaincurdir[1001];
        free_char_arry(remaincurdir, curdirlen - shelldirlen + 1);
        for (int i = 0; i < curdirlen - shelldirlen; i++)
            remaincurdir[i] = curpdir[shelldirlen + i];
        remaincurdir[curdirlen - shelldirlen] == '\0';
    if (strcmp(shelldir,relativecurdir) == 0)
    {
        sprintf(shellname, "<%s@%s:~%s>", hostname, systemname, remaincurdir);
    }
    else
    {
        sprintf(shellname, "<%s@%s:%s>", hostname, systemname, curpdir);
    }
    printf("%s", shellname); 
}

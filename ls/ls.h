#ifndef __LISTDIR_H
#define __LISTDIR_H
#include "../headers.h"

void exec_ls(char s[],int l,int a);
typedef struct files_data
{
	char file_permissions[20];
	nlink_t file_nhlinks;
	char file_uown[1000];
	char file_gown[1000];
	off_t file_size;
	char file_mtime[100];
	char file_name[1000];
}file;
long long int i,j,p;

#endif

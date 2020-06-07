#ifndef __FILE_H__
#define __FILE_H__

#include "list.h"

typedef struct Directory {
	char *name;
	Dir_list *directories;
	File_list *files;
	struct Directory *parent_d;
} Directory;

typedef struct File {
	char *name;
	int size;
	char *data;
	Directory *dir;
} File;

#endif



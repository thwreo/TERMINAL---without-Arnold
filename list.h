#ifndef __LIST_H__
#define __LIST_H__

#include "file.h"


typedef struct Dir_list {
	struct Directory *a_dir;
	struct Dir_list *next; //next directory
} Dir_list;

typedef struct File_list {
	struct File *a_file;
	struct File_list *next; //next file
} File_list;

#endif

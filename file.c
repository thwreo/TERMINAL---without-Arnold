#ifndef __FILE_C__
#define __FILE_C__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "file.h"
#include "list.h"

Directory *create_fs(void)
{
	Directory *root_directory = (Directory *)malloc(sizeof(Directory));

	root_directory->parent_d = NULL;
	root_directory->name = "/";
	root_directory->directories = NULL;
	return root_directory;
}
void delete_fs(Directory *root_directory)
{
	root_directory->directories = NULL;
	root_directory->parent_d = NULL;
	root_directory->name = NULL;
	root_directory->files = NULL;
	free(root_directory);
	root_directory = NULL;
}

void pwd(Directory *dir)
{
	if (dir) {
		if (dir->parent_d == NULL || dir->parent_d->parent_d == NULL) {
			pwd(dir->parent_d);
			printf("%s", dir->name);
		} else {
			pwd(dir->parent_d);
			printf("/%s", dir->name);
		}
	}
}

#endif

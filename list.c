#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "file.h"
#include "list.h"

#include "file.c"

void tab(int count) //functie ce printeaza un nr dat de spatii (pt tree)
{
	int i;

	count = count*4;
	for (i = 1; i <= count; i++)
		printf(" ");
}

File_list *touch(char *filename, char *content, Directory *dir)
{
	File_list *head = (File_list *)malloc(sizeof(File_list));

	head = dir->files;

	File_list *before_current_file = (File_list *)malloc(sizeof(File_list));

	File *new_file = (File *)malloc(sizeof(File *));

	new_file->name = filename;
	new_file->data = content;
	new_file->size = strlen(content);

	File_list *new_file_list = (File_list *)malloc(sizeof(File_list));

	new_file_list->a_file = new_file;

	if (dir->files == NULL) {
		new_file_list->next = NULL;
		dir->files = new_file_list;
		free(head);
		return dir->files;
	}
	int cmp = strcasecmp(dir->files->a_file->name, new_file->name);

	if (cmp > 0) {
		new_file_list->next = dir->files;
		dir->files = new_file_list;
		return dir->files;
	}
	while (cmp < 0 && dir->files->next != NULL) {
		before_current_file = dir->files;
		dir->files = dir->files->next;
		cmp = strcasecmp(dir->files->a_file->name, new_file->name);
	}
	if (cmp < 0 && dir->files->next == NULL) {
		new_file_list->next = NULL;
		dir->files->next = new_file_list;
		return head;
	} else if (strcasecmp(dir->files->a_file->name, new_file->name) > 0)  {
		new_file_list->next = dir->files;
		before_current_file->next = new_file_list;
		return head;
	}

	return head;
}

Dir_list *mkdir(char *new_dir_name, Directory *dir)
{
	Dir_list *head = (Dir_list *)malloc(sizeof(Dir_list));

	head = dir->directories;

	Dir_list *before_dir = (Dir_list *)malloc(sizeof(Dir_list));

	Directory *new_dir = (Directory *)malloc(sizeof(Directory));

	new_dir->name = new_dir_name;
	new_dir->directories = NULL;
	new_dir->files = NULL;
	new_dir->parent_d = dir;

	Dir_list *new_dir_list = (Dir_list *)malloc(sizeof(Dir_list));

	new_dir_list->a_dir = new_dir;

	if (dir->directories == NULL) {
		new_dir_list->next = NULL;
		dir->directories = new_dir_list;
		free(head);
		return dir->directories;
	}

	int cmp = strcasecmp(dir->directories->a_dir->name, new_dir->name);

	if (cmp > 0) {
		new_dir_list->next = dir->directories;
		dir->directories = new_dir_list;
		return dir->directories;
	}
	while (cmp < 0 && dir->directories->next != NULL) {
		before_dir = dir->directories;
		dir->directories = dir->directories->next;
		cmp = strcasecmp(dir->directories->a_dir->name, new_dir->name);
	}
	if (cmp < 0 && dir->directories->next == NULL) {
		new_dir_list->next = NULL;
		dir->directories->next = new_dir_list;
		return head;
	} else if (cmp > 0)  {
		new_dir_list->next = dir->directories;
		before_dir->next = new_dir_list;
		return head;
	}

	return head;
}

void ls(Directory *current_directory)
{
	Dir_list *aux_directories = (Dir_list *)malloc(sizeof(Dir_list));

	aux_directories = current_directory->directories;

	File_list *aux_files = (File_list *)malloc(sizeof(File_list));

	aux_files = current_directory->files;

	while (aux_files != NULL) {
		printf("%s ", aux_files->a_file->name);
		aux_files = aux_files->next;
	}
	while (aux_directories != NULL) {
		printf("%s ", aux_directories->a_dir->name);
		aux_directories = aux_directories->next;
	}
	printf("\n");
}

Directory *cd(char *directory_name, Directory *current_directory)
{
	Dir_list *aux = (Dir_list *)malloc(sizeof(Dir_list));

	aux = current_directory->directories;
	if (strcmp(directory_name, "..") == 0) {
		if (current_directory->parent_d != NULL)
			return current_directory->parent_d;
		else
			return current_directory;
	} else {
		while (aux != NULL) {
			if (strcmp(aux->a_dir->name, directory_name) == 0)
				return aux->a_dir;
			aux = aux->next;
		}
	}
	printf("Cannot move to '%s': No such directory!\n", directory_name);
	return current_directory;
}

void tree(Dir_list *dir, File_list *files, int depth)
{
	if (dir != NULL || files != NULL) {
		if (files != NULL) {
			tab(depth);
			printf("%s\n", files->a_file->name);
			tree(dir, files->next, depth);
		} else {
			if (dir != NULL) {
				tab(depth);
				printf("%s\n", dir->a_dir->name);
				Dir_list *dirs = dir->a_dir->directories;

				tree(dirs, dir->a_dir->files, depth+1);
				tree(dir->next, files, depth);
			}
		}
	}
}

File_list *rm(char *filename, Directory *dir) // dir = current_directory
{
	int cmp;

	File_list *head = dir->files;

	File_list *before_current_file = dir->files;

	if (dir->files == NULL) {
		printf("Cannot remove '%s': No such file!\n", filename);
		return NULL;
	}
	if (!strcmp(dir->files->a_file->name, filename)) {
		before_current_file = dir->files->next;
		//free(head);
		//free(dir->files->a_file);
		return before_current_file;
	}
	if (dir->files->next != NULL) {
		while (dir->files->next != NULL) {
			cmp = strcmp(dir->files->a_file->name, filename);

			if (!cmp) {
				before_current_file->next = dir->files->next;
				//free(dir->files->a_file);
				return head;
			}
			before_current_file = dir->files;
			dir->files = dir->files->next;
		}
		if (!strcmp(dir->files->a_file->name, filename)) {
			before_current_file->next = NULL;
			//free(dir->files->a_file);
			return head;
		}
		printf("Cannot remove '%s': No such file!\n", filename);
		return head;
	}
}

Dir_list *rmdir(char *dir_name, Directory *dir)
{
	Dir_list *head = dir->directories;

	Dir_list *before_dir = dir->directories;

	if (dir->directories == NULL) {
		printf("Cannot remove '%s': No such directory!\n", dir_name);
		return NULL;
	}
	if (!strcmp(dir->directories->a_dir->name, dir_name)) {
		before_dir = dir->directories->next;
		free(head);
		free(dir->directories->a_dir);
		return before_dir;
	}
	if (dir->directories->next != NULL) {
		while (dir->directories->next != NULL) {
			if (!strcmp(dir->directories->a_dir->name, dir_name)) {
				before_dir->next = dir->directories->next;
				free(dir->directories->a_dir);
				return head;
			}
			before_dir = dir->directories;
			dir->directories = dir->directories->next;
		}
		if (!strcmp(dir->directories->a_dir->name, dir_name)) {
			before_dir->next = NULL;
			free(dir->directories->a_dir);
			return head;
		}
		printf("Cannot remove '%s': No such directory!\n", dir_name);
		return head;
	}
}

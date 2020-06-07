#define BUFFEr_SIz3 9999
char buffer[BUFFEr_SIz3];

#include "list.c"

int main(void)
{
	Directory *current_dir; //directorul curent
	char command[100];

	while (1) {
		scanf("%s", command);

		if (!strcmp(command, "create")) {
			char string[3];

			scanf("%s", string);
			if (!strcmp(string, "fs"))
				current_dir = create_fs();
		}

		if (!strcmp(command, "delete")) {
			char string[2];

			if (!strcmp(string, "fs"))
				delete_fs(current_dir);
			exit(0);
		}

		if (!strcmp(command, "touch")) {
			char *filename = (char *)malloc(sizeof(char) * 30);

			char *cont = (char *)malloc(sizeof(char) * 100);

			scanf("%s", filename);
			scanf("%s", cont);
			current_dir->files = touch(filename, cont, current_dir);
		}

		if (!strcmp(command, "mkdir")) {
			char *dir_name = (char *)malloc(sizeof(char) * 30);

			scanf("%s", dir_name);
			current_dir->directories = mkdir(dir_name, current_dir);
		}

		if (!strcmp(command, "ls"))
			ls(current_dir);

		if (!strcmp(command, "pwd")) {
			pwd(current_dir);
			printf("\n");
		}

		if (!strcmp(command, "cd")) {
			char directory_name[20];

			scanf("%s", directory_name);
			current_dir = cd(directory_name, current_dir);
		}

		if (!strcmp(command, "tree")) {
			printf("%s\n", current_dir->name);
			tree(current_dir->directories, current_dir->files, 1);
		}

		if (!strcmp(command, "rm")) {
			char *filename = (char *)malloc(sizeof(char) * 30);

			scanf("%s", filename);
			current_dir->files = rm(filename, current_dir);
			free(filename);
		}

		if (!strcmp(command, "rmdir")) {
			char *dir_name = (char *)malloc(sizeof(char) * 30);

			scanf("%s", dir_name);
			current_dir->directories = rmdir(dir_name, current_dir);
			free(dir_name);
		}
	}
	return 0;
}

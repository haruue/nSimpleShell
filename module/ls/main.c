#include <libndls.h>
#include <module.h>
#include <dir_common.h>
#include <dirent.h>


int module_main(int argc, char *argv[]) {
	char *path = malloc(MAX_PATH_LENGTH * sizeof(char));
	if (argc < 2) {	// 不带参数调用
		sh_getwd(path);
	} else {	// 带参数调用
		sh_relativePathToAbsolute(path, argv[1]);
	}
	if (!sh_isdir(path)) {
		nio_printf("ls: cannot access %s: No such directory\n", argv[1]);
		return -1;
	}
	// Read dir
	DIR *dir;
	dir = opendir(path);
	struct dirent * ptr;
	while ((ptr = readdir(dir)) != NULL) {
		nio_printf("%s\t", ptr->d_name);
	}
	nio_printf("\n");
	closedir(dir);

	free(path);
	return 0;
}

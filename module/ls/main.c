#include <libndls.h>
#include <module.h>
#include <dir_common.h>


int list_files(const char *path, void *context);
char *cut_path(const char *file_path, const char *dir_path);

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
	int (*callback_list_files)(const char *path, void *context);
	callback_list_files = list_files;
	file_each(path, callback_list_files, path);
	nio_printf("\n");
	free(path);
	return 0;
}

int list_files(const char *path, void *context) {
	char *filename = cut_path(path, (char *) context);
	if (filename != NULL) {
		nio_printf("%s\t", filename);
	}
	return 0;
}

/**
 * 处理递归时的 path ，截取指定目录下的路径
 */
char *cut_path(const char *file_path, const char *dir_path) {
	char *file_ptr = file_path;
	char *dir_ptr = dir_path;
	while (*++dir_ptr == *++file_ptr);
	if (*file_ptr == '/') {
		file_ptr++;
	}
	if (strstr(file_ptr, "/") == NULL) {
		return file_ptr;
	} else {
		return NULL;
	}
}

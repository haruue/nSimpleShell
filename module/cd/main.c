#include <libndls.h>
#include <module.h>
#include <const.h>

int changeDir(const char *dir_path);
char* dirToAbsolute(char *absolute_path, const char *dir_path);
int isDir(const char *path);
char *addEndSlash(char *string);
char *deleteEndSlash(char *string);
char *deleteLastDir(char *path);


int module_main(int argc, char *argv[]) {
	char *pwd = getenv("PWD");
	if (argc < 2 || pwd == NULL) {	// 直接 cd 不带参数，或者当前路径 PWD 并不存在
		char *home = getenv("HOME");
		if (home == NULL) {
			setenv("HOME", "/", 1);
			changeDir("/");
		} else {
			changeDir(home);
		}
		if (argc < 2) {	// 如果是 cd 不带参数的情况则可以直接退出
			return 0;
		}
	}
	return changeDir(argv[1]);
}

int changeDir(const char *dir_path) {
	char *absolute_path = malloc(MAX_PATH_LENGTH * sizeof(char));
	dirToAbsolute(absolute_path, dir_path);
	if (!isDir(absolute_path)) {
		nio_printf("sh: cd: %s: Not a directory\n", dir_path);
		return 1;
	}
	setenv("PWD", absolute_path, 1);
	free(absolute_path);
	return 0;
}

char* dirToAbsolute(char *absolute_path, const char *dir_path) {
	char *tmpPath = malloc(MAX_PATH_LENGTH * sizeof(char));
	if (dir_path[0] == '/') { // 绝对路径形式
		strcpy(tmpPath, dir_path);
	} else {
		char *pwd = getenv("PWD");
		strcpy(tmpPath, pwd);
		addEndSlash(tmpPath);
		strcat(tmpPath, dir_path);
	}
	strcpy(absolute_path, "/");
	char *fold;
	fold = strtok(tmpPath, "/");
	while (fold != NULL) {
		if (strcmp(fold, "") == 0 || strcmp(fold, ".") == 0) {
			fold = strtok(NULL, "/");
			continue;
		}
		if (strcmp(fold, "..") == 0) {
			deleteLastDir(absolute_path);
			fold = strtok(NULL, "/");
			continue;
		}
		addEndSlash(absolute_path);
		strcat(absolute_path, fold);
		fold = strtok(NULL, "/");
	}
	free(tmpPath);
	return absolute_path;
}

int isDir(const char *path) {
	if (strcmp(path, "/") == 0) {	// 我觉得这是一个 BUG ，根目录不被认为是一个目录。。。
		return 1;
	}
	struct stat info;
	stat(path,&info);
	return S_ISDIR(info.st_mode);
}

char *addEndSlash(char *string) {
	if (strcmp(string, "") == 0) {	// 本来就是空的
		strcpy(string, "/");
	} else {
		char *ptr = string;
		while (*++ptr);
		ptr--;
		if (*ptr != '/') {
			*(ptr + 1) = '/';
			*(ptr + 2) = '\0';
		}
	}
	return string;
}

char *deleteEndSlash(char *string) {
	if (strcmp(string, "") == 0) {
		strcpy(string, "/");
	} else {
		char *ptr = string;
		while (*++ptr);
		ptr--;
		if (*ptr == '/' && ptr != string) {
			*ptr = '\0';
		}
	}
	return string;
}

char *deleteLastDir(char *path) {
	char *ptr = path;
	deleteEndSlash(path);
	while (*++ptr);
	while (*--ptr != '/');
	if (ptr != path) {
		*ptr = '\0';
	} else {
		*(ptr + 1) = '\0';
	}
	return path;
}

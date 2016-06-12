#include "dir_common.h"

#include <libndls.h>
#include "const.h"

unsigned int __sh_dir_sizeofString(const char *string);
char *__sh_dir_mallocString(const char *string);
char *__sh_dir_addEndSlash(char *string);
char *__sh_dir_deleteEndSlash(char *string);
char *__sh_dir_deleteLastDir(char *path);

char *__sh_getcwd(char *buf, unsigned int size) {
	char *pwdString = getenv("PWD");
	if (pwdString == NULL) {
		char *homeString = getenv("HOME");
		if (homeString == NULL) {
			setenv("PWD", "/", 1);
			setenv("HOME", "/", 1);
		} else {
			setenv("PWD", homeString, 1);
		}
		pwdString = getenv("PWD");
	}
	int paramBufState = (buf != NULL) ? 1 : 0;
	int paramSizeState = (size != 0) ? 2 : 0;
	char *result;
	switch (paramBufState | paramSizeState) {
		case 0:
			result = __sh_dir_mallocString(pwdString);
			strcpy(result, pwdString);
			return result;
		case 1:
			strcpy(buf, pwdString);
			return buf;
		case 2:
			if (size >= __sh_dir_sizeofString(pwdString)) {
				result = malloc(size);
				strcpy(result, pwdString);
			} else {
				result = NULL;
			}
			return result;
		case 3:
			if (size >= __sh_dir_sizeofString(pwdString)) {
				strcpy(buf, pwdString);
			} else {
				buf = NULL;
			}
			return buf;
	}
	return NULL;
}

char *__sh_getwd(char *path_name) {
	return sh_getcwd(path_name, 0);
}

int __sh_chdir(const char *path) {
	char *absolute_path = malloc(MAX_PATH_LENGTH * sizeof(char));
	sh_relativePathToAbsolute(absolute_path, path);
	if (!sh_isdir(absolute_path)) {
		return 1;
	}
	setenv("PWD", absolute_path, 1);
	free(absolute_path);
	return 0;
}

int __sh_mkdir(const char *path_name, int mode) {
	char *absolute_path = malloc(MAX_PATH_LENGTH * sizeof(char));
	sh_relativePathToAbsolute(absolute_path, path_name);
	return mkdir(absolute_path, mode);
}

int __sh_rmdir(const char *path) {
	char *absolute_path = malloc(MAX_PATH_LENGTH * sizeof(char));
	sh_relativePathToAbsolute(absolute_path, path);
	return rmdir(absolute_path);
}

int __sh_isdir(const char *path) {
	if (strcmp(path, "/") == 0) {	// 我觉得这是一个 BUG ，根目录不被认为是一个目录。。。
		return 1;
	}
	struct stat info;
	stat(path, &info);
	return S_ISDIR(info.st_mode);
}

int __sh_isAbsolutePath(const char *path) {
	return path[0] == '/';
}

char *__sh_relativePathToAbsolute(char *absolute_path, const char *relative_path) {
	char *tmpPath = malloc(MAX_PATH_LENGTH * sizeof(char));
	if (sh_isAbsolutePath(relative_path)) { // 绝对路径形式
		strcpy(tmpPath, relative_path);
	} else {
		char *pwd = sh_getcwd(NULL, 0);
		strcpy(tmpPath, pwd);
		free(pwd);
		__sh_dir_addEndSlash(tmpPath);
		strcat(tmpPath, relative_path);
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
			__sh_dir_deleteLastDir(absolute_path);
			fold = strtok(NULL, "/");
			continue;
		}
		__sh_dir_addEndSlash(absolute_path);
		strcat(absolute_path, fold);
		fold = strtok(NULL, "/");
	}
	free(tmpPath);
	return absolute_path;
}


/********************
 *      INTERAL     *
 ********************/

/**
 * 返回 string 占用的内存空间
 */
unsigned int __sh_dir_sizeofString(const char *string) {
	return (strlen(string) + 1) * sizeof(char);
}

/**
 * 分配一块与给定的 string 一样大的堆内存
 */
char *__sh_dir_mallocString(const char *string) {
	return malloc(__sh_dir_sizeofString(string));
}

/**
 * 添加末尾斜杠，如
 * "/document" -> "/document/"
 * 已有斜杠的不会再添加
 * "/document/" -> "/document/"
 * "/" -> "/"
 * 传入空字符串将会被添加一个斜杠成为根目录
 * "" -> "/"
 */
char *__sh_dir_addEndSlash(char *string) {
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

/**
 * 删除末尾斜杠，如
 * "/documents/" -> "/documents"
 * 末尾无斜杠则不会有任何变化
 * "/documents" -> "/documents/"
 * 根目录斜杠不会被删除
 * "/" -> "/"
 * 传入空字符串将会被添加一个斜杠成为根目录
 * "" -> "/"
 */
char *__sh_dir_deleteEndSlash(char *string) {
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

/**
 * 删除路径末尾的目录或文件到上一层目录
 * "/documents/ndless" -> "/documents/ndless"
 * "/documents/ndless/" -> "/documents/ndless/"
 * 此函数调用 char *deleteEndSlash(char *string) ，特殊情况处理相同，不再赘述
 */
char *__sh_dir_deleteLastDir(char *path) {
	char *ptr = path;
	__sh_dir_deleteEndSlash(path);
	while (*++ptr);
	while (*--ptr != '/');
	if (ptr != path) {
		*ptr = '\0';
	} else {
		*(ptr + 1) = '\0';
	}
	return path;
}

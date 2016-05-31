#include "shell_env.h"

#include <libndls.h>
#include <string.h>

char* getKey(char *key, const char* string);
char* getValue(char *key, const char* string);
void checkEmpty();

char **environ = NULL;
int envcount = 0;

void setDefaultShellEnv(char **env) {
	environ = env;
}

char** sh_environ() {
	checkEmpty();
	return environ;
}

char* sh_getenv(const char *key) {
	checkEmpty();
	char** currentEnv = environ;
	while (*currentEnv != NULL) {
		char *tmpkey = (char *) malloc(sizeof(*currentEnv));
		if (strcmp(key, getKey(tmpkey, *currentEnv)) == 0) {
			char *value = getValue(tmpkey, *currentEnv);
			free(tmpkey);
			return value;
		}
		free(tmpkey);
		currentEnv++;
	}
	return NULL;
}

int sh_putenv(const char *string) {
	checkEmpty();
	char **old_environ = environ;
	environ = malloc((envcount + 2) * sizeof(char **));
	if (environ == NULL) {	// 内存分配失败，回滚更改
		environ = old_environ;
		return -1;
	}
	char **currentEnv = environ;
	char **currentOldEnv = old_environ;
	while (NULL != *currentOldEnv) {
		*currentEnv = malloc(sizeof(*currentOldEnv));
		if (*currentEnv == NULL) {	// 内存分配失败，回滚更改
			environ = old_environ;
			return -1;
		}
		strcpy(*currentEnv, *currentOldEnv);
		free(*currentOldEnv);
		currentEnv++;
		currentOldEnv++;
	}
	*currentEnv = malloc(sizeof(string));
	if (*currentEnv == NULL) {	// 内存分配失败，回滚更改
			environ = old_environ;
			return -1;
	}
	strcpy(*currentEnv, string);
	currentEnv++;
	*currentEnv = NULL;
	return 0;
}

int sh_setenv(const char *name, const char * value, int overwrite) {
	checkEmpty();
	if (overwrite == 0 && NULL != sh_getenv(name)) {	// 不覆盖已有变量
		return 0;
	}
	char *string = malloc(sizeof(name) + sizeof(value) + 1);
	if (string == NULL) {	// 内存分配失败
		return -1;
	}
	strcpy(string, name);
	strcat(string, "=");
	strcat(string, value);
	int result = sh_putenv(string);
	free(string);
	return result;
}

void sh_unsetenv(const char *key) {
	checkEmpty();
	char** currentEnv = environ;
	while (*currentEnv != NULL) {
		char *tmpkey = malloc(sizeof(*currentEnv));
		if (strcmp(getKey(tmpkey, *currentEnv), key) == 0) {
			char** old = currentEnv + 1;
			char** new = currentEnv;
			while (*old != NULL) {
				*new = *old;
				old++;
				new++;
			}
			*new = NULL;
			free(*old);
			free(old);
			free(tmpkey);
		}
		free(tmpkey);
	}
}



// 以下函数用于内部调用
char* getKey(char *key, const char* string) {
	strcpy(key, string);
	strtok(key, "=");
	return key;
}

char* getValue(char *key, const char* string) {
	strcpy(key, string);
	return strtok(key, "=");
}

void checkEmpty() {
	if (environ == NULL) {
		environ = malloc(sizeof(char **));
		*environ = NULL;
	}
}
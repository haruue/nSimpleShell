#include "shell_common.h"

#include <libndls.h>
#include <nspireio/nspireio.h>
#include "const.h"
#include "shell_env.h"



int sh_system(const char *command) {
	char *string = malloc(sizeof(command));
	strcpy(string, command);
	char *words[MAX_ARGUMENTS_COUNT] = {0};
	int argument_count = 0;
	char *tmp;
	while ((tmp = strtok(string, "")) != NULL) {
		words[argument_count] = string;
		string = tmp;
		argument_count++;
	}
	// 作为环境变量定义
	if (strstr(words[0], "=") != NULL) {
		sh_putenv(string);
		free(string);
		return 0;
	}
	free(string);
	// 作为模块命令
	char *path = malloc(50 * sizeof(char));
	strcpy(path, sh_getenv("PATH"));
	strcat(path, "/");
	strcat(path, words[0]);
	strcat(path, ".tns");
	if (access(path, F_OK) != 0) {
		nio_printf("sh: %s: command not found\n", words[0]);
		return 127;
	}
	int argc = argument_count + EXTERN_ARGUMENTS_COUNT - 1;
	char **argv = malloc(argc * sizeof(char *));
	argv[0] = (char *) nio_get_default();
	argv[1] = (char *) sh_environ();
	for (int i = 0; i < argument_count; ++i) {
		argv[i + EXTERN_ARGUMENTS_COUNT] = words[i + 1];
	}
	int result = nl_exec(path, argc, argv);
	nio_load(CONSOLE_SCREEN_CACHE_FILE, nio_get_default());
	return result;
}

int sh_script(const char* path) {
	if (access(path, F_OK) != 0) {
		nio_printf("sh: %s: No such file or directory\n", path);
		return 1;
	}
	FILE *fp = fopen(path, "r");
	if (NULL == fp) {
		nio_printf("sh: %s: Permission denied\n", path);
		return 1;
	}	
	char *command = malloc(MAX_COMMAND_LENGTH * sizeof(char));
	int result = 0;
	while (!feof(fp)) {
		memset(command, 0, MAX_COMMAND_LENGTH * sizeof(char));
		fgets(command, sizeof(command) - 1, fp);
		result = sh_system(command);
	}
	free(command);
	fclose(fp);
	return result;
}

void sh_exit(int status) {
	nio_save(CONSOLE_SCREEN_CACHE_FILE, nio_get_default());
	exit(status);
}

void sh_exit_with_shell() {
	sh_exit(RETURN_VALUE_EXIT);
}

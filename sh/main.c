#include <libndls.h>
#include "shell_common.h"
#include "const.h"

int main(void) {
	assert_ndless_rev(877);

	// 初始化 console 
	nio_console csl;
    nio_init(&csl, NIO_MAX_COLS, NIO_MAX_ROWS, 0, 0, BLACK, WHITE, TRUE);
    nio_set_default(&csl);
	
    char *command = malloc(MAX_COMMAND_LENGTH * sizeof(char));

    int result = sh_script(PATH_INITRC);

	while (result != RETURN_VALUE_EXIT) {
		memset(command, 0, MAX_COMMAND_LENGTH * sizeof(char));
		if (getenv("PS1")) {
			nio_printf("%s ", getenv("PS1"));
		} else {
			nio_printf("%s ", "$");
			printf("PS1 undef");
		}
		nio_getsn(command, MAX_COMMAND_LENGTH);
		if (strlen(command) == 0) {
			result = 0;
			continue;
		}
		if (strcmp(command, "exit") == 0) {
			result = RETURN_VALUE_EXIT;
			continue;
		}
		if (strcmp(command, "sh") == 0) {
			result = 0;
			continue;
		}
		result = sh_system(command);
	}

    // 释放 console 
	nio_free(&csl);
	return 0;
}

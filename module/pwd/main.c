#include <libndls.h>
#include <module.h>
#include <dir_common.h>

int module_main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
	char *pwd = (char *) malloc(MAX_PATH_LENGTH * sizeof(char));
	nio_printf("%s\n", sh_getwd(pwd));
	free(pwd);
	return 0;
}

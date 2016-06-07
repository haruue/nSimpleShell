#include <libndls.h>
#include <module.h>
#include <const.h>
#include <dir_common.h>

int module_main(int argc, char *argv[]) {
	int result = 0;
	if (argc < 2) {	// 直接 cd 不带参数
		char *home = getenv("HOME");
		if (home == NULL) {
			setenv("HOME", "/", 1);
			result = sh_chdir("/");
		} else {
			result = sh_chdir(home);
		}
	} else {
		result = sh_chdir(argv[1]);
	}
	if (result != 0) {
		nio_printf("cd: %s: Not a directory\n", argv[1]);
	}
	return result;
}

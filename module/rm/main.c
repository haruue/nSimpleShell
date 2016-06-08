#include <libndls.h>
#include <module.h>
#include <dir_common.h>

int module_main(int argc, char *argv[]) {
	if (argc < 2) {	// 不带参数运行
		printf("rm: missing operand\n");
		return 1;
	}
	char *path = malloc(MAX_PATH_LENGTH * sizeof(char));
	sh_relativePathToAbsolute(path, argv[1]);
	int result = remove(path);
	if (result != 0) {
		nio_printf("rm: cannot remove `%s\': No such file\n", argv[1]);
	}
	return result;
}

#include <libndls.h>
#include <module.h>
#include <dir_common.h>
#include <const.h>

int module_main(int argc, char *argv[]) {
	if (argc < 2) {	// 不带参数执行
		nio_printf("cat: missing file operand\n");
		return 1;
	}
	char *path = malloc(MAX_PATH_LENGTH * sizeof(char));
	sh_relativePathToAbsolute(path, argv[1]);
	FILE *fp = fopen(path, "r");
	if (fp == NULL) {
		nio_printf("cat: %s: No such file\n", argv[1]);
		return 1;
	}
	char c;
	while (c = fgetc(fp), !feof(fp)) {
		nio_putc(c, nio_get_default());
	}
	fclose(fp);
	return 0;
}

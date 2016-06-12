#include <libndls.h>
#include <module.h>
#include <dir_common.h>

char *__sh_dir_addEndSlash(char *string);
char *basename(char *path);

int module_main(int argc, char *argv[]) {
	if (argc < 3) {	// 不带参数或者只带一个参数运行
		nio_printf("cp: missing file operand\n");
		return 1;
	}
	// 前置输入处理
	char *src_path = (char *) malloc(MAX_PATH_LENGTH * sizeof(char));
	sh_relativePathToAbsolute(src_path, argv[1]);
	char *dst_path = (char *) malloc(MAX_PATH_LENGTH * sizeof(char));
	sh_relativePathToAbsolute(dst_path, argv[2]);
	if (sh_isdir(src_path)) {	// 如果源是一个目录，提示不支持
		nio_printf("cp: sorry, not support yet.\n");
		return 1;
	}
	if (sh_isdir(dst_path)) {	// 如果目标是一个目录，则当目录处理，在后面加上文件名
		__sh_dir_addEndSlash(dst_path);
		strcat(dst_path, basename(src_path));
	}
	FILE *fp_src = fopen(src_path, "r");
	if (fp_src == NULL) {
		nio_printf("cp: cannot stat `%s': No such file", argv[1]);
		return 1;
	}
	FILE *fp_dst = fopen(dst_path, "w");
	if (fp_dst == NULL) {
		nio_printf("cp: cannot create regular file `%s': No such file or directory\n", argv[2]);
		return 1;
	}
	char c;
	while (c = fgetc(fp_src), !feof(fp_src)) {
		fputc(c, fp_dst);
	}
	fclose(fp_src);
	fclose(fp_dst);
	free(src_path);
	free(dst_path);
	return 0;
}

char *basename(char *path) {
	while (*++path != '\0');	// 移动到最后
	while (*--path != '/');		// 移动到斜杠
	path++;
	return path;
}
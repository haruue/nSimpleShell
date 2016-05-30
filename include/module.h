#ifndef __SHELL_INCLUDE_MODULE_H__
#define __SHELL_INCLUDE_MODULE_H__

/**
 * module.h
 * 这个头文件用于模块的创建，创建模块时 #include "module.h" 并且实现 module_main
 */

#include <libndls.h>
#include "const.h"
#include "shell_env.h"

/**
 * 模块的入口
 * 在每个模块里实现这个函数，就像 main 函数一样，它为模块提供参数和环境变量
 * @param argc 参数个数
 * @param argv 参数值
 * @return 模块的返回值
 */
int module_main(int argc, char* argv[]);

/**
 * 检测模块的执行方式
 * 如果发现用户是直接通过“文档”执行模块，则显示一个窗口并退出
 */
int assert_straight_run(int argc) {
	if (argc < EXTERN_ARGUMENTS_COUNT) {
		show_msgbox("Failure", "This program must be executed by sh.");
		exit(0);
	}
	return 0;
}

int main(int argc, char* argv[]) {
	assert_ndless_rev(877);
	assert_straight_run(argc);

	// 区分程序参数和额外参数
	// 程序参数
	int module_argc = argc - EXTERN_ARGUMENTS_COUNT;
	char **module_argv = new char*[module_argc];
	module_argv[0] = argv[0];
	for (int i = 1; i < module_argc; i++) {
		module_argv[i] = argv[i + EXTERN_ARGUMENTS_COUNT];
	}
	// 额外参数
	nio_console *csl = (nio_console *) argv[1];
    nio_set_default(csl);
    SHELL_ENV *env = (SHELL_ENV *) argv[2];
    setDefaultShellEnv(env);

    // 执行模块的 main 函数
    int result = module_main(module_argc, module_argv);

    // 保存当前控制台状态，否则返回到 sh 时当前程序的输出将会消失
	nio_save(CONSOLE_SCREEN_CACHE_FILE, csl);
	return result;
}




#endif /*__SHELL_INCLUDE_MODULE_H__*/

#ifndef __SHELL_INCLUDE_SHELL_COMMON_H__
#define __SHELL_INCLUDE_SHELL_COMMON_H__

/**
 * shell_common.h
 * 这个头文件提供一些 module 与 shell 交互时常用的函数
 */

#include <nspireio/nspireio.h>

/**
 * 系统调用，执行 shell 命令
 * @param string 命令
 */
#define sh_system __sh_system
int sh_system(const char *string);

/**
 * 执行一个 shell 脚本文件
 * @param shell 脚本文件路径
 */
#define sh_script __sh_script
int sh_script(const char* path);

/**
 * 退出一个 module
 * @param status 返回给 shell 的值
 */
#define sh_exit __sh_exit
void sh_exit(int status);

/**
 * 退出 module 并退出这层 shell 
 */
#define sh_exit_with_shell __sh_exit_with_shell
void sh_exit_with_shell();



#endif /*__SHELL_INCLUDE_SHELL_COMMON_H__*/

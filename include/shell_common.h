#ifndef __SHELL_INCLUDE_SHELL_COMMON_H__
#define __SHELL_INCLUDE_SHELL_COMMON_H__

/**
 * shell_common.h
 * 这个头文件提供一些常用的函数
 */

#include "const.h"

/**
 * 系统调用，执行 shell 命令
 * @param string 命令
 */
int sh_system(const char *string);

/**
 * 退出程序并退出这层 shell 
 */
void exit_shell();



#endif /*__SHELL_INCLUDE_SHELL_COMMON_H__*/
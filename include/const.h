#ifndef __SHELL_INCLUDE_CONST_H__
#define __SHELL_INCLUDE_CONST_H__

/**
 * const.h
 * 这个头文件存储一些常量
 */

// 额外参数个数，如控制台 csl 和环境变量 env
#define EXTERN_ARGUMENTS_COUNT 2

// 表示退出的返回值，如果 module 对 shell 返回了这个值， shell 将会退出
#define RETURN_VALUE_EXIT 23065

// 控制台缓存文件
#define CONSOLE_SCREEN_CACHE_FILE "/tmp/console_cache.tns"


#endif /*__SHELL_INCLUDE_CONST_H__*/

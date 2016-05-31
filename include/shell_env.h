#ifndef __SHELL_INCLUDE_SHELL_ENV_H__
#define __SHELL_INCLUDE_SHELL_ENV_H__

/**
 * shell_env.h
 * 这个头文件用于处理环境变量
 */

/**
 * 设置以下函数进行处理的环境变量，一般仅用于内部调用
 * @param 指向首个环境变量的指针
 */
void setDefaultShellEnv(char** env);

/**
 * 获得指向首个环境变量的指针以进行遍历
 * @return 相当于 extern char ** environ;
 */
char** sh_environ();

/**
 * 通过 key 获取一个环境变量
 * @param key 需要获取的环境变量对应的 key 值
 * @return 如果存在这个环境变量，返回对应的 value ，否则返回 NULL
 */
char* sh_getenv(const char *key);

/**
 * 改变或增加环境变量的内容
 * @param string 格式为 KEY=VALUE
 * @return 成功则返回 0 ，否则返回 -1
 */
int sh_putenv(const char *string);

/**
 * 设置一个环境变量
 * @param key 需要设置的 key 的值
 * @param value 需要设置的 value 的值 
 * @param overwrite 是否覆盖，0 不覆盖，1 覆盖
 * @return 成功则返回 0 ，否则返回 -1
 */
int sh_setenv(const char *name,const char * value,int overwrite);


/**
 * 删除一个环境变量
 * @param key 需要被删除的环境变量对应的 key 值
 */
void sh_unsetenv(const char *key);

#endif /*__SHELL_INCLUDE_SHELL_ENV_H__*/

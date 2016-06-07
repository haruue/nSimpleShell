#ifndef __SHELL_INCLUDE_DIR_COMMON_H__
#define __SHELL_INCLUDE_DIR_COMMON_H__

/**
 * dir_common.h
 * 这个头文件提供一些目录相关的方法
 */

/**
 * 获取当前工作目录
 * @param buf 存放工作目录字符串的内存指针（传入 NULL 可自动动态分配）
 * @param size buf的长度，传入 0 自动确定大小
 * @return 如果绝对路径长度超过 size ，返回 NULL。否则返回结果
 */
char *sh_getcwd(char *buf, unsigned int size);

/**
 * 获取当前工作目录
 * @param path_name 存放工作目录字符串的内存指针（传入 NULL 可自动动态分配）
 * @return 当前工作目录
 */
char *sh_getwd(char *path_name);

/**
 * 改变当前工作目录
 * @param path 需要改变到的目录的相对路径或者绝对路径
 * @return 成功返回 0 ，发生错误则返回错误代码
 */
int sh_chdir(const char *path);

/**
 * 创建目录
 * @param path_name 需要创建的目录的相对路径或者绝对路径
 * @param mode 访问权限（貌似 Nspire 上一般用 0777 就好）
 * @return 成功返回 0 ，失败返回错误代码
 */
int sh_mkdir(const char *path_name, int mode);

/**
 * 删除目录
 * @param path 需要删除的目录的相对路径或者绝对路径，目录必须为空
 * @return 成功返回 0 ，失败返回错误代码
 */
int sh_rmdir(const char *path);

/**
 * 判断一个路径是否是目录
 * @param path 需要检测的相对路径或者绝对路径
 * @return 是目录则返回 1 ，否则返回 0 
 */
int sh_isdir(const char *path);

/**
 * 判断一个路径是不是绝对路径，路径所指的目标不一定存在
 * @param path 需要判断的路径
 * @return 绝对路径返回 1 ，否则返回 0  
 */
int sh_isAbsolutePath(const char *path);

/**
 * 将相对路径转换成绝对路径，路径对应的位置不一定存在
 * @param absolute_path 存放绝对路径结果的内存空间，请保证足够大
 * @param relative_path 需要转换的相对路径
 * @return 转换结果
 */
char *sh_relativePathToAbsolute(char *absolute_path, const char *relative_path);




#endif /*__SHELL_INCLUDE_DIR_COMMON_H__*/
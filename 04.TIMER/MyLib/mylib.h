/*
 * mylib.h
 *
 *  Created on: 2021年8月15日
 *      Author: Francis
 */

#ifndef MYLIB_MYLIB_H_
#define MYLIB_MYLIB_H_

#include <stdio.h>
/*
 * 延时函数头文件
 * sleep()延时s
 * usleep()延时ms
 */
#include <unistd.h>

//printf重定向
int fputc(int _c, register FILE *_fp);
int fputs(const char *_ptr, register FILE *_fp);
//需要使用printf或delay时，要先调用该函数
void mainLib(void);

#endif /* MYLIB_MYLIB_H_ */

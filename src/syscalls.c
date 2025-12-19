/**
 * @file    syscalls.c
 * @brief   System call implementations for newlib.
 * @note    This file is require for warning-free linking with newlib.
 */

#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

int _close(int file) { return -1; }
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int file) { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _read(int file, char *ptr, int len) { return 0; }
int _write(int file, char *ptr, int len) {
    // 如果需要，这里可以连接到 UART 输出
    return 0;
}
int _getpid(void) { return 1; }
int _kill(int pid, int sig) { errno = EINVAL; return -1; }
/*
 * log.h
 *
 *  Created on: Feb 19, 2020
 *      Author: alex
 */

#ifndef SRC_COMMON_LOG_H_
#define SRC_COMMON_LOG_H_

#include <stdio.h>

/* Log out of memory without message buffering */
//void error();
void log_oom(const char *file, int line, const char *func);
void fatal(const char *fmt, ...);

#define error(...) printf(__VA_ARGS__)

#endif /* SRC_COMMON_LOG_H_ */

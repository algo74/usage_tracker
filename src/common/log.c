/*
 * log.c
 *
 *  Created on: Feb 19, 2020
 *      Author: alex
 */


#include <stdio.h>

/* Log out of memory without message buffering */
void log_oom(const char *file, int line, const char *func)
{

  fprintf(stderr, "%s:%d: %s: malloc failed\n", file, line, func);

}

/*
 * attempt to log message and exit()
 */
void fatal(const char *fmt, ...)
{
  fprintf(stderr,"fatal: %s\n", fmt);


  exit(1);
}

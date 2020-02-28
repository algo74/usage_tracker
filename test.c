/*
 * test.c
 *
 *  Created on: Feb 19, 2020
 *      Author: alex
 */

#include <stdio.h>

//#include "config.h"
#include "src/common/list.h"
#include "src/common/xmalloc.h"
#include "src/common/xassert.h"

#include "usage_tracker.h"


char* time2str(time_t t) {
  if (t==-1) {
    return "-1\n";
  }
  if (t == 0) {
    return "0\n";
  }
  return ctime(&t);
}

void check(utracker_int_t ut, time_t when, time_t d, int value) {
  printf("first below %d for %ld after %s", value, d, time2str(when));
  printf("         is -- %s", time2str(ut_int_when_below(ut, when, d, value)));
}

int main() {

  //List test_list = list_create(test_free_entry);

  printf("creating with 10\n");

  utracker_int_t ut = ut_int_create(10);

  ut_int_dump(ut);


  time_t now = time(NULL);
  printf("now: %s\n", ctime(&now));

  //check(ut, now, 10, 20);
  xassert(ut_int_when_below(ut, now, 10, 20) == now);

  //check(ut, now, 10, 10);
  xassert(ut_int_when_below(ut, now, 10, 10) == -1);

  ut_int_add_usage(ut, now, now+20, 30);

  ut_int_dump(ut);

  xassert(ut_int_when_below(ut, now, 10, 41) == now);
  xassert(ut_int_when_below(ut, now, 10, 40) == now+20);
  xassert(ut_int_when_below(ut, now+10, 10, 40) == now+20);
  xassert(ut_int_when_below(ut, now+20, 10, 40) == now+20);
  xassert(ut_int_when_below(ut, now+21, 10, 40) == now+21);
  xassert(ut_int_when_below(ut, now+10, 10, 10) == -1);
  xassert(ut_int_when_below(ut, now+10, 1, 40) == now+20);
  xassert(ut_int_when_below(ut, now, 1, 40) == now+20);


  ut_int_add_usage(ut, now+5, now+10, 30);

  ut_int_dump(ut);

  xassert(ut_int_when_below(ut, now, 10, 41) == now+10);
  xassert(ut_int_when_below(ut, now, 10, 40) == now+20);
  xassert(ut_int_when_below(ut, now, 5, 41) == now);
  xassert(ut_int_when_below(ut, now+20, 10, 40) == now+20);
  xassert(ut_int_when_below(ut, now+21, 10, 40) == now+21);
  xassert(ut_int_when_below(ut, now+10, 10, 10) == -1);
  xassert(ut_int_when_below(ut, now+10, 1, 40) == now+20);
  xassert(ut_int_when_below(ut, now, 1, 40) == now+20);
  xassert(ut_int_when_below(ut, now, 100, 71) == now);
  xassert(ut_int_when_below(ut, now+4, 100, 71) == now+4);

  ut_int_add_usage(ut, now+5, now+10, 30);

  ut_int_dump(ut);

  ut_int_add_usage(ut, now+10, now+20, 60);

  ut_int_dump(ut);

  ut_int_remove_till_end(ut, now+15, -90);

  ut_int_dump(ut);

  xassert(ut_int_when_below(ut, now, 100, 71) == -1);
  xassert(ut_int_when_below(ut, now, 100, 100) == -1);
  xassert(ut_int_when_below(ut, now, 100, 101) == now+20);
  xassert(ut_int_when_below(ut, now, 5, 41) == now);
  xassert(ut_int_when_below(ut, now, 6, 41) == -1);
  xassert(ut_int_when_below(ut, now, 6, 101) == now);
  xassert(ut_int_when_below(ut, now, 15, 101) == now);
  xassert(ut_int_when_below(ut, now, 16, 101) == now+20);

  ut_int_remove_till_end(ut, now+15, 90);

  ut_int_dump(ut);

  ut_int_remove_till_end(ut, now+20, -90);

  ut_int_dump(ut);

  ut_int_remove_till_end(ut, now+5, 60);

  ut_int_dump(ut);

  ut_int_remove_till_end(ut, now, 30);

  ut_int_dump(ut);

  ut_int_destroy(ut);

  ut = ut_int_create(100);

  ut_int_remove_till_end(ut, now+10, 20);
  ut_int_remove_till_end(ut, now+20, 20);
  ut_int_remove_till_end(ut, now+40, 40);

  ut_int_dump(ut);

  xassert(ut_int_when_below(ut, now, 100, 20) == -1);
  xassert(ut_int_when_below(ut, now, 100, 100) == now+10);
  xassert(ut_int_when_below(ut, now, 100, 101) == now);
  xassert(ut_int_when_below(ut, now, 5, 80) == now+20);
  xassert(ut_int_when_below(ut, now, 6, 40) == now+40);
  xassert(ut_int_when_below(ut, now, 6, 60) == now+40);

  printf("tests passed\n");

  ut_int_destroy(ut);

  ut = ut_int_create(212);
  ut_int_remove_till_end(ut, (now/60+1)*60+25, 1);
  ut_int_add_usage(ut, (now/60+1)*60+24, (now/60+1)*60+35, 6000);
  ut_int_dump(ut);
  ut_int_add_usage(ut, (now/60+1)*60+35, (now/60+1)*60+47, 6000);
  ut_int_dump(ut);
  xassert(ut_int_when_below(ut, (now/60+1)*60+24, 6, 212) == (now/60+1)*60+47);
}

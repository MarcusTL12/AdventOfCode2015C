#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_util/file_util.h"

void d1p1() {
    char *inp = file_read_full("input/day1/input");

    int64_t floor = 0;
    for (char *c = inp; *c; c++) floor += *c == '(' ? 1 : -1;

    printf("%li\n", floor);

    free(inp);
}

void d1p2() {
    char *inp = file_read_full("input/day1/input");

    int64_t floor = 0, ans;
    for (char *c = inp; *c; c++) {
        floor += *c == '(' ? 1 : -1;
        if (floor == -1) {
            ans = c - inp + 1;
            break;
        }
    }

    printf("%li\n", ans);

    free(inp);
}

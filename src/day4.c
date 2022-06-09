#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "aoc_util/md5_util.h"

const char *INPUT = "ckczppom";

void d4p1() {
    size_t inplen = strlen(INPUT);

    char strbuffer[32], hashbuf[16];
    char *numbuffer = strbuffer + inplen;
    memcpy(strbuffer, INPUT, inplen);

    size_t i = 1;
    while (true) {
        size_t digits = sprintf(numbuffer, "%zu", i);
        md5(hashbuf, strbuffer, inplen + digits);
        if (!hashbuf[0] && !hashbuf[1] && !(hashbuf[2] & 0xf0)) break;
        i++;
    }

    printf("%zu\n", i);
}

void d4p2() {
    size_t inplen = strlen(INPUT);

    char strbuffer[32], hashbuf[16];
    char *numbuffer = strbuffer + inplen;
    memcpy(strbuffer, INPUT, inplen);

    size_t i = 1;
    while (true) {
        size_t digits = sprintf(numbuffer, "%zu", i);
        md5(hashbuf, strbuffer, inplen + digits);
        if (!hashbuf[0] && !hashbuf[1] && !hashbuf[2]) break;
        i++;
    }

    printf("%zu\n", i);
}

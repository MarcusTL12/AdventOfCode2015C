#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_util/file_util.h"
#include "aoc_util/int_util.h"
#include "aoc_util/array_util.h"

void d2p1() {
    char *inp = file_read_full("input/day2/input");

    int64_t ans = 0;

    for (char *c = inp; *c;) {
        int64_t dims[3];
        for (size_t i = 0; i < 3; i++) {
            dims[i] = parse_push_int64(&c);
            c++;
        }

        int64_t minside = dims[0] * dims[1];

        for (size_t i = 0; i < 3; i++) {
            for (size_t j = i + 1; j < 3; j++) {
                int64_t side = dims[i] * dims[j];
                minside = min(side, minside);
                ans += side * 2;
            }
        }

        ans += minside;
    }

    printf("%li\n", ans);

    free(inp);
}

void d2p2() {
    char *inp = file_read_full("input/day2/input");

    int64_t ans = 0;

    for (char *c = inp; *c;) {
        int64_t dims[3];
        for (size_t i = 0; i < 3; i++) {
            dims[i] = parse_push_int64(&c);
            c++;
        }

        minmax_t mm = minmax_inds(dims, 3);
        size_t mid_ind = 3 - mm.min - mm.max;

        ans += 2 * (dims[mm.min] + dims[mid_ind]) + dims[0] * dims[1] * dims[2];
    }

    printf("%li\n", ans);

    free(inp);
}

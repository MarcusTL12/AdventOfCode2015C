#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_util/file_util.h"
#include "aoc_util/hashmap.h"
#include "aoc_util/point.h"

static point2i char2dir(char c) {
    switch (c) {
        case '<':
            return (point2i){-1, 0};
        case '>':
            return (point2i){1, 0};
        case 'v':
            return (point2i){0, -1};
        case '^':
            return (point2i){0, 1};
    }
    return (point2i){0, 0};
}

void d3p1() {
    char *inp = file_read_full("input/day3/input");

    struct hashmap *visited = hashmap_new(
        sizeof(point2i), 0, 3, 2, point2i_hash, point2i_cmp, NULL, NULL);

    point2i pos = {0, 0};
    hashmap_set(visited, &pos);

    for (char *c = inp; *c && *c != '\n'; c++) {
        pos = point2i_add(pos, char2dir(*c));
        hashmap_set(visited, &pos);
    }

    printf("%zu\n", hashmap_count(visited));

    hashmap_free(visited);
    free(inp);
}

void d3p2() {
    char *inp = file_read_full("input/day3/input");

    struct hashmap *visited = hashmap_new(
        sizeof(point2i), 0, 3, 2, point2i_hash, point2i_cmp, NULL, NULL);

    point2i pos[2] = {0}, *ppos[2] = {&pos[0], &pos[1]};
    hashmap_set(visited, &(point2i){0, 0});

    for (char *c = inp; *c && *c != '\n'; c++) {
        *ppos[0] = point2i_add(*ppos[0], char2dir(*c));
        hashmap_set(visited, ppos[0]);
        point2i *tmp = ppos[0];
        ppos[0] = ppos[1];
        ppos[1] = tmp;
    }

    printf("%zu\n", hashmap_count(visited));

    hashmap_free(visited);
    free(inp);
}
